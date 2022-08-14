//
// Created by holger on 2022/6/2.
//
#include <linux/module.h>

static int __init init_hello(void) {
  printk("<1>Hello World, by Hao Zhang!\n");
  return 0;
}

static void __exit cleanup_hello(void) {
  printk("<1>Goodbye, by Hao Zhang!\n");
}

MODULE_LICENSE("GPL");
module_init(init_hello);
module_exit(cleanup_hello);
MODULE_AUTHOR("Hao Zhang");
MODULE_DESCRIPTION("hello world");