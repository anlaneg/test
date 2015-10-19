#include <stdio.h>

#ifdef PROJECT_TEST
#include "dyn.h"
#include "static.h"
#include "module1.h"
#include "module2.h"

void project_test(void)
{
	dyn();
	fun();
	module1();
	module2();	
}
#endif
int main(int argc,char**argv)
{
	printf("hello world");
	#ifdef PROJECT_TEST
	project_test();
	#endif
	return 0;
}
