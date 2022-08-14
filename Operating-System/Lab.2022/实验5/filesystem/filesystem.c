#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "filesystem.h"

char memory[MAX_DISK_SIZE];  //512KB的磁盘存储空间（链接分配）
char memory_usage[BLOCK_AMOUNT] = {};  //磁盘块的使用情况
MFD users[MAX_USER_SIZE];  //一级目录
int user_count = 0;  //用户数量
int login_user_id = -1;  //目前登录的用户ID

int main() {
  printf("文件管理模拟器\n");
  char input_cache[128], *input_res;
  for (;;) {
    printf("请登录或创建用户\n");
    printf("1-登录; 2-创建用户; 3-退出\n");
    printf(">>> ");
    fflush(stdout);
    scanf("%s", input_cache);
    fflush(stdin);
//    printf("!!> %s <!!\n", input_cache);
    int choice = (int) strtol(input_cache, &input_res, 10);
    if (choice == 1) {
      user_login();
    } else if (choice == 2) {
      user_create();
    } else if (choice == 3) {
      exit(EXIT_SUCCESS);
    } else {
      printf("您的输入有误，请重新选择\n");
    }
    fflush(stdout);
    if (login_user_id == -1) {  //没有登录状态
      continue;
    }
    //主循环
    for (;;) {
      printf(">>> ");
      fflush(stdout);
      memset(input_cache, 0, sizeof(input_cache));
      getchar();  //注意scanf不会对换行符做特殊处理，需要把\n单独去掉
      scanf("%[^\n]", input_cache);  //使用"%[^\n]"代替gets
      fflush(stdin);
//      printf("!!> %s <!!\n", input_cache);
      char *command = strtok(input_cache, " ");
      if (command == NULL || strlen(command) == 0) {
        continue;
      }
      if (strcmp(command, "create") == 0) {
        char *file_name = strtok(NULL, " ");
        if (file_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_create(file_name) != 0) {
            printf("文件创建失败\n");
          }
        }
      } else if (strcmp(command, "delete") == 0) {
        char *file_name = strtok(NULL, " ");
        if (file_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_delete(file_name) != 0) {
            printf("文件删除失败\n");
          }
        }
      } else if (strcmp(command, "open") == 0) {
        char *file_name = strtok(NULL, " ");
        if (file_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_open(file_name) != 0) {
            printf("文件打开失败\n");
          }
        }
      } else if (strcmp(command, "close") == 0) {
        char *file_name = strtok(NULL, " ");
        if (file_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_close(file_name) != 0) {
            printf("文件关闭失败\n");
          }
        }
      } else if (strcmp(command, "read") == 0) {
        char *file_name = strtok(NULL, " ");
        if (file_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_read(file_name) != 0) {
            printf("文件读取失败\n");
          }
        }
      } else if (strcmp(command, "write") == 0) {
        char *file_name = strtok(NULL, " ");
        if (file_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_write(file_name) != 0) {
            printf("文件写入失败\n");
          }
        }
      } else if (strcmp(command, "dir") == 0) {
        file_dir();
      } else if (strcmp(command, "rename") == 0) {
        char *file_name = strtok(NULL, " ");
        char *new_name = strtok(NULL, " ");
        if (file_name == NULL || new_name == NULL) {
          printf("请输入文件名\n");
        } else {
          if (file_rename(file_name, new_name) != 0) {
            printf("修改名称失败\n");
          }
        }
      } else if (strcmp(command, "chmod") == 0) {
        char *file_name = strtok(NULL, " ");
        char *type_str = strtok(NULL, " ");
        if (file_name == NULL || type_str == NULL) {
          printf("请输入文件名以及文件模式\n");
        } else {
          char mod = type_str[0];
          if (file_chmod(file_name, mod) != 0) {
            printf("文件模式修改失败\n");
          }
        }
      } else if (strcmp(command, "help") == 0) {
        help();
      } else if (strcmp(command, "logout") == 0) {
        user_logout();
        break;
      } else if (strcmp(command, "exit") == 0) {
        exit(EXIT_SUCCESS);
      } else {
        printf("您的输入有误，请重新输入。\n输入 help 查看帮助。\n");
      }
      fflush(stdout);
    }
  }
}

//具体实现

//文件管理

//分配一个磁盘块
DISK *memory_alloc() {
  int address = -1;
  for (int i = 0; i < BLOCK_AMOUNT; ++i) {
    if (memory_usage[i] == 0) {
      address = i * BLOCK_SIZE;
      memory_usage[i] = 1;
      break;
    }
  }
  if (address == -1) {
    return NULL;
  }
  DISK *block = (DISK *) malloc(sizeof(DISK));
  block->address = address;
  block->length = 0;
  block->next = NULL;
  return block;
}

//回收start_block指向的磁盘块链表
void memory_free(DISK *start_block) {
  DISK *next;
  while (start_block != NULL) {
    next = start_block->next;
    memory_usage[start_block->address / BLOCK_SIZE] = 0;
    free(start_block);
    start_block = next;
  }
}

int file_create(const char *file_name) {
  //判断文件是否存在
  for (UFD *p = users[login_user_id].user_dir_head->next;
       p != NULL;
       p = p->next) {
    if (strcmp(p->file->file_name, file_name) == 0) {
      printf("文件%s已存在\n", file_name);
      return 1;
    }
  }
  //创建目录项
  UFD *file_node = (UFD *) malloc(sizeof(UFD));  //分配UFD
  if (file_node == NULL) {
    return 2;
  }
  file_node->next = NULL;
  //创建文件控制块
  file_node->file = (FCB *) malloc(sizeof(FCB));  //分配FCB
  if (file_node->file == NULL) {
    return 2;
  }
  strcpy(file_node->file->file_name, file_name);
  file_node->file->mode = FILE_MODE_WRITABLE;
  file_node->file->disk_start = memory_alloc();  //分配一个磁盘块
  if (file_node->file->disk_start == NULL) {
    printf("文件系统没有空余空间可用\n");
    free(file_node->file);  //撤销分配
    free(file_node);
    return 3;
  }
  file_node->file->disk_end = file_node->file->disk_start;  //结束磁盘块
  file_node->file->length = 0;  //文件大小
  file_node->file->max_length = BLOCK_SIZE;  //占用空间
  file_node->file->opened = false;  //默认未打开
  file_node->file->modify_time = time(NULL);  //文件修改时间
  //将目录项插入UFD链表
  UFD *p = users[login_user_id].user_dir_head;
  while (p->next) p = p->next;
  p->next = file_node;
  return 0;
}

int file_delete(const char *file_name) {
  UFD *prev = users[login_user_id].user_dir_head;  //前驱节点
  UFD *curr = prev->next;  //要找的节点
  //查找指定的文件
  while (curr != NULL) {
    if (strcmp(curr->file->file_name, file_name) == 0) {
      break;  //找到了
    } else {
      prev = prev->next;
      curr = curr->next;
    }
  }
  if (curr == NULL) {
    printf("没有找到该文件，请检查输入的文件名是否正确\n");
    return 1;
  }
  //判断文件是否被进程打开
  if (curr->file->opened == true) {
    printf("该文件已被进程打开\n");
    return 2;
  }
  //调整前驱节点的next
  prev->next = curr->next;
  //删除curr
  memory_free(curr->file->disk_start);
  free(curr);
  return 0;
}

//查找指定的FCB
FCB *find_file(const char *file_name) {
  UFD *prev = users[login_user_id].user_dir_head;  //前驱节点
  UFD *curr = prev->next;  //要找的节点
  //查找指定的文件
  while (curr != NULL) {
    if (strcmp(curr->file->file_name, file_name) == 0) {
      break;  //找到了
    } else {
      prev = prev->next;
      curr = curr->next;
    }
  }
  if (curr == NULL) {
    return NULL;
  }
  return curr->file;
}

int file_open(const char *file_name) {
  //判断file_name文件是否存在
  FCB *fcb = find_file(file_name);
  if (fcb == NULL) {
    printf("文件%s不存在\n", file_name);
    return 1;
  }
  //判断file_name文件是否打开
  if (fcb->opened == true) {
    printf("该文件已被进程打开\n");
    return 2;
  }
  fcb->opened = true;
  return 0;
}

int file_close(const char *file_name) {
  //判断file_name文件是否存在
  FCB *fcb = find_file(file_name);
  if (fcb == NULL) {
    printf("文件%s不存在\n", file_name);
    return 1;
  }
  fcb->opened = false;
  return 0;
}

int file_read(const char *file_name) {
  //判断file_name文件是否存在
  FCB *fcb = find_file(file_name);
  if (fcb == NULL) {
    printf("文件%s不存在\n", file_name);
    return 1;
  }
  //判断file_name文件是否打开
  if (fcb->opened != true) {
    printf("该文件没有被打开，无法读写\n");
    return 2;
  }
  //输出文件内容，每50字符换一次行
  int count = 0;
  for (DISK *block = fcb->disk_start; block != NULL; block = block->next) {
    for (int i = 0; i < block->length; ++i, ++count) {
      printf("%c", memory[block->address + i]);
      if (memory[block->address + i] == '\n') {
        count = 0;
      }
      if ((count + 1) % 50 == 0) {
        printf("\n");
      }
    }
  }
  return 0;
}

int file_write(const char *file_name) {
  //判断file_name文件是否存在
  FCB *fcb = find_file(file_name);
  if (fcb == NULL) {
    printf("文件%s不存在\n", file_name);
    return 1;
  }
  //判断file_name文件是否打开
  if (fcb->opened != true) {
    printf("该文件没有被打开，无法读写\n");
    return 2;
  }
  //判断file_name文件是否有写权限
  if (fcb->mode != FILE_MODE_WRITABLE) {
    printf("该文件没有写权限，无法写入\n");
    return 3;
  }
  char buff[1030];
  printf("请输入要写入的内容，以换行结束，不超过1024个字符：\n");
  fflush(stdout);
  fflush(stdin);
  getchar();
  scanf("%[^\n]", buff);
  //舍弃大于1024的部分，末尾加换行符
  size_t len = strlen(buff);
  len = len > 1024 ? 1024 : len;
  buff[len] = '\n';
  buff[++len] = 0;
  //修改写入时间
  fcb->modify_time = time(NULL);
  //写入文件
  DISK *b = fcb->disk_end;
  for (int i = 0; i < len; ++i) {
    if (b->length >= BLOCK_SIZE) {  //当前磁盘块已满
      b->next = memory_alloc();  //申请新的磁盘块
      if (b->next == NULL) {
        printf("文件系统没有空余空间可用，第%d个字符后的内容将被舍弃\n", i);
        return 4;
      }
      b = b->next;
      fcb->max_length += BLOCK_SIZE; //更新占用空间
      fcb->disk_end = b;
    }
    //逐字符写入
    memory[b->address + b->length] = buff[i];
    b->length++;
    fcb->length++;
  }
  return 0;
}

int file_dir() {
  printf("文件名\t 文件长度\t 占用空间\t 物理地址\t 文件类型\t 进程占用\t 修改时间\n");
  char time_str[128];
  for (UFD *p = users[login_user_id].user_dir_head->next;
       p != NULL;
       p = p->next) {
    strftime(time_str, 128, "%a, %d %b %Y %H:%M:%S GMT",
             localtime(&p->file->modify_time));
    printf("%-6s\t %-6d\t %-6d\t %-6d\t %-6c\t %-6s\t %s\n",
           p->file->file_name,
           p->file->length,
           p->file->max_length,
           p->file->disk_start->address,
           p->file->mode,
           p->file->opened == true ? "是" : "否",
           time_str);
  }
  return 0;
}

int file_rename(const char *file_name, const char *new_name) {
  //判断file_name文件是否存在
  FCB *fcb = find_file(file_name);
  if (fcb == NULL) {
    printf("文件%s不存在\n", file_name);
    return 1;
  }
  //判断new_name文件是否存在
  for (UFD *p = users[login_user_id].user_dir_head->next;
       p != NULL;
       p = p->next) {
    if (strcmp(p->file->file_name, new_name) == 0) {
      printf("文件%s已存在\n", new_name);
      return 2;
    }
  }
  strcpy(fcb->file_name, new_name);
  return 0;
}

int file_chmod(const char *file_name, char mod) {
  //判断file_name文件是否存在
  FCB *fcb = find_file(file_name);
  if (fcb == NULL) {
    printf("文件%s不存在\n", file_name);
    return 1;
  }
  //判断file_name文件是否打开
  if (fcb->opened == true) {
    printf("该文件已被进程打开\n");
    return 2;
  }
  //判断文件模式是否合法
  if (mod != FILE_MODE_READONLY && mod != FILE_MODE_WRITABLE) {
    printf("错误的文件模式\n");
    return 3;
  }
  fcb->mode = mod;
  return 0;
}

//用户管理
void user_create() {
  if (user_count >= MAX_USER_SIZE) {
    printf("用户数量已达到最大，创建用户失败\n");
    return;
  }
  char input_cache[32], input_cache2[32];
  //输入并校验用户名
  printf("请输入用户名：");
  fflush(stdout);
  fflush(stdin);
  scanf("%s", input_cache);
  fflush(stdin);
  if (strlen(input_cache) <= 2) {
    printf("用户名过短，创建用户失败\n");
    return;
  }
  if (strlen(input_cache) > 16) {
    input_cache[16] = 0;
    printf("用户名过长，将截取前15个字符：%s\n", input_cache);
  }
  for (int i = 0; i < user_count; i++) {
    if (!strcmp(users[i].username, input_cache)) {
      printf("该用户名已存在，创建用户失败\n");
      return;
    }
  }
  int user_id = user_count;
  user_count++;
  strcpy(users[user_id].username, input_cache);
  //输入并校验密码
  for (;;) {
    printf("请输入密码：");
    fflush(stdout);
    fflush(stdin);
    system("stty -echo");  //关闭回显
    system("stty -icanon");
    scanf("%s", input_cache);
    fflush(stdin);
    system("stty icanon");
    system("stty echo");
    printf("\n");
    if (strlen(input_cache) < 6 || strlen(input_cache) > 16) {
      printf("密码长度应为6-15位，请重新输入\n");
      continue;
    }
    printf("请重复输入：");
    fflush(stdout);
    fflush(stdin);
    system("stty -echo");  //关闭回显
    system("stty -icanon");
    scanf("%s", input_cache2);
    fflush(stdin);
    system("stty icanon");
    system("stty echo");
    printf("\n");
    if (strcmp(input_cache, input_cache2) != 0) {
      printf("两次输入的不一致，请重新输入\n");
      continue;
    }
    break;
  }
  strcpy(users[user_id].password, input_cache);
  printf("创建用户成功，将以 %s 用户登录\n", users[user_id].username);
  login_user_id = user_id;
  //创建用户的二级目录
  users[user_id].user_dir_head = (UFD *) malloc(sizeof(UFD)); //头节点！
  users[user_id].user_dir_head->file = NULL;
}

void user_login() {
  char name[32], passwd[32];
  //输入并校验用户名
  printf("请输入用户名：");
  fflush(stdout);
  fflush(stdin);
  scanf("%s", name);
  fflush(stdin);
  if (strlen(name) <= 2) {
    printf("用户名过短\n");
    return;
  }
  if (strlen(name) > 16) {
    name[16] = 0;
    printf("用户名过长，将截取前15个字符：%s\n", name);
  }
  int user_id = -1;
  for (int i = 0; i < user_count; i++) {
    if (strcmp(users[i].username, name) == 0) {
      user_id = i;
      break;
    }
  }
  if (user_id == -1) {
    printf("您输入的用户名不存在\n");
    return;
  }
  //输入并校验密码
  for (int times = 3; times > 0; times--) {
    printf("请输入密码：");
    fflush(stdout);
    fflush(stdin);
    system("stty -echo");  //关闭回显
    system("stty -icanon");
    scanf("%s", passwd);
    fflush(stdin);
    system("stty icanon");
    system("stty echo");
    printf("\n");
    if (strcmp(users[user_id].password, passwd) != 0) {
      printf("您输入的密码错误，您还有%d次输入机会\n", times - 1);
      continue;
    }
    printf("您好，%s\n", users[user_id].username);
    login_user_id = user_id;
    break;
  }
}

void user_logout() {
  printf("再见，%s!\n", users[login_user_id].username);
  login_user_id = -1;
}

//辅助函数
void help() {
  printf("———————————————————————————————————————\n");
  printf(" create-创建 格式：create a1，创建名为a1的文件，默认可读可写，分配一个磁盘块（512 Bytes）\n");
  printf(" delete-删除 格式：delete a1，删除名为a1的文件\n");
  printf(" open-打开文件 格式：open a1，打开名为a1的文件，若已打开则失败\n");
  printf(" close-关闭文件 格式：close a1，将关闭文件a1\n");
  printf(" read-查看文件内容 格式：read a1，显示a1的内容，文件需要预先打开，否则不成功\n");
  printf(" write-写入 格式：write a1，根据提示写入a1，文件需要预先打开，否则不成功\n");
  printf(" dir-列文件目录 格式：dir，显示当前用户的所有文件\n");
  printf(" rename-重命名 格式：rename a1 b1，将文件a1改名为b1\n");
  printf(" chmod-修改文件模式，只读-r，可读可写-w 格式：chmod a1 r，将文件a1的权限改为只读方式\n");
  printf(" help-显示帮助界面\n");
  printf(" logout-退出用户，返回登录界面\n");
  printf(" exit-退出程序\n");
  printf("————————————————————————————————————————\n");
}

