/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件用于实现模块注册
 */
#ifndef SPEED_MODULE_REGISTER_H
#define SPEED_MODULE_REGISTER_H

#include <assert.h>
/**
 * 模块名最大长度
 */
#define SPEED_MAX_MODULE_NAME_LENGTH (31ULL)


#define SPEED_MODULE_REGISTER_FUNCTION_DECLARE(readn,writen,init,destroy)\
extern int32_t readn(void*udata,char*msg_buf,uint32_t n);\
extern int32_t writen(void*udata,char*msg_buf,uint32_t n);\
extern int32_t init (void* udata);\
extern int32_t destroy(void*udata);


/**
 * 为了进行速度测试，要求实现client,与server
 * client将首先发起会话，需要保证client连接到server
 * server可响应client的请求
 */
typedef enum speed_module_type
{
	MODULE_CLIENT,
	MODULE_SERVER
}speed_module_type_t;

/**
 * 读取n字节至msg_buf中
 * @param [inout] udata 用户私有数据
 * @param [out] msg_buf 消息缓存,缓存长度为n
 * @param [in] n 要读取的字节数
 * @return 0 读取成功
 * @return !0 读取失败
 */
typedef int32_t (*handle_readn_fun) (void* udata,char* msg_buf,uint32_t n);

/**
 * 写入n字节至msg_buf中
 * @param[inout] udata 用户私有数据
 * @param[out] msg_buf 消息缓存，缓存长度为n
 * @param[in] n 要写入的字节数
 * @return 0 写入成功
 * @return !0 写入失败
 */
typedef int32_t (*handle_writen_fun) (void* udata,char* msg_buf,uint32_t n);

/**
 * 初始化对应类型
 * @param[inout] udata 用户私有数据
 * @param[int] type 初始化类型
 * @return 0 实始化成功
 * @return !0 初始化失败
 */
typedef int32_t (*handle_init_fun) (void* udata);

/**
 * 销毁对应类型
 * @param[inout] udata 用户私有数据
 * @param[int] type 初始化类型
 * @return 0 实始化成功
 * @return !0 初始化失败
 */
typedef int32_t (*handle_destroy_fun)(void*udata);

/**
 * ipc模块接口
 */
typedef struct speed_module_handle
{
	char* name;//模块名
	struct {
	handle_readn_fun  readn;//readn函数
	handle_writen_fun writen;//writen函数
	handle_init_fun   init;//init函数
	handle_destroy_fun   destroy;//destroy函数
	uint32_t private_size;//private struct size
	}client,server;
}speed_module_handle_t;


typedef struct speed_module_util
{
	handle_readn_fun readn;//读函数
	handle_writen_fun writen;//写函数
	handle_init_fun init;//初始函数
	handle_destroy_fun destroy;//destroy函数
	void* udata;//udata
	uint32_t udata_size;//udate大小
}speed_module_util_t;

/**
 * 模块定义
 */
typedef struct speed_module
{
	char name[SPEED_MAX_MODULE_NAME_LENGTH+1];//模块名
	speed_module_util_t client;
	speed_module_util_t server;
	struct speed_module*next;//指向module
	struct speed_module*prev;//指向module
}speed_module_t;

/**
 * module 访问函数
 * @param[inout] module 模块名
 * @param[in] args 参数
 * @return 0 继续访问
 * @return !0 停止访问
 */
typedef int32_t (*module_access_fun) (struct speed_module* module,void*args);


/**
 * 模块注册函数
 * @param[in] module_hannle 模块handle
 * @return 0 注册成功
 * @return !0 注册失败
 */
int32_t speed_module_register(speed_module_handle_t* module_handle);

/**
 * 模块解注册
 * @param[in] name 模块名称
 * @return 0 解注册成功
 * @return !0 解注册失败
 */
int32_t speed_module_unregister(char*name);

/**
 * 模块查询
 * @param[in] name 要查询的模块名称
 * @return NULL 查询失败
 * @return !NULL 查询成功
 */
speed_module_t* speed_module_find(const char*name);

/**
 * 遍历所有module
 * @param[in] access_fun 访问函数
 * @param[inout] args 参数 
 * @return 0 访问成功
 * @return !0 访问失败
 */
int32_t speed_module_foreach(module_access_fun access_fun,void*args);

static inline speed_module_util_t* speed_module_util_get(speed_module_type_t type,speed_module_t* module)
{
	if(type == MODULE_CLIENT)
	{
		return &(module->client);
	}
	assert(type == MODULE_SERVER);
	return &(module->server);
}

#endif //SPEED_MODULE_REGISTER_H
