//
// Created by 张昊 on 2022/3/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t child_pid = fork();  // 创建子进程，获取 PID
  if (child_pid == 0) { // 当前处在子进程中
    int ret;  // 子进程返回值
    printf("[CHILD] 当前处于子进程中\n");
    printf("[CHILD] 子进程 PID = %d\n", getpid());
    printf("[CHILD] 父进程 PID = %d\n", getppid());
    printf("[CHILD] 子进程睡眠 1 秒...\n");
    sleep(1);
    printf("[CHILD] 请输入子进程执行完毕后的返回值(0-255): ");
    scanf("%d", &ret);
    printf("[CHILD] 子进程即将退出\n");
    exit(ret);  // 退出子进程
  } else if (child_pid > 0) {  // 当前处在父进程中, fork() 返回子进程 PID
    int status;  // 子进程向父进程提供的退出状态
    printf("[PARENT] 当前处于父进程中\n");
    printf("[PARENT] 父进程 PID = %d\n", getpid());
    printf("[PARENT] 子进程 PID = %d\n", child_pid);
    printf("[PARENT] 父进程将等待子进程运行结束...\n");
    wait(&status);
    printf("[PARENT] 子进程的返回值: %d\n", WEXITSTATUS(status));
    printf("[PARENT] 父进程即将退出\n");
    exit(EXIT_SUCCESS);
  } else {  // fork 失败
    fprintf(stderr, "fork 失败！\n");
    exit(EXIT_FAILURE);
  }
}