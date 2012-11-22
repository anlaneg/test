#include <stdio.h>

int main(int argc,char**argv)
{
	printf("test system type length:\n");
	printf("sizeof(char)=%u\n",sizeof(char));
	printf("sizeof(short)=%u\n",sizeof(short));
	printf("sizeof(int)=%u\n",sizeof(int));
	printf("sizeof(long)=%u\n",sizeof(long));
	printf("sizeof(long long)=%u\n",sizeof(long long));
	printf("sizeof(float)=%u\n",sizeof(float));
	printf("sizeof(double)=%u\n",sizeof(double));
	printf("sizeof(long double)=%u\n",sizeof(long double));

	return 0;
}
