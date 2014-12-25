#include <unistd.h>

int main(int argc,char**argv)
{
	if(link("./mytest.c","./mytest_new.c"))
	{
		return 1;
	}
	return 0;
}
