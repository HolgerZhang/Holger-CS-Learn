#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "game.h"

// 裁判
void run_judgement(int msg_notice1,  // 通知玩家1的消息队列id
                   int msg_notice2,  // 通知玩家2的消息队列id
                   int msg_rec1,  // 获取玩家1出招结果的消息队列id
                   int msg_rec2,  // 获取玩家2出招结果的消息队列id
                   const int rounds) {
  // 历史记录
  round_logs_t *round_logs = malloc((rounds + 1) * sizeof(round_logs_t));
  round_logs[0].action1 = round_logs[0].action2 = ACT_NONE;  // 第一条记录设置为空
  round_logs[0].result = RES_DRAW;
  for (int round = 1; round <= rounds; ++round) {
    fflush(stdout);  // 刷新标准输出缓冲区
    // 通知各玩家当前是第 round 轮，并告知上一轮对手的动作和结果
    notice_msg notice1, notice2;
    notice_msg_init(&notice1);
    notice_msg_init(&notice2);
    notice1.notice.round = notice2.notice.round = round;
    // 保存上轮结果、对手出招
    notice1.notice.last_result = notice2.notice.last_result = \
        round_logs[round - 1].result;
    notice1.notice.last_rival_action = round_logs[round - 1].action2;
    notice2.notice.last_rival_action = round_logs[round - 1].action1;
    printf("裁判通知各玩家当前是第%d轮\n", round);
    while (msgsnd(msg_notice1, &notice1, sizeof(notice_t), 0) == -1);
    while (msgsnd(msg_notice2, &notice2, sizeof(notice_t), 0) == -1);
    // 接收玩家这一轮的出招结果
    move_msg move1, move2;
    int get1 = 0, get2 = 0;  // 是否成功获取玩家出招信息
    time_t start_time = 0;  // 开始时间
    while (!get1 || !get2) {  // 接收玩家这一轮的出招结果
      // 非阻塞地接收数据
      if (!get1 && msgrcv(msg_rec1, &move1, sizeof(move_t),
                          0, IPC_NOWAIT) != -1) {
        if (move1.move.round != round) {  // 错误轮次
          printf("裁判收到玩家1错误轮次的出招：当前是第%d轮，玩家1发送的是第%d轮\n",
                 round, move1.move.round);
        } else {
          get1 = 1;
          printf("裁判收到玩家1第%d轮出招 %s\n", round, action_string(move1.move.action));
          if (start_time == 0) {
            start_time = time(NULL);  // 设定开始时间
          }
        }
      }
      if (!get2 && msgrcv(msg_rec2, &move2, sizeof(move_t),
                          0, IPC_NOWAIT) != -1) {
        if (move2.move.round != round) {  // 错误轮次
          printf("裁判收到玩家2错误轮次的出招：当前是第%d轮，玩家2发送的是第%d轮\n",
                 round, move2.move.round);
        } else {
          get2 = 1;
          printf("裁判收到玩家2第%d轮出招 %s\n", round, action_string(move2.move.action));
          if (start_time == 0) {
            start_time = time(NULL);  // 记录第一个发送的时间
          }
        }
      }
      if (start_time != 0 && (time(NULL) - start_time > INTERVAL)) {
        break;    // 如果超时停止接收
      }
    }
    if (!get1) {  // 覆盖掉错误的出招结果
      move_msg_init(&move1, 1);
      move1.move.round = round;
    }
    if (!get2) {  // 覆盖掉错误的出招结果
      move_msg_init(&move2, 2);
      move2.move.round = round;
    }
    // 判定并记录结果，进行下一轮
    round_logs[round].round = round;
    round_logs[round].action1 = move1.move.action;
    round_logs[round].action2 = move2.move.action;
    round_logs[round].result =  // 判定结果
        result_announce(move1.move.action, move2.move.action);
    show_round(&round_logs[round]);  // 显示结果
  }
  // 循环结束，通知玩家游戏结束
  notice_msg notice1, notice2;
  notice_msg_init(&notice1);
  notice_msg_init(&notice2);
  notice1.notice.round = notice2.notice.round = -1;  // 如果轮数为-1，玩家进程会退出
  printf("裁判通知玩家游戏结束\n");
  while (msgsnd(msg_notice1, &notice1, sizeof(notice_t), 0) == -1);
  while (msgsnd(msg_notice2, &notice2, sizeof(notice_t), 0) == -1);
  // 统计，保存结果的文件为 result.txt
  statistics(round_logs, rounds, "result.txt");
  free(round_logs);
}

// 玩家
void run_player(int uid, int msg_notice, int msg_snd) {
  pid_t pid = fork();  // 创建新进程
  if (pid < 0) {
    fprintf(stderr, "Fork player 失败！\n");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    // 设置随机数种子
    unsigned seed = (unsigned) (time(NULL) + msg_notice) * (msg_snd + 2);
    if (uid % 2) { seed = -seed; }  // 尽量拉开两玩家的差距
    srand(seed);
    for (;;) {
      fflush(stdout);  // 刷新标准输出缓冲区
      notice_msg notice_m;      // 玩家接收来自裁判的出招消息
      notice_msg_init(&notice_m);
      while (msgrcv(msg_notice, &notice_m, sizeof(notice_t), 0, 0) == -1);
      if (notice_m.notice.round < 0) {  // 如果轮数为<0，玩家进程会退出
        printf("玩家%d进程结束\n", uid);
        exit(EXIT_SUCCESS);
      }
      printf("玩家%d收到第%d轮出招信号\n", uid, notice_m.notice.round);
      // 玩家出招
      move_msg move_m;
      move_msg_init(&move_m, uid);
      move_m.move.round = notice_m.notice.round;
      move_m.move.action = random_action(&notice_m.notice);  // 随机出招
      printf("玩家%d发送第%d轮出招 %s\n", uid, move_m.move.round,
             action_string(move_m.move.action));
      if (msgsnd(msg_snd, &move_m, sizeof(move_t), 0) == -1) {
        fprintf(stderr, "玩家%d发送第%d轮出招信息失败！\n", uid, move_m.move.round);
      }
    }
  }
}

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "请提供一个命令行参数作为比赛轮数！\n");
    exit(EXIT_FAILURE);
  }
  // 初始化消息队列：分别是两个玩家的提醒消息和出招消息
  int key11 = 0x1f, key12 = 0x2f, key21 = 0x3f, key22 = 0x4f;
  int msg_notice1, msg_notice2, msg_rec1, msg_rec2;
  if ((msg_notice1 = msgget(key11, IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "提醒消息队列1创建失败！\n");
    exit(EXIT_FAILURE);
  }
  if ((msg_notice2 = msgget(key12, IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "提醒消息队列2创建失败！\n");
    exit(EXIT_FAILURE);
  }
  if ((msg_rec1 = msgget(key21, IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "出招消息队列1创建失败！\n");
    exit(EXIT_FAILURE);
  }
  if ((msg_rec2 = msgget(key22, IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "出招消息队列2创建失败！\n");
    exit(EXIT_FAILURE);
  }
  const int rounds = atoi(argv[1]);  // 比赛轮数
  printf("比赛轮数：%d\n", rounds);
  fflush(stdout);
  // 先生成玩家，再运行裁判
  run_player(1, msg_notice1, msg_rec1);
  run_player(2, msg_notice2, msg_rec2);
  run_judgement(msg_notice1, msg_notice2, msg_rec1, msg_rec2, rounds);
  // 等待玩家退出
  wait(NULL);
  wait(NULL);
  // 删除消息队列
  if (msgctl(msg_notice1, IPC_RMID, 0) == -1) {
    fprintf(stderr, "提醒消息队列1删除失败！\n");
  }
  if (msgctl(msg_notice2, IPC_RMID, 0) == -1) {
    fprintf(stderr, "提醒消息队列2删除失败！\n");
  }
  if (msgctl(msg_rec1, IPC_RMID, 0) == -1) {
    fprintf(stderr, "接收消息队列1删除失败！\n");
  }
  if (msgctl(msg_rec2, IPC_RMID, 0) == -1) {
    fprintf(stderr, "接收消息队列2删除失败！\n");
  }
  return 0;
}