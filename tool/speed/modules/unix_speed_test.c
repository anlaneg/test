
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
#include "unix_speed_test.h"

/**
 * 读取n字节至msg_buf中
 * @param [inout] udata 用户私有数据
 * @param [out] msg_buf 消息缓存,缓存长度为n
 * @param [in] n 要读取的字节数
 * @return 0 读取成功
 * @return !0 读取失败
 */
int32_t unix_udp_server_readn(unix_udp_server_udata_t* info,char* msg_buf,uint32_t n)
{
	uint32_t actual_reads = 0;
	int32_t readn;
	while(actual_reads < n)
	{
		if((readn=recvfrom(info->server_fd,msg_buf+actual_reads,n-actual_reads,0,NULL,NULL)) <= 0)
		{
			speed_err("recv from client fail,error message \"%s\"\n",strerror(errno));
			return -1;
		}
		actual_reads += readn;
	}
	return 0;
}

/**
 * 写入n字节至msg_buf中
 * @param[inout] udata 用户私有数据
 * @param[out] msg_buf 消息缓存，缓存长度为n
 * @param[in] n 要写入的字节数
 * @return 0 写入成功
 * @return !0 写入失败
 */
int32_t unix_udp_client_writen(unix_udp_client_udata_t*info,char* msg_buf,uint32_t n)
{
	uint32_t actual_writes = 0;
	int32_t writen;
	while(actual_writes < n)
	{
		if((writen=sendto(info->client_fd,msg_buf+actual_writes,n-actual_writes,0,(struct sockaddr *)&info->server_addr,sizeof(info->server_addr))) <= 0)
		{
			speed_err("write to server fail,error message \"%s\" \n",strerror(errno));
			return -1;
		}
		actual_writes += writen;
	}
	return 0;
}

/**
 * 实现unix udp方式客户端初始化
 * @param[in] udata
 * @return 0 初始化成功
 * @return !0　初始化失败
 */
int32_t unix_udp_client_init(unix_udp_client_udata_t*udata)
{
	if( (udata->client_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
	{
		speed_err("we create client unix socket fail! error message :\"%s\"",strerror(errno));
		return -1;
	}

	memset(&(udata->server_addr), 0, sizeof(udata->server_addr));
	udata->server_addr.sun_family = AF_UNIX;
	strcpy(udata->server_addr.sun_path,UNIX_UDP_BIND_NAME);

	return 0;
}

/**
 * 实现unix udp方式服务器端初始化
 * @param[in] udata
 * @return 0 初始化成功
 * @return !0　初始化失败
 */
int32_t unix_udp_server_init(unix_udp_server_udata_t*udata)
{
	int fd;
	struct sockaddr_un ipcFile;

	memset(&ipcFile, 0, sizeof(ipcFile));

	ipcFile.sun_family = AF_UNIX;
	strcpy(ipcFile.sun_path,UNIX_UDP_BIND_NAME);
	if((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
	{
		speed_err("we create unix socket fail,error messge :\"%s\"",strerror(errno));
		return -1;
	}
	unlink(ipcFile.sun_path);
	if(bind(fd, (struct sockaddr *) &ipcFile, sizeof(ipcFile)))
	{
		speed_err("we bind unix udp socket to \"%s\" fail,error message : \"%s\"",ipcFile.sun_path,strerror(errno));
		return -1;
	}

	udata->server_fd = fd;	
	return 0;
}

