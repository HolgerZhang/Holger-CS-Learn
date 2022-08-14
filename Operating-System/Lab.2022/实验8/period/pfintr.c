#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define FILENAME "/proc/vmstat"
#define DEFAULT_TIME 5

long get_page_fault(void);

bool isnumber(const char *str) {
  for (int i = 0; i < strlen(str); ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

int main(int argc, const char **argv) {
  int calc_time = DEFAULT_TIME;
  long page_fault;  //休眠时间
  if (argc >= 2 && isnumber(argv[1])) {
    calc_time = atoi(argv[1]);
  }
  printf("Use time: %ds\n", calc_time);
  page_fault = get_page_fault();
  sleep(calc_time);  //进程休眠
  page_fault = get_page_fault() - page_fault;
  printf("In %d seconds,system calls %ld page fault!\n",
         calc_time, page_fault);
  return 0;
}

/* 该函数对 /proc/stat 文件内容进行读操作，读取指定项的值到 data */
ssize_t readfile(char *data) {
  int i, offset = 0, count = 0;
  char c, string[50];
  int fd = open(FILENAME, O_RDONLY);
  ssize_t retval;
  if (fd < 0) {
    printf("Open file /proc/stat failed!\n");
    return -1;
  }
  /* 查找 vmstat 文件中的关键字 pgfault */
  do {
    i = 0;
    do {
      lseek(fd, offset, SEEK_SET);
      retval = read(fd, &c, sizeof(char));
      if (retval < 0) {
        printf("read file error!\n");
        return retval;
      }
      offset += sizeof(char);
      if (c == ' ' || c == '\n') {
        string[i] = 0;
        break;
      }
      if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
          || (c >= 'A' && c <= 'Z'))
        string[i++] = c;
    } while (1);
  } while (strcmp("pgfault", string));
  /* 读取缺页次数 */
  i = 0;
  do {
    lseek(fd, offset, SEEK_SET);
    retval = read(fd, &c, sizeof(char));
    if (retval < 0) {
      printf("read file error!\n");
      return retval;
    }
    offset += sizeof(char);
    if (c == ' ' || c == '\n') {
      string[i] = 0;
      i = 0;
      count++;
    }
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z'))
      string[i++] = c;
  } while (count != 1);
  close(fd);
  strcpy(data, string);
  return 0;
}

/* 该函数通过调用文件操作函数 readfile, 得到当前系统的缺页中断次数 */
long get_page_fault(void) {
  char pgfault[50], *buff;
  /* 读取缺页中断次数 */
  if (readfile(pgfault) < 0) {
    printf("read data from file failed!\n");
    exit(0);
  }
  printf("Now the number of page fault is %s\n", pgfault);
  return strtol(pgfault, &buff, 10);
}