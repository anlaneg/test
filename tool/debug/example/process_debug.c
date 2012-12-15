/*实现文件注释*/
#include "process_debug.h"

/*模块标记*/
uint32_t g_debug_module_flag ;

/*debug模块名称*/
const char* g_debug_module_name[PROCESS_MODULE_COUNT + 1]=
{
"hello",
"world",
"log",
"test",
NULL

};
