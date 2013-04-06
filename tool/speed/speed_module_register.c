/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件用于实现模块注册
 */

/**
 * ipc模块接口
 */
typedef struct speed_module_handle
{
	char* name;//模块名
	handle_readn_fun  readn;
	handle_writen_fun writen;
	handle_init_fun   init;
	uint32_t prvate_size;
}speed_module_handle_t;

int32_t speed_module_register(speed_module_handle_t* module_handle);

int32_t speed_module_unregister(char*name);

