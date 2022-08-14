#include <stdio.h>
#include <stdlib.h>
#include "game.h"

const char *action_string(action_t action) {  // 输出动作
  switch (action) {
    case ACT_ROCK:
      return "石头";
    case ACT_SCISSORS:
      return "剪刀";
    case ACT_PAPER:
      return "布";
    default:
      return "超时";
  }
}
const char *result_string(result_t result) {  // 输出结果
  switch (result) {
    case RES_DRAW:
      return "平局";
    case RES_P1_VICTORY:
      return "玩家1胜利";
    case RES_P1_DEFEAT:
      return "玩家2胜利";
  }
}

void notice_msg_init(notice_msg *msg) {  // 初始化裁判发给玩家的信息
  msg->type = TYPE_NOTICE;
  msg->notice.round = 0;
  msg->notice.last_rival_action = ACT_NONE;
  msg->notice.last_result = RES_DRAW;
}

void move_init(move_t *move, int uid) {  // 初始化玩家发给裁判的信息
  move->uid = uid;
  move->round = -1;
  move->action = ACT_NONE;
}

void move_msg_init(move_msg *msg, int uid) {  // 初始化送往消息队列的封装
  msg->type = TYPE_MOVE;
  move_init(&msg->move, uid);
}

// 出招结果的判断
result_t result_announce(action_t action1, action_t action2) {
  if (action1 != action2) {
    if (action1 == ACT_SCISSORS && action2 == ACT_ROCK) return RES_P1_DEFEAT;
    if (action1 == ACT_SCISSORS && action2 == ACT_PAPER) return RES_P1_VICTORY;
    if (action1 == ACT_ROCK && action2 == ACT_SCISSORS) return RES_P1_VICTORY;
    if (action1 == ACT_ROCK && action2 == ACT_PAPER) return RES_P1_DEFEAT;
    if (action1 == ACT_PAPER && action2 == ACT_SCISSORS) return RES_P1_DEFEAT;
    if (action1 == ACT_PAPER && action2 == ACT_ROCK) return RES_P1_VICTORY;
    if (action1 == ACT_NONE) return RES_P1_DEFEAT;
    if (action2 == ACT_NONE) return RES_P1_VICTORY;
  }
  return RES_DRAW;
}

// 展示每轮结果
void show_round(round_logs_t *log) {
  printf("第%d轮玩家1出招 %s ，玩家2出招 %s ，结果为%s\n",
         log->round, action_string(log->action1),
         action_string(log->action2), result_string(log->result));
}

// 统计胜负
void statistics(const round_logs_t *result_list,
                int rounds,
                const char *result_file) {  // 将每轮的胜负结果存入文件
  int player1 = 0, player2 = 0, draw = 0;
  FILE *fin;
  if ((fin = fopen(result_file, "w")) == NULL) {
    fprintf(stderr, "文件 '%s' 无法打开\n", result_file);
    return;
  }
  printf("\n统计信息：\n");
  for (int i = 1; i <= rounds; i++) {
    fprintf(fin, "NO.%d: %s\n", i, result_string(result_list[i].result));
    printf("NO.%d: %s\n", i, result_string(result_list[i].result));
    switch (result_list[i].result) {
      case RES_P1_VICTORY: {
        player1++;
        break;
      }
      case RES_DRAW: {
        draw++;
        break;
      }
      case RES_P1_DEFEAT: {
        player2++;
        break;
      }
    }
  }
  printf("\n玩家1胜利次数：%d \n玩家2胜利次数：%d \n平局次数：%d\n",
         player1, player2, draw);
  fprintf(fin, "\n玩家1胜利次数：%d \n玩家2胜利次数：%d \n平局次数：%d\n",
          player1, player2, draw);
  printf("最终胜利：%s\n\n",
         player1 == player2 ? "平局" : player1 > player2 ? "玩家1" : "玩家2");
  fprintf(fin, "最终胜利：%s\n",
          player1 == player2 ? "平局" : player1 > player2 ? "玩家1" : "玩家2");
  fclose(fin);
}

// 随机出招
action_t random_action(notice_t *history) {
  int r = rand() % 3;
  if (r == 0) return ACT_PAPER;
  else if (r == 1) return ACT_ROCK;
  else return ACT_SCISSORS;
}