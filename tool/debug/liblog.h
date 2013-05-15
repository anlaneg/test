
#ifndef LIBLOG_H
#define LIBLOG_H

#include <stdio.h>
#include "libdebug.h"


#define LIB_DEBUG(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() >= DEBUG_LEVEL)\
		{\
			fprintf(stdout,fmt,##__VA_ARGS__);\
		}
	}

#define LIB_INFO(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() >= INFO_LEVEL)\
		{\
			fprintf(stdout,fmt,##__VA_ARGS__);\
		}
	}

#define LIB_LOG(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() >= INFO_LEVEL)\
		{\
			fprintf(stdout,fmt,##__VA_ARGS__);\
		}
	}

#define LIB_WARN(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() >= WARN_LEVEL)\
		{\
			fprintf(stderr,fmt,##__VA_ARGS__);\
		}
	}

#define LIB_ERROR(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() >= ERROR_LEVEL)\
		{\
			fprintf(stderr,fmt,##__VA_ARGS__);\
		}
	}

#define LIB_FAULT(submod,fmt,...) \
	if((submod) & debug_module_state())\
	{\
		if(debug_get_module_log_level() >= FAULT_LEVEL)\
		{\
			fprintf(stderr,fmt,##__VA_ARGS__) ;\
		}
	}

#endif
