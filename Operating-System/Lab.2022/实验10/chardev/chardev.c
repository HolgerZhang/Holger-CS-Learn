#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#define SUCCESS  0
#define DEVICE_NAME  "chardev"
#define BUF_LEN  80
static int Major;
static int Device_Open = 0;  //设备打开数量
static char msg[BUF_LEN]; //字符缓冲区
static char *msg_Ptr = NULL;  //发送的数据指针
//函数声明
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *filp,
                           char __user *buffer,
                           size_t length,
                           loff_t *offset);
static ssize_t device_write(struct file *filp,
                            const char __user *buffer,
                            size_t length,
                            loff_t *offset);
//定义初始化字符设备的操作方法
static struct file_operations fops =
    {.read = device_read, .write = device_write, .open = device_open, .release = device_release};
//打开设备
static int device_open(struct inode *inode, struct file *file) {
  static int counter = 0;
  if (Device_Open)
    return -EBUSY;
  Device_Open++;
  sprintf(msg, "I already told you %d times Hello world\n", counter++);
  msg_Ptr = msg;
  try_module_get(THIS_MODULE);
  return SUCCESS;
}
//释放设备
static int device_release(struct inode *inode, struct file *file) {
  Device_Open--;
  module_put(THIS_MODULE);
  return 0;
}
//读设备
static ssize_t device_read(struct file *filp,
                           char __user *buffer,
                           size_t length,
                           loff_t *offset) {
  if (*msg_Ptr == 0)
    return 0;
  ssize_t max_len = (ssize_t) strlen(msg);
  ssize_t len = min((ssize_t) length, max_len);
  //内核空间不能直接访问用户空间的buffer
  copy_to_user(buffer, msg_Ptr, len);
  return len;
}
//写设备
static ssize_t device_write(struct file *filp,
                            const char __user *buffer,
                            size_t length,
                            loff_t *offset) {
  ssize_t len = min((int) length, BUF_LEN);
  //内核空间不能直接访问用户空间的buffer
  copy_from_user(msg_Ptr, buffer, len);
  return len;
}
//初始化字符设备
int init_chardev_module(void) {
  Major = register_chrdev(0, DEVICE_NAME, &fops);
  if (Major < 0) {
    printk("Registering the character device failed with %d \n ", Major);
    return Major;
  }
  printk("<1> I was assigned major number %d ", Major);
  printk("<1> the drive, create a dev file");
  printk("<1> mknod /dev/hello c %d 0.\n", Major);
  printk("<1> I was assigned major number %d ", Major);
  printk("<1> the device file\n");
  printk("<1> Remove the file device and module when done\n");
  printk("<1> By Hao Zhang, 1927405160.\n");
  return 0;
}
//关闭字符设备
void exit_chardev_module(void) {
  unregister_chrdev(Major, DEVICE_NAME);
}
MODULE_LICENSE("Dual BSD/GPL");
module_init(init_chardev_module);
module_exit(exit_chardev_module);