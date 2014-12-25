#obj-m += hello.o
#hello-objs := hello-1.o other.o 
obj-m += memdev.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
