#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 640

typedef struct partition {  //定义分区
  int address, size;
  struct partition *next;
} partition_t;

/*-----函数定义-------*/
int allocate(int size);  // 分配分区
int reclaim(int addr);  // 回收分区
partition_t *first_fit_find(int size);  // 首次适应
partition_t *best_fit_find(int size);  // 最佳适应
partition_t *worst_fit_find(int size);  // 最差适应
void print_partition(partition_t *head);   // 输出已分配分区表或空闲分区
/*-----变量定义-------*/
partition_t *used, *unused;  // used: 已分配分区表 unused: 空闲分区表
char way;  // 定义分配方式：首先适应、最佳适应、最差适应

int main() {
  // 初始化
  partition_t *p;
  char input_cache[256], *input_res;
  p = malloc(sizeof(partition_t));  // 全部为空闲
  p->size = MAX;
  p->address = 0;
  p->next = NULL;
  unused = malloc(sizeof(partition_t));  //建立空闲分区表的初始状态
  unused->size = MAX;
  unused->address = 0;
  unused->next = p;
  used = malloc(sizeof(partition_t));  // 建立已分配分区表的初始状态
  used->size = 0;
  used->address = 0;
  used->next = NULL;
  printf("************ 空闲分区表 ****************\n");
  print_partition(unused);  //输出
  printf("************已分配分区表****************\n");
  print_partition(used);
  do {
    printf("输入分配方式 [首次适应(f)/最佳适应(b)/最差适应(w)]: ");
    fflush(stdout);
    scanf("%s", input_cache);
    fflush(stdin);
    way = input_cache[0];
    //printf("Input %c\n", way);
  } while (tolower(way) != 'f' && tolower(way) != 'b' && tolower(way) != 'w');
  char choose;
  // 循环
  do {
    printf("分配(a)/回收内存(r)/其他字符退出: ");
    fflush(stdout);
    scanf("%s", input_cache);
    fflush(stdin);
    choose = input_cache[0];  // 选择分配或回收
    //printf("Input %c\n", choose);
    if (tolower(choose) == 'a') {  //a为分配
      int size;
      //输入申请空间大小
      printf("输入申请空间大小(KB): ");
      fflush(stdout);
      scanf("%s", input_cache);
      fflush(stdin);
      size = (int) strtol(input_cache, &input_res, 10);
      int addr = allocate(size);  // 调用分配函数分配内存
      if (addr < 0) { // 分配不成功
        printf("申请的空间太大，分配失败！\n\n");
      } else { // 分配成功
        printf("空间分配成功！ADDRESS=%d\n", addr);
        printf("************ 空闲分区表 ****************\n");
        print_partition(unused);  //输出
        printf("************已分配分区表****************\n");
        print_partition(used);
      }
    } else if (tolower(choose) == 'r') {  //回收内存
      int addr, size;
      // 输入回收地址和大小
      printf("输入要回收的内存空间的地址: ");
      fflush(stdout);
      scanf("%s", input_cache);
      fflush(stdin);
      addr = (int) strtol(input_cache, &input_res, 10);
      size = reclaim(addr);
      if (size < 0) { // 回收不成功
        printf("地址不合法，回收失败！\n\n");
      } else { // 分配成功
        printf("空间回收成功！SIZE=%d\n", size);
        printf("************ 空闲分区表 ****************\n");
        print_partition(unused);  //输出
        printf("************已分配分区表****************\n");
        print_partition(used);
      }
    } else {
      printf("程序即将退出！\n");
    }
  } while (tolower(choose) == 'a' || tolower(choose) == 'r');
  // 释放空间
  while (used != NULL) {
    p = used->next;
    free(used);
    used = p;
  }
  while (unused != NULL) {
    p = unused->next;
    free(unused);
    unused = p;
  }
  return 0;
}

// 内存分配函数，查找空闲分区，成功返回地址，失败返回-1
int allocate(int size) {
  if (size > unused->size || size < 0) {
    return -1;  // 申请无效
  }
  partition_t *prev = NULL;
  if (tolower(way) == 'b') {
    prev = best_fit_find(size);  // 最佳适应
  } else if (tolower(way) == 'f') {
    prev = first_fit_find(size);  // 首次适应
  } else if (tolower(way) == 'w') {
    prev = worst_fit_find(size);  // 最差适应
  }
  if (prev == NULL) {  // 没有合适的节点
    return -1;
  }
  partition_t *curr = prev->next;
  // 有合适的节点curr，prev是其前驱节点
  partition_t *block = malloc(sizeof(partition_t));
  block->size = size;
  block->address = curr->address;
  // 修改unused
  if (curr->size == size) {  // 若节点大小等于申请大小则完全分配
    prev->next = curr->next;
    free(curr);
  } else {  // 大于申请空间则截取相应大小分配
    curr->size -= size;
    curr->address += size;
  }
  unused->size -= size;
  // 修改used（头插法）
  block->next = used->next;
  used->next = block;
  used->size += size;
  return block->address;
}

// 内存回收函数，成功返回释放的空间大小，失败返回-1
int reclaim(int addr) {
  // 检查地址是否在已分配分区表中出现
  // 若有则从表中删除该项，并获取相应分区块指针
  partition_t *prev = used, *curr = used->next;
  while (curr != NULL) {
    if (curr->address == addr) {
      prev->next = curr->next;
      used->size -= curr->size;
      break;
    }
    prev = prev->next;
    curr = curr->next;
  }
  if (curr == NULL) {  // 否则内存回收失败
    return -1;
  }
  partition_t *block = curr;
  int size = block->size;
  unused->size += block->size;
  // 找到首次curr->address >= block->address的位置
  // 则prev-curr中间为插入点
  prev = unused;
  curr = unused->next;
  while (curr != NULL && curr->address < block->address) {
    prev = prev->next;
    curr = curr->next;
  }
  if (prev != unused && prev->address + prev->size == block->address) {
    // 与上一块合并
    prev->size += block->size;
    free(block);
    block = prev;
  } else {
    // 作为新块插入
    prev->next = block;
    block->next = curr;
  }
  if (curr != NULL && curr->address == block->address + block->size) {
    // 与下一块合并
    block->size += curr->size;
    block->next = curr->next;
    free(curr);
  }
  return size;
}

// 首次适应空闲分区查找，返回空闲分区，失败返回NULL
partition_t *first_fit_find(int size) {
  partition_t *prev = unused, *curr = unused->next;
  int found = 0;
  while (curr != NULL) {  // 查找合适节点
    if (curr->size >= size) {
      found = 1;
      break;
    } else {
      prev = prev->next;
      curr = curr->next;
    }
  }
  if (!found) {  // 没有合适的节点
    return NULL;
  }
  return prev;
}

// 最佳适应: 搜索整个列表，找到适合条件的最小的分区进行分配，返回空闲分区，失败返回NULL
partition_t *best_fit_find(int size) {
  partition_t *prev = unused, *curr = unused->next;
  partition_t *saved_prev = NULL, *saved_curr = NULL;
  int found = 0;
  while (curr != NULL) {  // 查找合适节点
    if (curr->size >= size) {
      found = 1;
      if (saved_curr == NULL || curr->size < saved_curr->size) { // 比现有更小
        saved_prev = prev;
        saved_curr = curr;
      }
    }
    prev = prev->next;
    curr = curr->next;
  }
  if (!found) {  // 没有合适的节点
    return NULL;
  }
  return saved_prev;
}

// 最差适应: 搜索整个列表，找到适合条件的最大的分区进行分配，返回空闲分区，失败返回NULL
partition_t *worst_fit_find(int size) {
  partition_t *prev = unused, *curr = unused->next;
  partition_t *saved_prev = NULL, *saved_curr = NULL;
  int found = 0;
  while (curr != NULL) {  // 查找合适节点
    if (curr->size >= size) {
      found = 1;
      if (saved_curr == NULL || curr->size > saved_curr->size) { // 比现有更大
        saved_prev = prev;
        saved_curr = curr;
      }
    }
    prev = prev->next;
    curr = curr->next;
  }
  if (!found) {  // 没有合适的节点
    return NULL;
  }
  return saved_prev;
}

// 打印输出链表
void print_partition(partition_t *head) {
  partition_t *before;
  int index;
  before = head->next;
  index = 0;
  printf("> 总空间(KB): %d\n", head->size);
  if (head->next == NULL) {
    printf("没有分区！\n");
  } else {
    printf(" index    address    end     size        \n");
    while (before != NULL) {
      printf("---------------------------------------\n");
      printf(" %-9d%-9d%-9d%-9d\n",
             index,
             before->address,
             before->address + before->size,
             before->size);
      index++;
      before = before->next;
    }
  }
  printf("---------------------------------------\n");
}
