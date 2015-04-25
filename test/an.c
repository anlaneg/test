#include <stdio.h>
#include <math.h>


int main(int argc,char**argv)
{
	int i = 1;
	for(;i < 30 ; ++i)
	{
		long n = 1 << i;	
	
		int m = (int)(log2(n*(n-1))+0.99);
	
		printf("when %d bits ,use %d\n",2*i,m);
	}
	return 0;
}
