#include <stdio.h>
#include <string.h>

int main(int argc,char**argv)
{
	char*str="hello,world";
	printf("#%s#\n",strstr(str,"lo"));
	return 0;
}
