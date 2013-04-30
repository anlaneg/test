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
#include <pthread.h>
#include <time.h>
#include <inttypes.h>

#include "time_util.h"
#include "speed_mem.h"
#include "speed_log.h"
#include "speed_args.h"
#include "speed_module_register.h"
#include "speed_msg.h"
#include "unix_speed_test.h"

int32_t speed_parser_argments(int argc,char**argv,speed_frame_args_t*args)
{
	return 0;
}

static speed_module_msg_t* speed_module_msg_init(const speed_frame_args_t * args)
{
	char* module_name="unix-udp-module";
	uint32_t msg_size = 64;
	uint32_t msg_count = 20000000;
	speed_module_msg_t* msg = speed_module_msg_create(msg_size,msg_count);
	if(!(msg->module = speed_module_find(module_name)))
	{
		speed_err("we can not find module '%s' \n",module_name);
		speed_module_msg_destroy(msg);
		return NULL;
	}
	return msg;
}

void* client_send(void*args)
{
	speed_module_msg_t* msg = (speed_module_msg_t*)args;
	if(speed_send_msg(MODULE_CLIENT,msg))
	{
		speed_err("send sequeue message fail!\n");
		return NULL;
	}
	
	return NULL;
}

void* server_rcv(void*args)
{
	speed_module_msg_t*msg = (speed_module_msg_t*)args;
	if(speed_rcv_msg(MODULE_SERVER,msg))
	{
		speed_err("rcv sequeue message fail!\n");
		return NULL;
	}
	return NULL;
}

void speed_module_result_display(speed_module_msg_t* module_msg)
{
	time_t local_time=time(NULL);
	struct tm* current_time = localtime(&local_time);
	
	printf("date %04d-%02d-%02d %02d:%02d:%02d\n",current_time->tm_year+1900,current_time->tm_mon+1,current_time->tm_mday,current_time->tm_hour,current_time->tm_min,current_time->tm_sec);
	printf("----------------------------------\n");
	printf("size\t\tsend:%u       rcv:%u\n",module_msg->client.send_buf_len,module_msg->server.rcv_buf_len);
	printf("plan to\t\tsend : %u	rcv : %u\n",module_msg->client.msg_send_total,module_msg->server.msg_rcv_total);
	printf("actually\t\tsend : %u     rcv : %u\n",module_msg->client.msg_send_success,module_msg->server.msg_rcv_success);
	printf("rate\t\tsend : %.2f%%   rcv : %.2f%%\n",((double)module_msg->client.msg_send_success)/((double)module_msg->client.msg_send_total)*100,((double)module_msg->server.msg_rcv_success)/((double)module_msg->server.msg_rcv_total)*100);
	printf("use time(microsecond)\t\tsend : %" PRIu64 "     rcv : %" PRIu64 "\n", time_diff(&module_msg->client.send_begin,&module_msg->client.send_end),time_diff(&module_msg->server.rcv_begin,&module_msg->server.rcv_end));
	printf("speed\t\tsend : %.2fM/s   rcv : %.2fM/s\n", ((double)module_msg->client.msg_send_success * module_msg->client.send_buf_len)/((double)time_diff(&module_msg->client.send_begin,&module_msg->client.send_end))*1000000/(1024*1024),((double)module_msg->server.msg_rcv_success* module_msg->server.rcv_buf_len)/((double)time_diff(&module_msg->server.rcv_begin,&module_msg->server.rcv_end)) * 1000000/(1024*1024));
	printf("-----------------------------------\n");
}

/**
 * 实现模块装载
 * @return 0 装载成功
 * @return !0 装载失败
 */
int32_t speed_load_module(void)
{
	if(unix_udp_module_init())
	{
		speed_log("load unix udp scket test fail!\n");
	}
	return 0;	
}

int main(int argc,char**argv)
{
	pthread_t client;
	pthread_t server;
	speed_module_msg_t* module_msg;
	if(speed_load_module())
	{
		speed_err("load module fail!\n");
		return 1;	
	}
	//parser argments
	if(speed_parser_argments(argc,argv,NULL))
	{
		speed_err("parser argments fail!\n");
		return 1;
	}

	//do init
	if(!(module_msg=speed_module_msg_init(NULL)))
	{
		speed_err("speed module message init fail!\n");
		return 1;
	}

	module_msg->module->server.init(module_msg->module->server.udata);
	module_msg->module->client.init(module_msg->module->client.udata);

	//client thread 
	if(pthread_create(&client,NULL,client_send,module_msg))
	{
		speed_err("client pthread create fail!\n");
		return -1;
	}	

	//server thread
	if(pthread_create(&server,NULL,server_rcv,module_msg))
	{
		speed_err("server pthread create fail!\n");
		return -1;
	}

	//join
	pthread_join(client,NULL);
	pthread_join(server,NULL);

	//dispaly result
	speed_module_result_display(module_msg);
	return 0;
}
