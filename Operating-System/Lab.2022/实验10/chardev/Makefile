CONFIG_MODULE_SIG=n
obj-m := chardev.o
KDIR := /usr/src/linux-$(shell uname -r | cut -d '-' -f1)
PWD := $(shell pwd)
all: modules
modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean