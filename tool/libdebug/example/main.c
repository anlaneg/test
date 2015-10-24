#include <stdio.h>

#include "liblog.h"
#include "process_debug.h"

int main(int argc,char**argv)
{
	LIB_LOG(LOG_MODULE,"hello world \n");
	LIB_LOG(LOG_MODULE,"hello world :%d\n",3);
	return 1;
}
