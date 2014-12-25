#include <stdio.h>
#include <stdint.h>

int main(int argc,char**argv)
{
	printf("test system type length:\n");
	printf("sizeof(char)=%u\n",(uint32_t)sizeof(char));
	printf("sizeof(short)=%u\n",(uint32_t)sizeof(short));
	printf("sizeof(int)=%u\n",(uint32_t)sizeof(int));
	printf("sizeof(long)=%u\n",(uint32_t)sizeof(long));
	printf("sizeof(long long)=%u\n",(uint32_t)sizeof(long long));
	printf("sizeof(float)=%u\n",(uint32_t)sizeof(float));
	printf("sizeof(double)=%u\n",(uint32_t)sizeof(double));
	printf("sizeof(long double)=%u\n",(uint32_t)sizeof(long double));

	return 0;
}
