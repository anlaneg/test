
OBJECT=test.o wrap_init.o
all: $(OBJECT) do_ld

%.o:%.c
	gcc -g -o $@ -c $<

do_ld:
	gcc -g -Wl,--defsym=test_init=test_init_really -o test $(OBJECT)

clean:
	-rm -rf $(OBJECT)
	-rm test

