#include <stdio.h>

#include "process_debug.h"
#include "liblog.h"

int main(int argc,char**argv)
{
	LIB_LOG(LOG_MODULE,"hello world :%d\n",3);
	return 1;
}
