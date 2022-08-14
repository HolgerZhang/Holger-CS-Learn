#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define INVALID -1
#define INF 0xffff
#define total_instruction 320  //模拟的指令数
#define page_instruction 10
#define total_page total_instruction/page_instruction  //模拟的虚拟页面数

typedef struct {  //页面结构
  int pn;  //页号
  int pfn;  //内存块号
  int time;  //访问时间
} page_type;
page_type page[total_page];  //所有页面
typedef struct pfc_struct { //页面控制结构
  int pn;  //页号
  int pfn;  //内存块号
  struct pfc_struct *next;
} pfc_type;
pfc_type pfc[total_page];  //所有页面的虚页控制结构
pfc_type *free_head;  //空内存页头指针
pfc_type *busy_head;  //忙内存页头指针
pfc_type *busy_tail;  //忙内存页尾指针
int invalid_count;  //页面失效次数
int instructions[total_instruction];  //指令流数据组
int pno[total_instruction];  //每条指令所属页号
int offset[total_instruction];  //每条指令的页号偏移值
void generate_instruction();  // 生成320条指令（教材）
void generate_instruction_randomly();  // 生成320条指令（随机）
void initialize(int total_pf);  //初始化数据
void FIFO(int total_pf);  //计算使用FIFO算法时的访问命中率
void LRU(int total_pf);  //计算使用LRU算法时的访问命中率
void OPT(int total_pf);  //计算使用OPT算法时的访问命中率

int main() {
  srand(10 * getpid());
  //通过随机函数随机生成 320 条指令
  generate_instruction();
//  generate_instruction_randomly();
  //指令序列变换为页面地址流
  for (int i = 0; i < total_instruction; i++) {
    pno[i] = instructions[i] / page_instruction;
    offset[i] = instructions[i] % page_instruction;
  }
  //用户工作区从4个页面到32个页面
  for (int i = 4; i <= 32; i++) {
    printf("%2d pno frames", i);
    FIFO(i);
    LRU(i);
    OPT(i);
    printf("\n");
  }
}

void generate_instruction() {
  // 50%的指令是顺序执行的;
  // 25%的指令均匀地分布在前地址部分;
  // 25%的指令均匀地分布在后地址部分。
  int s = (float) 319 * rand() / 32767 / 32767 / 2 + 1;
  for (int i = 0; i < total_instruction; i += 4) {
    if (s < 0 || s > 319) {
      printf("When i==%d, Error, s==%d\n", i, s);
      exit(0);
    }
    instructions[i] = s;
    instructions[i + 1] = instructions[i] + 1;
    instructions[i + 2] = (float) instructions[i] * rand() / 32767 / 32767 / 2;
    instructions[i + 3] = instructions[i + 2] + 1;
    s = (float) (318 - instructions[i + 2]) * rand() / 32767 / 32767 / 2
        + instructions[i + 2] + 2;
    if ((instructions[i + 2] > 318) || (s > 319)) {
      printf("instructions[%d+2],instructions number which is: %d and s==%d\n",
             i,
             instructions[i + 2],
             s);
    }
  }
}

void generate_instruction_randomly() {
  for (int i = 0; i < total_instruction; ++i) {
    instructions[i] = rand() % 320;
  }
}

void initialize(int total_pf) {
  invalid_count = 0;  //页面失效次数
  for (int i = 0; i < total_page; i++) {
    page[i].pn = i;  //页号
    page[i].pfn = INVALID;  //内存块号
    page[i].time = -1;  //访问时间
  }
  for (int i = 0; i < total_pf - 1; i++) {
    pfc[i].next = &pfc[i + 1];
    pfc[i].pfn = i;
  }
  pfc[total_pf - 1].next = NULL;
  pfc[total_pf - 1].pfn = total_pf - 1;
  free_head = &pfc[0];
}

void FIFO(int total_pf) {
  initialize(total_pf);
  busy_head = busy_tail = NULL;
  for (int i = 0; i < total_instruction; i++) {
    if (page[pno[i]].pfn == INVALID) {  //页面失效
      invalid_count++;      //失效次数
      pfc_type *p;
      if (free_head == NULL) {   //无空闲页面
        p = busy_head->next;
        free_head = busy_head;  //释放忙页面队列的第一个页面(队头)
        page[busy_head->pn].pfn = INVALID;  //该页设置为无效
        free_head->next = NULL;
        busy_head = p;
      }
      //按FIFO方式调入新页面到内存页面
      p = free_head->next;  //取空闲页面队列队头
      free_head->next = NULL;
      free_head->pn = pno[i];  //页号
      page[pno[i]].pfn = free_head->pfn;  //内存块号改为有效
      if (busy_tail == NULL)
        busy_head = busy_tail = free_head;
      else {
        busy_tail->next = free_head;  //空闲页面减少一个
        busy_tail = free_head;
      }
      free_head = p;
    }
  }
  printf(" FIFO:%6.4f", 1 - (double) invalid_count / total_instruction);
}

void LRU(int total_pf) {
  initialize(total_pf);
  for (int i = 0, time = 0; i < total_instruction; i++, time++) {
    if (page[pno[i]].pfn == INVALID) {   //页面失效
      invalid_count++;  //失效次数
      int min_time, min_pno;
      if (free_head == NULL) {   //无空闲页面
        min_time = INF;
        for (int j = 0; j < total_page; j++) {  //找出访问时间最远的（最小）
          if (page[j].pfn != INVALID && page[j].time < min_time) {
            min_time = page[j].time;
            min_pno = j;
          }
        }
        free_head = &pfc[page[min_pno].pfn]; //释放最近未访问的页面
        page[min_pno].pfn = INVALID;  //该页设置为无效
        free_head->next = NULL;
      }
      page[pno[i]].pfn = free_head->pfn;  //内存块号改为有效
      page[pno[i]].time = time;  // 记录访问时间
      free_head = free_head->next;   //空闲页面减少一个
    } else
      page[pno[i]].time = time; //命中，更新访问时间
  }
  printf(" LRU:%6.4f", 1 - (double) invalid_count / total_instruction);
}

void OPT(int total_pf) {
  initialize(total_pf);
  for (int i = 0; i < total_instruction; i++) {
    if (page[pno[i]].pfn == INVALID) {   //页面失效
      invalid_count++;  //失效次数
      int max_dist, max_pno, dist[total_page];
      if (free_head == NULL) {   //无空闲页面
        // 1：标记将来不会被使用的页面
        // 对于所有无效页面，设置最后一次访问的指令序号为无穷大
        for (int j = 0; j < total_page; j++) {
          if (page[j].pfn != INVALID) {
            dist[j] = INF;
          } else {
            dist[j] = 0;
          }
        }
        // 2：标记最远的将来才会被使用的页面
        // 对于此后所有指令所在的页，若无效记录其最后一次访问的指令序号，若有效则为0
        for (int j = i + 1; j < total_instruction; j++) {
          if (page[pno[j]].pfn != INVALID) {
            dist[pno[j]] = j;
          }
        }
        max_dist = 1;  // 找出最后一次访问的指令序号最大的页
        for (int j = 0; j < total_page; j++) {
          if (dist[j] > max_dist) {
            max_dist = dist[j];
            max_pno = j;
          }
        }
        free_head = &pfc[page[max_pno].pfn]; //释放页面
        free_head->next = NULL;  //该页设置为无效
        page[max_pno].pfn = INVALID;
      }
      page[pno[i]].pfn = free_head->pfn;  //内存块号改为有效
      free_head = free_head->next;   //空闲页面减少一个
    }
  }
  printf(" OPT:%6.4f", 1 - (double) invalid_count / total_instruction);
}


