#PHONY += test
1g: 
	#尝试自定义段及遍历运行(１代)
	gcc -g -o ld.o -c ld.c
	gcc -g -nostdlib -c stubstart.S -o hello.o 
	ld -o test -T my.lds ld.o hello.o
clean:
	-rm -rf ld.o
	-rm -rf test
	-rm -rf hello.o
	-rm -rf fun.so
	-rm -rf 2g
	-rm -rf 2g.o

2g:
	#尝试采用脚本时,仍能连接gcc (２代)
	#my2.lds来自于ld --verbose合入要加入的ld片段.
	#命令行来源于gcc -g -o hello hello.c --verbose
	gcc -g -o 2g.o -c 2g.c
	ld --build-id --eh-frame-hdr -m elf_i386 --hash-style=gnu -dynamic-linker /lib/ld-linux.so.2 -o 2g /usr/lib/crt1.o /usr/lib/crti.o /usr/lib/gcc/i686-linux-gnu/4.4.5/crtbegin.o -L/usr/lib/gcc/i686-linux-gnu/4.4.5 -L/lib -L/usr/lib/ -L/usr/lib/i686-linux-gnu 2g.o -lgcc -lgcc_s -lc --no-as-needed /usr/lib/gcc/i686-linux-gnu/4.4.5/crtend.o /usr/lib/crtn.o -T my2.lds 




