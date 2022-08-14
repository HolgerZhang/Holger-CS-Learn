#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define data_buffer_len 4096
char read_buffer[data_buffer_len];

int main() {
  int fd = open("/dev/hello", O_RDWR);  //以可读可写方式打开
  ssize_t ret;
  size_t length;
  //读取
  ret = read(fd, read_buffer, sizeof(char) * data_buffer_len);
  read_buffer[ret] = '\0';
  printf("Read: %s (size=%ld)\n", read_buffer, ret);
  //写入
  const char *write_buffer = "Hello, here is Hao Zhang!";
  length = strlen(write_buffer);
  ret = write(fd, write_buffer, sizeof(char) * length);
  printf("Write: %s (ret=%ld)\n", write_buffer, ret);
  //再读取
  ret = read(fd, read_buffer, sizeof(char) * length);
  read_buffer[ret] = '\0';
  printf("Read: %s (size=%ld)\n", read_buffer, ret);
  close(fd);
  return 0;
}