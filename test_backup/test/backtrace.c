#include <execinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void printf_line()
{
	void* func_addr[256];
	char** func_symb = NULL;
	int size;
	printf("===hello world====\n");
	size = backtrace(func_addr,256);
	func_symb = 
	backtrace_symbols(func_addr,size);
	while(size > 0)
	{
		printf("%d: %s\n",size,func_symb[size-1]);
		size --;
	}
	free(func_symb);

}
int init()
{
	printf_line();
	return 0;
}

int add(int a,int b)
{
	init();
	return a + b;
}

int main(int argc,char**argv)
{
	add(3,4);
	return add(0,0);

}
