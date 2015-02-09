#include <stdio.h>
#include <stdint.h>

int add(int a,int b)
{
    return a+b;
}

int test(int a, int b)
{
    return a-b;
}

typedef int (*sf_hook_fun)(int,int);

 __attribute__((section(".SF_HOOK"))) static sf_hook_fun a = add  ;
 __attribute__((section(".SF_HOOK"))) static sf_hook_fun b = test ;

extern long sf_hook_start_point;
extern long sf_hook_end_point;

int main(int argc,char**argv)
{
    sf_hook_fun*  start = (sf_hook_fun*)(&sf_hook_start_point);
    while((uintptr_t)start < (uintptr_t)&sf_hook_end_point)
    {
	int ret = (*start)(3,4);
	printf(" result = %d\n",ret);
	start ++;
    }
    return 0;
}
