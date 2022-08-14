#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "game.h"

// 裁判
void run_judgement(int fd, const int rounds) {
  // server socket 配置
  struct sockaddr_in peer_addr;
  socklen_t peer_size;
  ssize_t recv_num, send_num;  // 发送和接收的字节数
  char recv_buff[BUFFER_SIZE]; // 接收缓冲区
  // 历史记录
  round_logs_t *round_logs = malloc((rounds + 1) * sizeof(round_logs_t));
  round_logs[0].action1 = round_logs[0].action2 = ACT_NONE;  // 第0条记录设置为空
  round_logs[0].result = RES_DRAW;
  round_logs[1].action1 = round_logs[1].action2 = ACT_NONE;  // 第1条记录设置为空
  int round = 1;  // 当前游戏轮数
  int client1_bye = 0, client2_bye = 0;  // 是否通知玩家进程退出
  int get1 = 0, get2 = 0;  // 是否成功获取玩家出招信息
  time_t start_time = 0;  // 开始时间
  for (;;) {
    fflush(stdout);  // 刷新标准输出缓冲区
    peer_size = sizeof(peer_addr);
    bzero(recv_buff, sizeof(recv_buff));  // 清空接收缓冲区
    do {    // 非阻塞地接收数据
      recv_num = recvfrom(fd, recv_buff, sizeof(recv_buff), MSG_DONTWAIT,
                          (struct sockaddr *) &peer_addr, &peer_size);
      // printf("裁判收到%zd字节数据: %s\n", recv_num, recv_buff);
    } while (recv_num <= 0  // 忙等，直到成功接收或超时
        || (start_time != 0 && (time(NULL) - start_time > INTERVAL)));
    if (recv_num > 0) {  // 处理数据
      move_t *move = (move_t *) recv_buff;  // client发送的数据都是move_t结构体
      if (move->uid != 1 && move->uid != 2) {  // 只认定uid=1或2的玩家
        printf("未知的uid %d，忽略\n", move->uid);
        continue;
      }
      if (move->round < 0) {  // round<0, client请求轮数信息
        notice_t notice;  // 要发送的数据
        if (round <= rounds) {
          // 通知该玩家当前是第 round 轮，并告知上一轮对手的动作和结果
          // printf("裁判通知玩家%d当前是第%d轮\n", move->uid, round);
          notice.round = round;
          // 保存上轮结果、对手出招
          notice.last_result = round_logs[round - 1].result;
          notice.last_rival_action = (move->uid == 1) ?
                                     round_logs[round - 1].action2 :
                                     round_logs[round - 1].action1;
        } else {  // 游戏已经结束，通知玩家进程退出
          printf("裁判通知玩家%d退出\n", move->uid);
          notice.round = -1;  // 如果返回的轮数<0，玩家进程会退出
          if (move->uid == 1) client1_bye = 1;  // 已通知玩家进程退出
          else client2_bye = 1;
        }
        send_num = sendto(fd, &notice, sizeof(notice_t), 0,
                          (struct sockaddr *) &peer_addr, peer_size);
        // printf("裁判发送%zd字节数据\n", send_num);
      } else {  // round>0, 接收玩家这一轮的出招结果
        if (move->round != round) {  // 错误轮次
          printf("裁判收到玩家%d错误轮次的出招：当前是第%d轮，玩家发送的是第%d轮\n",
                 move->uid, round, move->round);
        } else {
          if (move->uid == 1) {
            get1 = 1;
            round_logs[round].action1 = move->action;
          } else if (move->uid == 2) {
            get2 = 1;
            round_logs[round].action2 = move->action;
          }
          printf("裁判收到玩家%d第%d轮出招 %s\n", move->uid, round,
                 action_string(move->action));
          if (start_time == 0) {
            start_time = time(NULL);  // 记录第一个发送的时间
          }
        }
      }
    }
    if (client1_bye && client2_bye) {
      break;  // 已经通知所有玩家进程退出, 裁判可以停止接收数据了
    }
    if ((get1 && get2)  // 收到了两个玩家出招结果，或者超时，判定结果，进行下一轮
        || (start_time != 0 && (time(NULL) - start_time > INTERVAL))) {
      round_logs[round].round = round;
      round_logs[round].result = // 判定结果
          result_announce(round_logs[round].action1, round_logs[round].action2);
      show_round(&round_logs[round]);  // 显示结果
      round++;  // 进行下一轮
      get1 = get2 = 0;
      start_time = 0;
      if (round <= rounds) {
        printf("裁判：当前是第%d轮\n", round);
        round_logs[round].action1 = ACT_NONE;
        round_logs[round].action2 = ACT_NONE;
      }
    }
  }
  // 统计，保存结果的文件为 result-server.txt
  statistics(round_logs, rounds, "result-server.txt");
  free(round_logs);
}

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "请提供一个命令行参数作为比赛轮数！\n");
    exit(EXIT_FAILURE);
  }
  // 创建 UDP Socket
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    fprintf(stderr, "socket error\n");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // 绑定监听端口
  printf("裁判：监听 %d 端口\n", PORT);
  if (bind(fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    fprintf(stderr, "bind error\n");
    exit(EXIT_FAILURE);
  }
  const int rounds = atoi(argv[1]);  // 比赛轮数
  printf("比赛轮数：%d\n", rounds);
  run_judgement(fd, rounds);  // 运行裁判进程
  // 关闭 socket
  close(fd);
  return 0;
}