//
// Created by 张昊 on 2022/3/10.
//
// SRTF（最短剩余时间优先）: 每次调度下次运行CPU时间最短的进程。
// 若有比当前进程的剩余时间更短（严格小于）的进程到达时，抢占。（被抢占的进程不改变到达时间）
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
 * @brief 判断新进程是否抢占正在运行的进程，并将新进程加入就绪队列：
 * 若可以抢占，则正在运行的进程和新进程均加入就绪队列，均设置为就绪状态；
 * 否则，仅将新进程加入就绪队列，设置为就绪状态。
 * 不会对就绪队列进行排序，原因是main函数每次循环都会执行排序。
 * @param running_proc 正在运行的进程的PCB
 * @param new_proc 新进程的PCB
 * @return 0 - 不会抢占；!0 - 会抢占
 */
int interrupt(pcb *running_proc, pcb *new_proc) {
  if (new_proc->interval_time < running_proc->interval_time) {
    // 比当前进程的剩余时间更短（严格小于）的进程到达，会抢占
    push_ready(new_proc);
    printf("有新进程 %s 到达：\n", new_proc->name);
    display_proc(new_proc);
    push_ready(running_proc);
    printf("当前进程 %s 被抢占\n", running_proc->name);
    return !0;
  } else {  // 不会抢占
    push_ready(new_proc);
    printf("有新进程 %s 到达：\n", new_proc->name);
    display_proc(new_proc);
    return 0;
  }
}

/**
 * @brief 每运行一个CPU时间后检查新建队列中是否有新进程到达，若有则转向"中断"判断是否抢占
 * @param proc 进程PCB
 */
void run(pcb *proc) {
  if (NULL != proc) {
    proc->states = PROC_STATE_RUNNING;  // 设置进程运行状态
    printf("当前正在运行的进程是 %s：\n", proc->name); // 显示当前运行的进程
    display_proc(proc);
    long interval = 0;
    while (proc->interval_time > 0) {
      proc->interval_time--;  // 运行一个CPU时间
      machine_time++;
      interval++;
      if (NULL != created && created->arrive_time <= machine_time) { // 有新进程到达
        pcb *new_proc = created;
        created = created->next_proc;
        new_proc->next_proc = NULL;
        if (0 != interrupt(proc, new_proc)) {
          break;
        }
      }
    }
    printf("进程 %s 运行时间：%ld\n", proc->name, interval);
    if (proc->interval_time == 0) {
      proc->states = PROC_STATE_FINISH;  // 结束
      proc->finish_time = machine_time;
      printf("进程 %s 运行结束：\n", proc->name);
      display_proc(proc);
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
    if (PROC_STATE_FINISH == proc->states) {  // 若运行结束，回收进程资源
      destroy_proc(proc);
    }
  }
  printf("\n*** 所有进程调度完成 ***\n");
  return EXIT_SUCCESS;
}
