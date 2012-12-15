
/*文件头注释*/
#include <stdint.h>
#include "libdebug.h"

#ifndef PROCESS_DEBUG_H
#define PROCESS_DEBUG_H


/*定义模块数目*/
#define PROCESS_MODULE_COUNT (4ULL)

/*定义相应模块的对外标记*/
#define HELLO_MODULE (1ULL << 4) /*控制hello模块*/
#define WORLD_MODULE (1ULL << 4) /*控制world模块*/
#define LOG_MODULE (1ULL << 4) /*控制world模块*/
#define TEST_MODULE (1ULL << 4) /*控制world模块*/


/*模块标记*/
extern uint32_t g_debug_module_flag;

/*debug模块名称*/
extern const char* g_debug_module_name[PROCESS_MODULE_COUNT + 1];

/**
 * 开启模块函数
 * @param[in] module_name 要开启的模块名称,例如"HELLO_MODULE"
 * @return 无
 * 注意：如果module_name未定义，则此函数不启作用
 */
static inline void debug_module_enable(const char*module_name)
{
	int32_t idx;
	if((idx = debug_get_module_name_index(g_debug_module_name,module_name)) < 0)
	{
		//TODO error index
		return ;
	}

	g_debug_module_flag |= (1ULL << idx);	
}

/**
 * 关闭模块函数
 * @param[in] module_name 要关闭的模块名称，例如"HELLO_MODULE"
 * @return 无
 * 注意：如果module_name未定义，则此函数不启作用
 */
static inline void debug_module_disable(const char*module_name)
{
	int32_t idx;
	if((idx = debug_get_module_name_index(g_debug_module_name,module_name)) < 0)
	{
		//TODO error index
		return ;
	}

	g_debug_module_flag &= (~(1ULL << idx));
}

/**
 * 开启所有模块函数
 */
static inline void debug_module_enable_all()
{
	g_debug_module_flag = (1ULL << (PROCESS_MODULE_COUNT + 1)) -1;
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
 * 模块模块是否被开启
 * @param[in] module_name 模块名称，例如"HELLO_MODULE"
 * @return 0 此模块未开启
 * @return !0 此模块已开启
 */
static inline int32_t debug_module_is_enable(const char*module_name)
{
	int32_t idx;
	if((idx = debug_get_module_name_index(g_debug_module_name,module_name)) < 0)
	{
		//TODO error index
		return 0;
	}	

	return g_debug_module_flag & (1ULL << idx);
}

#endif
