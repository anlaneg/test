file=speed.o tipc_rdm_test.o

all:$(file)
	gcc -o $@ $^

$(file):%.o:%.c
	gcc -g -Wall -c -o $@ $^


clean:
	-rm -rf $(file)

