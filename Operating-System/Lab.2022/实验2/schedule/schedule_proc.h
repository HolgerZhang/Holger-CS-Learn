//
// Created by 张昊 on 2022/3/10.
//

#ifndef EXP02__SCHEDULE_PROC_H_
#define EXP02__SCHEDULE_PROC_H_

// 进程级定义

// 进程运行状态
typedef enum states {
  PROC_STATE_CREATED,
  PROC_STATE_READY,
  PROC_STATE_RUNNING,
  PROC_STATE_WAIT,
  PROC_STATE_FINISH
} states_t;
// 进程PCB
typedef struct pcb_t {
  unsigned pid; // PID
  char name[16];  // 进程名称
  states_t states; // 进程的当前状态
  int priority; // 进程优先数
  long arrive_time; // 到达时间
  long interval_time; // 剩余区间时间
  long finish_time;  // 结束时间，-1为尚未结束运行
  struct pcb_t *next_proc; // 所有进程(以PCB的形式)组成的链表
} pcb;
// 创建进程
pcb *create_proc(unsigned pid,
                 const char *name,
                 int priority,
                 long arrive,
                 long interval);
pcb *destroy_proc(pcb *proc);  // 回收进程资源
void display_proc(pcb *proc);  // 显示进程信息
void idle_proc(long interval);  // 运行空闲进程

// 队列级定义

extern pcb *created;  // 新建队列
extern pcb *ready;  // 就绪队列
extern pcb *ready_tail;  // 就绪队列尾
extern long machine_time;  // 处理机时间
void push_ready(pcb *proc);  // 就绪队列入队
pcb *pop_ready();  // 就绪队列出队
typedef long (*pcb_comparable_t)(pcb *, pcb *);  // 比较进程的回调函数类型
pcb *sort_list(pcb *head, pcb_comparable_t comparable);  // 对进程队列排序
void reset_ready_tail();  // 重置就绪队列队尾指针
void new_proc_ready();  // 将当前时间点以及之前到达的PCB加入到就绪队列
void display_ready();   // 显示就绪队列

#endif //EXP02__SCHEDULE_PROC_H_
