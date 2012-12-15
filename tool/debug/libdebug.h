
#include <stdint.h>
#include <string.h>


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


