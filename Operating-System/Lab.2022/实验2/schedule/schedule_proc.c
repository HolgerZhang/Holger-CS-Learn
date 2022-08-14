//
// Created by 张昊 on 2022/3/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule_proc.h"

// 进程级实现

/**
 * @brief 创建进程
 * @param pid PID
 * @param name 进程名称
 * @param priority 优先级
 * @param arrive 到达时间
 * @param interval 区间时间
 * @return 若创建成功，返回进程PCB；否则为NULL
 */
pcb *create_proc(unsigned pid,
                 const char *name,
                 int priority,
                 long arrive,
                 long interval) {
  pcb *proc = (pcb *) malloc(sizeof(pcb));
  if (NULL != proc) {
    proc->states = PROC_STATE_CREATED;
    proc->pid = pid;
    strcpy(proc->name, name);
    proc->priority = priority;
    proc->arrive_time = arrive;
    proc->interval_time = interval;
    proc->finish_time = -1;
    proc->next_proc = NULL;
  }
  return proc;
}

/**
 * @brief 回收进程资源
 * @param proc 进程PCB
 * @return 若PCB不为NULL，返回链表后一个进程PCB指针；否则为NULL
 */
pcb *destroy_proc(pcb *proc) {
  pcb *next_proc = NULL;
  if (NULL != proc) {
    next_proc = proc->next_proc;
    free(proc);
  }
  return next_proc;
}

/**
 * @brief 显示进程信息
 * @param proc 进程PCB
 */
void display_proc(pcb *proc) {
  if (NULL != proc) {
    printf("PID: %-d\t PROCESS: %-s\t PRIOR: %-d\t ",
           proc->pid,
           proc->name,
           proc->priority);
    char *states_string;
    switch (proc->states) {
      case PROC_STATE_CREATED:
        states_string = "CREATED";
        break;
      case PROC_STATE_READY:
        states_string = "READY";
        break;
      case PROC_STATE_RUNNING:
        states_string = "RUNNING";
        break;
      case PROC_STATE_WAIT:
        states_string = "WAIT";
        break;
      case PROC_STATE_FINISH:
        states_string = "FINISH";
        break;
    }
    printf("STATES: %-8s\t Arrive: %-ld\t Interval: %-ld\t "
           "Finish: %-ld\n", states_string, proc->arrive_time,
           proc->interval_time, proc->finish_time);
  }
}

/**
 * @brief 运行空闲进程
 * @param interval 持续时长
 */
void idle_proc(long interval) {
  // running IDLE process ${interval} second(s)
  machine_time += interval;
  printf("CPU空闲时长：%ld\n", interval);
}


// 队列级实现

pcb *created = NULL;  // 新建队列
pcb *ready = NULL;  // 就绪队列
pcb *ready_tail = NULL;  // 就绪队列尾
long machine_time = 0;  // 处理机时间

/**
 * @brief 就绪队列入队
 * @param proc 进程PCB
 */
void push_ready(pcb *proc) {
  if (NULL == proc || 0 == proc->interval_time) {  // 空进程和区间为0的进程不会加入就绪队列
    return;
  }
  proc->next_proc = NULL;
  proc->states = PROC_STATE_READY;  // 设置状态为就绪
  if (NULL == ready) {  // 就绪队列为空，同时设置队尾指针
    ready = proc;
    ready_tail = proc;
  } else {  // 向队尾指针后追加，并调整队尾指针
    ready_tail->next_proc = proc;
    ready_tail = ready_tail->next_proc;
  }
}

/**
 * @brief 就绪队列出队
 * @return 若就绪队列为空返回NULL；否则返回第一个进程
 */
pcb *pop_ready() {
  if (ready == NULL) {
    return NULL;
  }
  pcb *proc = ready;
  ready = ready->next_proc;
  proc->next_proc = NULL;
  if (proc == ready_tail) {  // 若就绪队列只有一个进程（队首队尾为同一个进程）
    ready_tail = NULL;  // 出队时队尾指针置空
  }
  return proc;
}

/**
 * @brief 【排序辅助函数】找中点，拆分链表
 * @param head 进程链表
 * @return 第二部分的链表首元素
 */
pcb *sort_list_search_mid(pcb *head) {
  pcb *fast = head, *slow = head;
  pcb *mid = NULL, *mid_after = NULL;
  while (NULL != fast && NULL != fast->next_proc
      && NULL != fast->next_proc->next_proc) {
    fast = fast->next_proc->next_proc;
    slow = slow->next_proc;
  }
  mid = slow;
  mid_after = mid->next_proc;
  mid->next_proc = NULL; // 将链表一分为二
  return mid_after;
}

/**
 * @brief 【排序辅助函数】合并两个有序链表
 * @param left 有序链表1
 * @param right 有序链表2
 * @param comparable 比较两PCB的回调函数
 * @return 合并后的头指针
 */
pcb *sort_list_merge(pcb *left, pcb *right, pcb_comparable_t comparable) {
  pcb *p1 = left, *p2 = right;
  pcb result, *p3 = &result;  // 不包含数据的头节点
  // p3在合并过程中，始终指向合并链表的当前尾节点
  while (NULL != p1 && NULL != p2) {
    if (comparable(p1, p2) <= 0) {
      p3->next_proc = p1;
      p3 = p1;
      p1 = p1->next_proc;
    } else {
      p3->next_proc = p2;
      p3 = p2;
      p2 = p2->next_proc;
    }
  }
  if (NULL == p2) {
    p3->next_proc = p1;
  }
  if (NULL == p1) {
    p3->next_proc = p2;
  }
  left = result.next_proc;
  return left;
}

/**
 * @brief 对进程队列排序（归并排序）
 * @note 排序后需要调整链表的尾指针（如果有的话）
 * @param head 进程链表
 * @param comparable 比较两PCB的回调函数
 * @return 若进程链表不为NULL，返回排序后的链表首指针；否则为NULL
 */
pcb *sort_list(pcb *head, pcb_comparable_t comparable) {
  if (NULL == head || NULL == head->next_proc) { // 递归终止条件: 链表长度小于等于1
    return head;
  }
  pcb *left, *right;
  left = head;
  right = sort_list_search_mid(head);
  left = sort_list(left, comparable);
  right = sort_list(right, comparable);
  head = sort_list_merge(left, right, comparable);
  return head;
}

/**
 * @brief 重置就绪队列队尾指针
 */
void reset_ready_tail() {
  if (NULL == ready) {
    ready_tail = NULL;
    return;
  }
  pcb *proc = ready;
  while (NULL != proc) {
    ready_tail = proc;
    proc = proc->next_proc;
  }
}

/**
 * @brief 将当前时间点以及之前到达的PCB加入到就绪队列
 */
void new_proc_ready() {
  pcb *p;
  while (NULL != created && created->arrive_time <= machine_time) {
    p = created;
    created = created->next_proc;
    push_ready(p);
  }
}

/**
 * @brief 显示就绪队列
 */
void display_ready() {
  if (NULL != ready) {
    printf("\n*** 就绪队列 (在处理机时间%ld) ***\n", machine_time);
  } else {
    printf("\n*** 就绪队列为空 (在处理机时间%ld) ***\n", machine_time);
  }
  pcb *p = ready;
  int count = 0;
  while (NULL != p) {
    display_proc(p);
    p = p->next_proc;
    count++;
  }
  printf("*** 就绪队列进程数量 %d ***\n\n", count);
}