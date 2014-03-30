
#ifndef JP_DEBUG_H
#define JP_DEBUG_H

/*文件头注释*/
#include <stdint.h>
#include "libdebug.h"
#include "liblog.h"

/*定义模块数目*/
#define JP_MODULE_COUNT (5ULL)

/*定义相应模块的对外标记*/
#define CORE (1ULL << 0) /*核心模块*/
#define GEN (1ULL << 1) /*生成模块*/
#define PARSER (1ULL << 2) /*解析模块*/
#define DEBUG (1ULL << 3) /*debug模块*/
#define FRAME (1ULL << 4) /*frame模块*/


/*debug模块名称*/
extern const char* g_debug_module_name[JP_MODULE_COUNT + 1];

/**
 * 开启模块函数
 * @param[in] module_name 要开启的模块名称,例如"CORE"
 * @return 0 开启成功
 * @return !0 开启失败(module_name未定义)
 */
static inline int32_t debug_module_enable(const char*module_name)
{
	int32_t idx;
	if((idx = debug_get_module_name_index(g_debug_module_name,module_name)) < 0)
	{
		return -1;
	}

	g_debug_module_flag |= (1ULL << idx);	
	return 0;
}

/**
 * 关闭模块函数
 * @param[in] module_name 要关闭的模块名称，例如"CORE"
 * @return 0 关闭成功
 * @return !0 关闭失败(module_name未定义)
 */
static inline int32_t debug_module_disable(const char*module_name)
{
	int32_t idx;
	if((idx = debug_get_module_name_index(g_debug_module_name,module_name)) < 0)
	{
		return -1;
	}

	g_debug_module_flag &= (~(1ULL << idx));
	return 0;
}

/**
 * 开启所有模块函数
 */
static inline void debug_module_enable_all()
{
	g_debug_module_flag = (1ULL << (JP_MODULE_COUNT + 1)) -1;
}


/**
 * 模块模块是否被开启
 * @param[in] module_name 模块名称，例如"CORE"
 * @return 0 此模块未开启
 * @return !0 此模块已开启
 */
static inline int32_t debug_module_is_enable(const char*module_name)
{
	int32_t idx;
	if((idx = debug_get_module_name_index(g_debug_module_name,module_name)) < 0)
	{
		return 0;
	}	

	return g_debug_module_flag & (1ULL << idx);
}

#endif
