PHONY += test
#IS_X86_64="$(shell uname -a | grep -q 'x86_64')"
UNAME=$(shell uname -a)

ARCH=$(shell echo $(UNAME) | sed '/^.*x86_64.*$/1/')

ifneq ($(strip $(ARCH)), 1)
ARCH=0
endif

fun:
	#实现so可执行
	gcc -fPIC -DX86_64=$(ARCH) -shared -o fun.so fun.c -e fun
clean:
	-rm -rf ld.o
	-rm -rf test
	-rm -rf hello.o
	-rm -rf fun.so
	-rm -rf 2g
	-rm -rf 2g.o
