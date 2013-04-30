
/**
 * @author:along
 * @date  :2013-04-06
 * @brief : 本文用于提供unix udp通信测试
 */
#include <stdint.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "speed_log.h"
#include "speed_module_register.h"

#ifndef UNIX_SPEED_TEST_H
#define UNIX_UDP_BIND_NAME "./.unix_speed.test"

typedef struct unix_udp_client_udata
{
	int client_fd;
	struct sockaddr_un server_addr;
}unix_udp_client_udata_t;

typedef struct unix_udp_server_udata
{
	int server_fd;
}unix_udp_server_udata_t;

/**
 * 读取n字节至msg_buf中
 * @param [inout] udata 用户私有数据
 * @param [out] msg_buf 消息缓存,缓存长度为n
 * @param [in] n 要读取的字节数
 * @return 0 读取成功
 * @return !0 读取失败
 */
int32_t unix_udp_server_readn(unix_udp_server_udata_t*udata,char* msg_buf,uint32_t n);

/**
 * 写入n字节至msg_buf中
 * @param[inout] udata 用户私有数据
 * @param[out] msg_buf 消息缓存，缓存长度为n
 * @param[in] n 要写入的字节数
 * @return 0 写入成功
 * @return !0 写入失败
 */
int32_t unix_udp_client_writen(unix_udp_client_udata_t*udata,char* msg_buf,uint32_t n);

/**
 * 实现unix udp方式客户端初始化
 * @param[in] udata
 * @return 0 初始化成功
 * @return !0　初始化失败
 */
int32_t unix_udp_client_init(unix_udp_client_udata_t*udata);

/**
 * 实现unix udp方式服务器端初始化
 * @param[in] udata
 * @return 0 初始化成功
 * @return !0　初始化失败
 */
int32_t unix_udp_server_init(unix_udp_server_udata_t*udata);

static inline int32_t unix_udp_module_init()
{
	speed_module_handle_t unix_udp_handle;

	memset(&unix_udp_handle,0,sizeof(speed_module_handle_t));

	unix_udp_handle.name ="unix-udp-module";

	unix_udp_handle.client.writen=(handle_writen_fun)unix_udp_client_writen;
	unix_udp_handle.client.init = (handle_init_fun)unix_udp_client_init;
	unix_udp_handle.client.private_size = sizeof(unix_udp_client_udata_t);

	unix_udp_handle.server.readn=(handle_readn_fun)unix_udp_server_readn;
	unix_udp_handle.server.init = (handle_init_fun)unix_udp_server_init;
	unix_udp_handle.server.private_size = sizeof(unix_udp_server_udata_t);
	

	return speed_module_register(&unix_udp_handle);	
}

#endif //UNIX_SPEED_TEST_H
