#include <stdio.h>

int test_init(void)
{
	printf("hi,i'm just test ld '--warp' option\n");
	return 0;
}


int main(int argc,char**argv)
{
	if(test_init())
	{
		printf("hi,test pass!\n");
		return 0;
	}
	return 1;
}
