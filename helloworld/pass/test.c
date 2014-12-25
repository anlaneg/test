#include "stdio.h"
struct A
{
	char a;
	//padding char[3]
	int c;
};


struct B
{
	long long h;//8
	int c;//4
	short a;//2
	char d;//1
	char b;//1
	char e;//1
	//padding char[3]
};

struct C
{
	long long h;//8
	int c;//4
	short d;//2
	//padding char[2]
};


#define BUILD_ERROR(cond) \
do{\
	(void)sizeof(typeof(cond) buffer[0-!!!(cond)]); \
}while(0)

int main()
{
	printf("%d,sizeof(a)=%u,sizeof(b)=%u,sizeof(c)=%u\n",sizeof(short),sizeof(struct A),sizeof(struct B),sizeof(struct C));
	return 0;
}
