CONFIG_MODULE_SIG=n
obj-m := hello.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:= /usr/src/linux-$(shell uname -r | cut -d '-' -f1)
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
