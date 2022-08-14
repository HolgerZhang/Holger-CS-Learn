#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "game.h"

// 玩家
void run_player(int uid, int fd) {
  // client socket 配置
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1
  ssize_t send_num, recv_num;  // 发送和接收的字节数
  char recv_buff[BUFFER_SIZE]; // 接收缓冲区
  // 设置随机数种子
  unsigned seed = (unsigned) (time(NULL) + fd) * (uid + 2);
  if (uid % 2) { seed = -seed; }  // 尽量拉开两玩家的差距
  srand(seed);
  int round;  // 记录游戏轮数
  for (;;) {
    fflush(stdout);  // 刷新标准输出缓冲区
    bzero(recv_buff, sizeof(recv_buff));  // 清空接收缓冲区
    move_t move;  // 向 server 发送的数据
    move_init(&move, uid);  // round = -1，询问裁判当前轮数
    int retry = 0;  // 未收到数据重发次数
    do {  // 玩家询问裁判当前轮数
      send_num = sendto(fd, &move, sizeof(move_t), 0,
                        (struct sockaddr *) &server_addr, sizeof(server_addr));
      // printf("玩家%d询问裁判当前轮数，发送%zd字节\n", uid, send_num);
      recv_num = recvfrom(fd, recv_buff, sizeof(recv_buff), MSG_DONTWAIT,
                          NULL, NULL);
      // printf("玩家%d收到%zd字节\n", uid, recv_num);
      if (recv_num <= 0) {  // 未收到数据重发请求，中间暂时休眠
        usleep((100 + retry * 100) % (INTERVAL * 1000));
        retry++;
      } else {
        retry = 0;  // 重置重发次数
      }
    } while (send_num <= 0 || recv_num <= 0);  // 直到成功发送或接收
    // server 返回内容为 notice_t 结构体
    notice_t *notice = (notice_t *) recv_buff;  // server发送的都是notice_t数据
    if (notice->round < 0) {  // 如果轮数<0，玩家进程会退出
      printf("玩家%d进程即将结束\n", uid);
      break;
    }
    if (round != notice->round) { // 轮数更新，玩家出招
      printf("玩家%d收到第%d轮出招信号\n", uid, notice->round);
      round = move.round = notice->round;  // 更新游戏轮数
      move.action = random_action(notice);  // 随机出招
      send_num = sendto(fd, &move, sizeof(move_t), 0,
                        (struct sockaddr *) &server_addr, sizeof(server_addr));
      printf("玩家%d发送第%d轮出招 %s，发送%zd字节\n", uid, move.round,
             action_string(move.action), send_num);
    } else {  // 出招轮数不变，展示休眠
      // printf("玩家%d：出招轮数不变\n", uid);
      usleep(300);
    }
  }
}

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "请提供一个命令行参数作为玩家ID！\n");
    exit(EXIT_FAILURE);
  }
  // UDP Socket
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    fprintf(stderr, "socket error\n");
    exit(EXIT_FAILURE);
  }
  int uid = atoi(argv[1]);  // 玩家ID
  run_player(uid, fd);  // 运行玩家进程
  // 关闭 socket
  close(fd);
  return 0;
}