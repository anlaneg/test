#include <stdio.h>
#include <stdint.h>

int main(int argc,char**argv)
{
	printf("test system type length:\n");
	printf("(uint32_t)sizeof(char)=%u\n",(uint32_t)sizeof(char));
	printf("(uint32_t)sizeof(short)=%u\n",(uint32_t)sizeof(short));
	printf("(uint32_t)sizeof(int)=%u\n",(uint32_t)sizeof(int));
	printf("(uint32_t)sizeof(long)=%u\n",(uint32_t)sizeof(long));
	printf("(uint32_t)sizeof(long long)=%u\n",(uint32_t)sizeof(long long));
	printf("(uint32_t)sizeof(float)=%u\n",(uint32_t)sizeof(float));
	printf("(uint32_t)sizeof(double)=%u\n",(uint32_t)sizeof(double));
	printf("(uint32_t)sizeof(long double)=%u\n",(uint32_t)sizeof(long double));

	return 0;
}
