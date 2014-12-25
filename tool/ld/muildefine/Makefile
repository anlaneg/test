#通过调整首次定义的函数位置,迫使进程选择第一个函数进行替换
OBJECT=wrap_init.o test.o
all: $(OBJECT) do_ld

%.o:%.c
	gcc -g -o $@ -c $<

do_ld:
	gcc -Wl,--allow-multiple-definition -g -o test $(OBJECT)

clean:
	-rm -rf $(OBJECT)
	-rm -rf test

