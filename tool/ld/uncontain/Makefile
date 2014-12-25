
OBJECT=test.o old_version.o wrap_init.o 
all: $(OBJECT) do_ld

%.o:%.c
	gcc -g -o $@ -c $<

do_ld:
	gcc -g -Wl,--wrap=test_init -o test $(OBJECT)

clean:
	-rm -rf $(OBJECT)
	-rm -rf test

