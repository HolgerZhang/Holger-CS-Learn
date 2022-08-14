#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#define SIZE 5  // 缓冲区大小
#define COUNT 10  // 总共生产的产品数量

typedef struct {  // 产品
  int id;     // 编号
  int value;  // 属性
} product_t;

product_t *buffer[SIZE];  // 保存产品的缓冲区
int producer_ptr = 0, consumer_ptr = 0;  // 生产指针和消费指针
// 生产指针指向缓冲区中下一个产品的保存位置，消费指针指向缓冲区中下一个取出的位置

sem_t empty;  //定义同步信号量 empty：空缓冲区数量
sem_t full;   //定义同步信号量 full：满缓冲区数量
sem_t mutex;  //定义互斥信号量 mutex
void semaphore_init();  // 初始化信号量
void semaphore_destroy();  // 删除信号量

void *producer() {  //生产者
  for (int i = 0; i < COUNT; ++i) {
    sem_wait(&empty);  // P(empty)
    sem_wait(&mutex);  // P(mutex)
    // 生产产品
    product_t *product = malloc(sizeof(product_t));
    if (product == NULL) {
      fprintf(stderr, "生产产品失败\n");
      semaphore_destroy();
      exit(EXIT_FAILURE);  // 进程退出
    } else {
      product->id = i;
      product->value = rand();
    }
    buffer[producer_ptr] = product;
    producer_ptr = (producer_ptr + 1) % SIZE;
    printf("生产产品（id=%d，属性：%d）\n", product->id, product->value);
    sem_post(&mutex);  // V(mutex)
    sem_post(&full);   // V(full)
  }
  return NULL;
}

void *consumer() {  //消费者
  for (int i = 0; i < COUNT; ++i) {
    sem_wait(&full);  // P(full)
    sem_wait(&mutex);  // P(mutex)
    // 从缓冲区中取出产品
    product_t *product = buffer[consumer_ptr];
    printf("消费产品（id=%d，属性：%d）\n", product->id, product->value);
    free(product);
    buffer[consumer_ptr] = NULL;
    consumer_ptr = (consumer_ptr + 1) % SIZE;
    sem_post(&mutex);  // V(mutex)
    sem_post(&empty);  // V(empty)
  }
  return NULL;
}

int main() {
  srand(time(NULL));
  semaphore_init();
  pthread_t id_producer;
  pthread_t id_consumer;
  pthread_create(&id_producer, NULL, producer, NULL); //创建生产者线程
  pthread_create(&id_consumer, NULL, consumer, NULL); //创建消费者线程
  pthread_join(id_producer, NULL);  //等待生产者线程结束
  pthread_join(id_consumer, NULL);  //等待消费者线程结束
  semaphore_destroy();
  return 0;
}

void semaphore_init() {
  sem_init(&empty, 0, SIZE);  // empty=SIZE
  sem_init(&full, 0, 0);    // full=0
  sem_init(&mutex, 0, 1);   // mutex=1
}

void semaphore_destroy() {
  sem_destroy(&empty);
  sem_destroy(&full);
  sem_destroy(&mutex);
}

