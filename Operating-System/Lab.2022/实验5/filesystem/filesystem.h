#include <stdbool.h>
#include <time.h>

#ifndef EXP05_FILESYSTEM_H_
#define EXP05_FILESYSTEM_H_

#define MAX_USER_SIZE 100  //最多用户数量
#define BLOCK_SIZE 512  //磁盘块大小（512 Bytes）
#define BLOCK_AMOUNT 1024  //磁盘块数量
#define MAX_DISK_SIZE BLOCK_SIZE*BLOCK_AMOUNT //最大磁盘空间（1024块）

#define FILE_MODE_READONLY 'r'
#define FILE_MODE_WRITABLE 'w'

typedef struct disk_block {  //磁盘块结构体
  int address;  //起始地址
  int length;  //使用容量（最大为BLOCK_SIZE）
  struct disk_block *next;  //指向下一磁盘块的指针
} DISK;

typedef struct file_control_block {  //文件控制块
  char file_name[16];  //文件名
  DISK *disk_start, *disk_end;  //文件在磁盘中的起始磁盘块和结束磁盘块
  int length;  //文件内容长度
  int max_length;  //文件占用空间
  char mode;  //文件读写方式
  time_t modify_time;  //文件相关的时间信息
  bool opened;  //判断是否有进程打开了该文件
} FCB;

typedef struct user_file_directory {  //用户文件目录
  FCB *file;  //文件
  struct user_file_directory* next;  //下一个目录
} UFD;

typedef struct master_file_directory {  //主文件目录
  char username[16];  //用户账号
  char password[16];  //用户密码
  UFD *user_dir_head;  //用户文件目录（二级目录）
} MFD;

//文件管理
int file_create(const char *file_name);  //创建文件，默认可读可写，分配一个磁盘块（512 Bytes）
int file_delete(const char *file_name);  //删除文件，回收磁盘块，文件被打开时失败
int file_open(const char *file_name);  //打开文件，若已打开则失败
int file_close(const char *file_name);  //关闭文件
int file_read(const char *file_name);  //读文件，文件需要预先打开，否则不成功
int file_write(const char *file_name);  //写文件，文件需要预先打开，否则不成功
int file_dir();  //列出当前用户的所有文件
int file_rename(const char *file_name, const char *new_name);  //重命名
int file_chmod(const char *file_name, char mod);  //修改文件模式，只读-r，可读可写-w

//用户管理
void user_create();  //创建新用户，若用户名重复失败
void user_login();  //登录到用户
void user_logout();  //登出

//辅助函数
void help();  //显示帮助

#endif //EXP05_FILESYSTEM_H_
