
/*文件头注释*/
#include <stdint.h>
#include "libdebug.h"

#ifndef ##FILE_NAME_UPPER##_DEBUG_H
#define ##FILE_NAME_UPPER##_DEBUG_H


/*定义模块数目*/
#define ##FILE_NAME_UPPER##_MODULE_COUNT (##DEBUG_MODULE_COUNT##ULL)

/*定义相应模块的对外标记*/
##DEBUG_MODULE_MACRO_FLAG##

/*模块标记*/
extern uint32_t g_debug_module_flag;

/*debug模块名称*/
extern const char* g_debug_module_name[##FILE_NAME_UPPER##_MODULE_COUNT + 1];

/**
 * 开启模块函数
 * @param[in] module_name 要开启的模块名称,例如"##DEBUG_MODULE_EXAMPLE##"
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
 * @param[in] module_name 要关闭的模块名称，例如"##DEBUG_MODULE_EXAMPLE##"
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
	g_debug_module_flag = (1ULL << (##FILE_NAME_UPPER##_MODULE_COUNT + 1)) -1;
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
 * @param[in] module_name 模块名称，例如"##DEBUG_MODULE_EXAMPLE##"
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
