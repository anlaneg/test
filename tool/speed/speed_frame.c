/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件用于实现IPC测速软件框架。此框架
 * 对待测速的机制有如下假设：
 * 1.被测IPC机制必须支持大于N字节的传输
 * 2.被测IPC机制必须可实现write_n,read_n方法
 * 3.被测IPC机制至少可实现两个进程间通信
 *
 * 此框架采用以下方式测试:
 * 1.消息长度N字节，获取消息传输速度（发送，接受）
 * 2.单向传递
 * 3.双向传递
 * 4.可通过参数设置框架，可通过参数自定义插件处理。
 */
#include <stdint.h>

/**
 * 模块名最大长度
 */
#define SPEED_MAX_MODULE_NAME_LENGTH (31ULL)

typedef enum speed_module_type
{
	MODULE_CLIENT,
	MODULE_SERVER;
	
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
typedef int32_t (*handle_init_fun)   (void* udata,speed_module_type_t type);

/**
 * module 访问函数
 * @param[inout] module 模块名
 * @param[in] args 参数
 * @return 0 继续访问
 * @return !0 停止访问
 */
typedef int32_t (*module_access_fun) (speed_module_t*module,void*args);

/**
 * 模块定义
 */
typedef sturct speed_module
{
	char name[SPEED_MAX_MODULE_NAME_LENGTH+1];//模块名
	handle_readn_fun readn;//读函数
	handle_writen_fun writen;//写函数
	handle_init_fun init;//初始函数
	void* udata;//udata	
	uint32_t udata_size;//udate大小
	struct speed_module*next;//指向module
}speed_module_t;


speed_module_t g_speed_modules;

static inline int32_t speed_module_add(speed_module_handle_t*module_handle)
{
}

static inline int32_t speed_module_del(char*name)
{
}

static inline speed_module_t* speed_module_find(char*name)
{
}

static inline speed_module_t* speed_module_foreach(module_access_fun access_fun,void*args)
{
}
