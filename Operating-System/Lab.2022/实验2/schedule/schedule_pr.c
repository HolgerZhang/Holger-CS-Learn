//
// Created by 张昊 on 2022/3/10.
//
// PR（动态优先数）: 假定低优先数，高优先级。每次调度优先数最大的进程。
// 被调度的进程只能运行一个CPU时间，运行后若未结束，将优先数+1（即优先级降低1）。
// 如果出现优先数一样大的，则优先调度到达时间小的。（重新加入就绪队列的进程不改变到达时间）
// 若有比当前进程的优先数更大（严格大于）的进程到达时，抢占。
// 若某一时刻无进程请求CPU，则处理机进入空闲。
//

#include <stdio.h>
#include <stdlib.h>
#include "schedule_proc.h"

/** 按到达时间比较进程PCB */
long compare_early_arrive(pcb *p1, pcb *p2) {
  return p1->arrive_time - p2->arrive_time;
}

/** 按优先数比较进程PCB */
long compare_minimal_priority(pcb *p1, pcb *p2) {
  if (p1->priority == p2->priority) {
    return compare_early_arrive(p1, p2);
  }
  return p1->priority - p2->priority;
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
    int priority;
    long arrive, interval;
    fscanf(fp, "%s %d %ld %ld", name, &priority, &arrive, &interval);
    if (NULL == created) {
      created = create_proc(pid, name, priority, arrive, interval);  // 在新建队列等候
      p = created;
    } else {
      p->next_proc = create_proc(pid, name, priority, arrive, interval);
      p = p->next_proc;
    }
  }
  created = sort_list(created, compare_early_arrive);  // 按到达时间排序
  return EXIT_SUCCESS;
}

/**
 * @brief PR，仅运行一个CPU时间
 * @param proc 进程PCB
 */
void run(pcb *proc) {
  if (NULL != proc) {
    proc->states = PROC_STATE_RUNNING;  // 设置进程运行状态
    printf("当前正在运行的进程是 %s：\n", proc->name); // 显示当前运行的进程
    display_proc(proc);
    long interval = 1;
    if (NULL == ready && NULL == created) {  // 当前是最后一个进程
      interval = proc->interval_time;  // 运行剩余的CPU时间
      proc->interval_time = 0;
      proc->priority += (int) interval;  // 每运行一个CPU时间，优先数+1
      machine_time += interval;
    } else {
      proc->interval_time--;  // 运行一个CPU时间
      proc->priority++;  // 每运行一个CPU时间，优先数+1
      machine_time++;
    }
    printf("进程 %s 运行时间：%ld，优先级变为：%d\n",
           proc->name, interval, proc->priority);
    if (0 == proc->interval_time) {
      proc->states = PROC_STATE_FINISH;  // 结束
      proc->finish_time = machine_time;
      printf("进程 %s 运行结束：\n", proc->name);
      display_proc(proc);
    } else {
      push_ready(proc);  // 加入就绪队列
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
    // 按优先数对就绪队列进行排序
    ready = sort_list(ready, compare_minimal_priority);
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

