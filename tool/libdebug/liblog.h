
#ifndef LIBLOG_H
#define LIBLOG_H

#include <stdio.h>
#include "libdebug.h"

//引用lib提供的变量
extern char *__progname;

#define LIB_LOG_ENABLE_COLOR (1)

//see http://blog.csdn.net/zy_zhao/article/details/8095253
#define LIB_OUTPUT_DEBUG_COLOR  (34)
#define LIB_OUTPUT_INFO_COLOR   (42)
#define LIB_OUTPUT_LOG_COLOR    (45)
#define LIB_OUTPUT_WARN_COLOR   (43)
#define LIB_OUTPUT_ERROR_COLOR  (31)
#define LIB_OUTPUT_FAULT_COLOR  (41)


#if LIB_LOG_ENABLE_COLOR

#define LIB_OUTPUT(file,color,fmt,...)\
	do{\
		fprintf(file,"\033[0;%dm",LIB_OUTPUT_##color##_COLOR);\
		fprintf(file,"[%s] %s:%s:%d ",__progname,__FILE__,__func__,__LINE__);\
		fprintf(file,fmt,##__VA_ARGS__);\
		fprintf(file,"\033[0m");\
	}while(0)

#else

#define LIB_OUTPUT(file,color,fmt,...)\
	do{\
		fprintf(file,"[%s] %s:%s:%d ",__progname,__FILE__,__func__,__LINE__);\
		fprintf(file,fmt,##__VA_ARGS__);\
	}while(0)

#endif


#define LIB_DEBUG(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= DEBUG_LEVEL)\
		{\
			LIB_OUTPUT(stdout,DEBUG,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_INFO(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= INFO_LEVEL)\
		{\
			LIB_OUTPUT(stdout,INFO,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_LOG(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= LOG_LEVEL)\
		{\
			LIB_OUTPUT(stdout,LOG,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_WARN(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= WARN_LEVEL)\
		{\
			LIB_OUTPUT(stderr,WARN,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_ERROR(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= ERROR_LEVEL)\
		{\
			LIB_OUTPUT(stderr,ERROR,fmt,##__VA_ARGS__);\
		}\
	}

#define LIB_FAULT(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() <= FAULT_LEVEL)\
		{\
			LIB_OUTPUT(stderr,FAULT,fmt,##__VA_ARGS__) ;\
		}\
	}

#endif
