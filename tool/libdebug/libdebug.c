#include "libdebug.h"

/*模块标记*/
uint32_t g_debug_module_flag =~(0ULL);

/*log级别*/
enum lib_debug_level g_debug_level = DEBUG_LEVEL;
