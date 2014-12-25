#include <stdio.h>

extern test_init(void);

int main(int argc,char**argv)
{
	if(test_init())
	{
		printf("hi,test pass!\n");
		return 0;
	}
	return 1;
}
