#ifndef EXP03__GAME_H_
#define EXP03__GAME_H_

#define TYPE_NOTICE 100L
#define TYPE_MOVE 200L
#define INTERVAL 10  // 每轮超时
#define PORT 9000  // Socket 端口
#define BUFFER_SIZE 32 // Socket 缓冲区大小


typedef enum {  // 动作
  ACT_NONE, // 无动作
  ACT_ROCK, // 石头
  ACT_PAPER, // 布
  ACT_SCISSORS // 剪刀
} action_t;

typedef enum {  // 结果
  RES_P1_VICTORY,  // 玩家1胜利（玩家2失败）
  RES_DRAW,   // 平局
  RES_P1_DEFEAT  // 玩家2胜利（玩家1失败）
} result_t;

const char *action_string(action_t action);
const char *result_string(result_t result);

typedef struct {  // 裁判发给玩家的信息
  int round;  // 当前是第几轮
  action_t last_rival_action;  // 上一轮对手的动作
  result_t last_result;  // 上一轮结果
} notice_t;

typedef struct {  // 送往消息队列的封装
  notice_t notice;
  long type;
} notice_msg;

typedef struct {  // 玩家发给裁判的信息
  int uid;  // 用户ID
  int round;  // 第几轮的动作, Socket 中轮数<0为请求轮数
  action_t action;  // 出招动作
} move_t;

typedef struct {  // 送往消息队列的封装
  move_t move;
  long type;
} move_msg;

void notice_msg_init(notice_msg *msg);
void move_init(move_t *move, int uid);
void move_msg_init(move_msg *msg, int uid);

typedef struct {  // 历史记录
  int round;  // 轮数
  action_t action1, action2;  // 玩家1、2的动作
  result_t result;  // 结果
} round_logs_t;

result_t result_announce(action_t action1, action_t action2);
void show_round(round_logs_t *log);
void statistics(const round_logs_t *result_list,
                int rounds,
                const char *result_file);
action_t random_action(notice_t *history);

#endif //EXP03__GAME_H_
