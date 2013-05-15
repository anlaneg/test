#ifndef LIBDEBUG_H
#define LIBDEBUG_H

#include <stdint.h>
#include <string.h>

enum lib_debug_level
{
	DEBUG_LEVEL=1,
	INFO_LEVEL,
	LOG_LEVEL,
	WARN_LEVEL,
	ERROR_LEVEL,
	FAULT_LEVEL	
};

/*模块标记*/
extern uint32_t g_debug_module_flag ;

/*log级别*/
extern enum lib_debug_level g_debug_level;

/**
 * 获取debug模块名称对应的索引
 * @param[in] debug_module_names debug模块名称数组
 * @param[in] module_name 模块名称
 * @return -1 获取失败
 * @return >=0 获取成功
 */
static inline int32_t  debug_get_module_name_index(const char* debug_module_names[],const char* module_name)
{
	int32_t idx ;
	for( idx = 0 ; debug_module_names[idx] ; ++idx)
	{
		if(!strcmp(debug_module_names[idx],module_name))
		{
			return idx;
		}
	}	

	return -1;
}

/**
 * 关闭所有模块函数
 */	
static inline void debug_module_disable_all()
{
	g_debug_module_flag = 0;
}

/**
 * 获取模块的debug状态
 * @return 模块状态
 */
static inline uint32_t debug_module_state()
{
	return g_debug_module_flag;
}

/**
 * 获取模块log 级别
 * @return log级别
 */
static inline  enum lib_debug_level debug_get_module_log_level()
{
	return g_debug_level;
}

#endif
