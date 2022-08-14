#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#define SYSCALL_ID 333

int main() {
	long ret = syscall(SYSCALL_ID);
	printf("System call sys_helloworld reutrn %ld\n", ret);
	return 0;
}
