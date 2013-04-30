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
#include <assert.h>
#include <string.h>

#include "speed_mem.h"
#include "speed_log.h"
#include "speed_module_register.h"

//find argment
struct module_find_args
{
	const char* name;
	speed_module_t* find;
};

/**
 * 模块头
 */
speed_module_t g_speed_modules={
	.name={0},
	.client={.readn=NULL,
	.writen=NULL,
	.init=NULL,
	.udata=NULL,
	.udata_size=0,
	},
	.server={.readn=NULL,
	.writen=NULL,
	.init=NULL,
	.udata=NULL,
	.udata_size=0,
	},
	.next=NULL,
	.prev=NULL
};

static inline speed_module_t* speed_module_new(speed_module_handle_t*module_handle)
{
	speed_module_t* module = speed_memory_alloc(sizeof(speed_module_t) + module_handle->client.private_size + module_handle->server.private_size);
	if(module)
	{
		strncpy(module->name,module_handle->name,SPEED_MAX_MODULE_NAME_LENGTH);
		module->name[SPEED_MAX_MODULE_NAME_LENGTH]='\0';
		module->client.readn  = module_handle->client.readn;
		module->server.readn  = module_handle->server.readn;
		module->client.writen = module_handle->client.writen;
		module->server.writen = module_handle->server.writen;
		module->client.init   = module_handle->client.init;
		module->server.init   = module_handle->server.init;
		module->client.destroy   = module_handle->client.destroy;
		module->server.destroy   = module_handle->server.destroy;
		module->client.udata  = (uint8_t*)(module+sizeof(speed_module_t));
		module->server.udata  = (uint8_t*)(module+sizeof(speed_module_t)+ module_handle->client.private_size);
		module->client.udata_size = module_handle->client.private_size;
		module->server.udata_size = module_handle->server.private_size;
	}

	return module;
}

static int32_t speed_module_add(speed_module_t* prev_module,speed_module_handle_t*module_handle,speed_module_t* next_module)
{
	assert(prev_module);
	assert(module_handle);
	assert(module_handle->name);
	assert(module_handle->client.readn || module_handle->server.readn);
	assert(module_handle->client.writen || module_handle->server.writen);
	assert(module_handle->client.init);
	assert(module_handle->server.init);
	speed_module_t* module_new=speed_module_new(module_handle);
	if(!module_new)
	{
		speed_err("module alloc fail!\n");
		return -1;
	}

	module_new->next = next_module;
	module_new->prev = prev_module;
	prev_module->next     = module_new;
	
	if(next_module)
	{
		next_module->prev = module_new;
	}
	return 0;	
}

static int32_t module_del(speed_module_t* module,void*args)
{
	const char* name = (const char*)args;
	assert(module);
	assert(name);
	
	if(!strcmp(name,module->name))
	{
		module->prev->next = module->next;
		if(module->next)
		{
			module->next->prev = module->prev;
		}
		//free module
		speed_memory_free(module);
		return 1;
	}
	return 0;
}



static int32_t module_find(speed_module_t* module,void*args)
{
	struct module_find_args* find_args = (struct module_find_args*) args;
	
	assert(module);
	assert(find_args);
	
	if(!strcmp(find_args->name,module->name))
	{
		find_args->find=module;
		return 1;
	}
	return 0;
}

/**
 * 遍历所有module
 * @param[in] access_fun 访问函数
 * @param[inout] args 参数 
 * @return 0 访问成功
 * @return !0 访问失败
 */
int32_t speed_module_foreach(module_access_fun access_fun,void*args)
{
	int32_t ret;
	speed_module_t* module;
	speed_module_t* next;
	for(module=g_speed_modules.next;module;module=next)
	{
		next = module->next;
		if((ret=access_fun(module,args)))
		{
			return ret;
		}
	}
	return 0;
}

/**
 * 模块查询
 * @param[in] name 要查询的模块名称
 * @return NULL 查询失败
 * @return !NULL 查询成功
 */
speed_module_t* speed_module_find(const char*name)
{
	struct module_find_args	args={
	.name=name,
	.find=NULL
	};

	if(speed_module_foreach(module_find,&args))
	{
		return args.find;
	}
	
	return NULL;
}

/**
 * 模块注册函数
 * @param[in] module_hannle 模块handle
 * @return 0 注册成功
 * @return !0 注册失败
 */
int32_t speed_module_register(speed_module_handle_t* module_handle)
{
	assert(module_handle);
	assert(module_handle->name);

	speed_module_t* module = speed_module_find(module_handle->name);
	if(module)
	{
		speed_err("speed module exsit %s\n",module_handle->name);
		return -1;
	}

	return speed_module_add(&g_speed_modules,module_handle,g_speed_modules.next);		
}

/**
 * 模块解注册
 * @param[in] name 模块名称
 * @return 0 解注册成功
 * @return !0 解注册失败
 */
int32_t speed_module_unregister(char*name)
{
	return !speed_module_foreach(module_del,name);
}
