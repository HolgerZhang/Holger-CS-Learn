//
// Created by 张昊 on 2022/3/10.
//
// SJF（短作业优先）: 每次调度下次运行CPU时间最短的进程，非抢占。
// 若某一时刻无进程请求CPU，则处理机进入空闲。
//

#include <stdio.h>
#include <stdlib.h>
#include "schedule_proc.h"

/** 按到达时间比较进程PCB */
long compare_early_arrive(pcb *p1, pcb *p2) {
  return p1->arrive_time - p2->arrive_time;
}

/** 按区间时间比较进程PCB */
long compare_shortest_job(pcb *p1, pcb *p2) {
  return p1->interval_time - p2->interval_time;
}

/** 进程读取函数 */
int initialize(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (NULL == fp) {
    return EXIT_FAILURE;
  }
  int count;
  pcb *p = NULL;
  fscanf(fp, "%d", &count);
  for (unsigned pid = 1; pid <= count; ++pid) {
    char name[16];
    long arrive, interval;
    fscanf(fp, "%s %ld %ld", name, &arrive, &interval);
    if (NULL == created) {
      created = create_proc(pid, name, 1, arrive, interval);  // 在新建队列等候
      p = created;
    } else {
      p->next_proc = create_proc(pid, name, 1, arrive, interval);
      p = p->next_proc;
    }
  }
  created = sort_list(created, compare_early_arrive);  // 按到达时间排序
  return EXIT_SUCCESS;
}

/**
 * @brief 以SJF算法运行进程
 * @param proc 进程PCB
 */
void run(pcb *proc) {
  if (NULL != proc) {
    proc->states = PROC_STATE_RUNNING;  // 设置进程运行状态
    printf("当前正在运行的进程是 %s：\n", proc->name); // 显示当前运行的进程
    display_proc(proc);
    machine_time += proc->interval_time;
    printf("进程 %s 运行时间：%ld\n", proc->name, proc->interval_time);
    proc->states = PROC_STATE_FINISH;  // 结束
    proc->finish_time = machine_time;
    printf("进程 %s 运行结束：\n", proc->name);
    display_proc(proc);
  }
}

int main(int argc, const char **argv) {
  if (argc != 2) {
    fprintf(stderr, "请提供一个命令行参数作为被调度进程信息！\n");
    return EXIT_FAILURE;
  }
  if (EXIT_SUCCESS != initialize(argv[1])) {
    fprintf(stderr, "文件读取失败！\n");
    return EXIT_FAILURE;
  }
  pcb *proc = NULL;
  while (NULL != ready || NULL != created) {  // 只有两队列均不为空才调度完成
    new_proc_ready();  // 将当前时间点以及之前到达的PCB加入到就绪队列
    // 按作业长短对就绪队列进行排序
    ready = sort_list(ready, compare_shortest_job);
    reset_ready_tail();
    display_ready();
    if (NULL == ready) { // 若就绪队列为空，说明当前时间CPU空闲
      idle_proc(created->arrive_time - machine_time);
      continue;
    }
    proc = pop_ready();  // 就绪队列队首出队
    run(proc);  // 运行
    destroy_proc(proc);  // 回收进程资源
  }
  printf("\n*** 所有进程调度完成 ***\n");
  return EXIT_SUCCESS;
}