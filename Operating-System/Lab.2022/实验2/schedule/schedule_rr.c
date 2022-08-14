//
// Created by 张昊 on 2022/3/10.
//
// RR（时间片轮转）: 每个进程分配一定长度的CPU时间，若仍未运行结束则抢占，并重新加入就绪队列。
// 按照进程请求CPU的先后顺序分配时间片。若某一时刻无进程请求CPU，则处理机进入空闲。
// 若有被抢占的进程和新进程同时要加入就绪队列，则被抢占的进程先加入就绪队列。
// 即，被抢占的进程将改变到达时间为抢占发生的时间，且总是被抢占的进程先加入就绪队列（通过稳定的排序实现）
//

#include <stdio.h>
#include <stdlib.h>
#include "schedule_proc.h"

#define SLICE 20  // 时间片大小

/** 按到达时间比较进程PCB */
long compare_early_arrive(pcb *p1, pcb *p2) {
  return p1->arrive_time - p2->arrive_time;
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
 * @brief 以时间片轮转算法运行进程
 * @param proc 进程PCB
 */
void run(pcb *proc) {
  if (NULL != proc) {
    proc->states = PROC_STATE_RUNNING;  // 设置进程运行状态
    printf("当前正在运行的进程是 %s：\n", proc->name); // 显示当前运行的进程
    display_proc(proc);
    if (proc->interval_time <= SLICE) {  // 剩余区间时间少于或等于一个时间片
      machine_time += proc->interval_time;  // 分配全部区间时间
      printf("进程 %s 运行时间：%ld\n", proc->name, proc->interval_time);
      proc->states = PROC_STATE_FINISH;  // 转为完成
      proc->finish_time = machine_time;
      printf("进程 %s 运行结束：\n", proc->name);
      display_proc(proc);
    } else {  // 只分配一个时间片
      machine_time += SLICE;
      proc->interval_time -= SLICE;
      printf("进程 %s 运行时间：%d\n", proc->name, SLICE);
      proc->arrive_time = machine_time;  // 修改到达时间
      push_ready(proc);  // 加入就绪队列
      printf("进程 %s 被抢占\n", proc->name);
    }
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
    // 按到达时间对就绪队列进行排序（因为新进程可能是在一个时间片内到达）
    ready = sort_list(ready, compare_early_arrive);
    reset_ready_tail();
    display_ready();
    if (NULL == ready) { // 若就绪队列为空，说明当前时间CPU空闲
      idle_proc(created->arrive_time - machine_time);
      continue;
    }
    proc = pop_ready();  // 就绪队列队首出队
    run(proc);  // 运行一个时间片
    if (PROC_STATE_FINISH == proc->states) {  // 若运行结束，回收进程资源
      destroy_proc(proc);
    }
  }
  printf("\n*** 所有进程调度完成 ***\n");
  return EXIT_SUCCESS;
}
