#include<stdio.h>
#include<stdlib.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#define SYSCALL_ID 223

int main() {
	unsigned long ret = syscall(SYSCALL_ID);
	printf("System call reutrn %ld\n", ret);
	return 0;
}

