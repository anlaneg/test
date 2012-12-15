/*实现文件注释*/
#include "##FILE_NAME##_debug.h"

/*模块标记*/
uint32_t g_debug_module_flag ;

/*debug模块名称*/
const char* g_debug_module_name[##FILE_NAME_UPPER##_MODULE_COUNT]=
{
##DEBUG_MODULE_NAME##
}
