
#ifndef LIBLOG_H
#define LIBLOG_H

#include <stdio.h>
#include "libdebug.h"

//引用lib提供的变量
extern char *__progname;

#define LIB_OUTPUT(file,fmt,...)\
	do{\
		fprintf(file,"[%s] %s:%s:%d ",__progname,__FILE__,__func__,__LINE__);\
		fprintf(file,fmt,##__VA_ARGS__);\
	}while(0)

#define LIB_DEBUG(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= DEBUG_LEVEL)\
		{\
			LIB_OUTPUT(stdout,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_INFO(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= INFO_LEVEL)\
		{\
			LIB_OUTPUT(stdout,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_LOG(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= LOG_LEVEL)\
		{\
			LIB_OUTPUT(stdout,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_WARN(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= WARN_LEVEL)\
		{\
			LIB_OUTPUT(stderr,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_ERROR(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= ERROR_LEVEL)\
		{\
			LIB_OUTPUT(stderr,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_FAULT(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= FAULT_LEVEL)\
		{\
			LIB_OUTPUT(stderr,fmt,##__VA_ARGS__) ;\
		}\
	}

#endif
