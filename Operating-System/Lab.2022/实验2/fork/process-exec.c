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
    printf("[CHILD] 当前处于子进程中\n");
    // ls 命令所需的参数, 最后一个元素必须是NULL
    char *argv[] = {"ls", "-l", "-a", "-h", NULL};
    if (-1 == execvp("/usr/bin/ls", argv)) {  // 执行命令 ls
      // 执行不成功会进入分支，否则子进程会exit
      fprintf(stderr, "[CHILD] 子进程执行失败！\n");
      exit(EXIT_FAILURE);
    }
  } else if (child_pid > 0) {  // 当前处在父进程中, fork() 返回子进程 PID
    int status;  // 子进程向父进程提供的退出状态
    printf("[PARENT] 当前处于父进程中\n");
    printf("[PARENT] 父进程将等待子进程运行结束...\n");
    wait(&status);
    printf("[PARENT] 子进程的返回值: %d\n", WEXITSTATUS(status));
    printf("[PARENT] 父进程即将退出\n");
    exit(0);
  } else {  // fork 失败
    fprintf(stderr, "fork 失败！\n");
    exit(EXIT_FAILURE);
  }
}