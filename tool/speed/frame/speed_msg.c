/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件用于实现消息框架构造，
 * 发送，双方信息互换的框架。
 * 1.指定序号，说明发包数目及大小。说明
 */

#include <stdint.h>
#include <sys/time.h>

#include "speed_module_register.h"
#include "speed_msg.h"
#include "speed_log.h"



int32_t speed_rcv_msg_validate(speed_module_msg_t*msg)
{
	//TODO  检查read_buf是否正确，如果正确，则确认收到，并更新状态
	return -1;
}

/**
 * 发送消息
 * @param[in] msg 发送缓存
 * @return 0 返回成功
 * @return !0 返回失败
 */
int32_t speed_send_msg(speed_module_type_t type,speed_module_msg_t*msg)
{
	//TODO 发送消息
	assert(msg);
	assert(msg->module);
	
	uint32_t send_cur ;
	speed_module_util_t* module_util=speed_module_util_get(type,msg->module);
	speed_module_single_msg_t* single_msg = speed_module_single_msg_get(type,msg);
	if(gettimeofday(&single_msg->send_begin,NULL))
	{
		speed_log("we get rcv begin time fail!\n");
	}

	for(send_cur = 0; send_cur < single_msg->msg_send_total; send_cur ++)
	{
		seq_msg_head_set_seq(single_msg->send_buf,send_cur);
		if(module_util->writen(module_util->udata,(char*)single_msg->send_buf,single_msg->send_buf_len))
		{
			bitmap_set(single_msg->send_bitmap,send_cur);
			continue;
		}
		single_msg->msg_send_success++;
	}

	if(gettimeofday(&single_msg->send_end,NULL))
	{
		speed_log("we get rcv end time fail!\n");
	}
	return 0;
}

/**
 * 收报文函数
 * @param[in] msg 接收缓存
 * @return 0 返回成功
 * @return !0 返回失败
 */
int32_t speed_rcv_msg(speed_module_type_t type,speed_module_msg_t*msg)
{
	//TODO 
	assert(msg);
	assert(msg->module);

	uint32_t rcv_cur ;
	speed_module_single_msg_t* single_msg = speed_module_single_msg_get(type,msg);
	speed_module_util_t* module_util = speed_module_util_get(type,msg->module);
	if(gettimeofday(&single_msg->rcv_begin,NULL))
	{
		speed_log("we get rcv begin time fail!\n");
	}

	for(rcv_cur = 0; rcv_cur < single_msg->msg_rcv_total; rcv_cur ++)
	{
		if(module_util->readn(module_util->udata,(char*)single_msg->rcv_buf,single_msg->rcv_buf_len))
		{
			continue;
		}
		uint32_t seq = seq_msg_head_get_seq(single_msg->rcv_buf);
		bitmap_set(single_msg->rcv_bitmap,seq);
		single_msg->msg_rcv_success++;
	}

	if(gettimeofday(&single_msg->rcv_end,NULL))
	{
		speed_log("we get rcv end time fail!\n");
	}
		
	return 0;
}

speed_module_msg_t* speed_module_msg_create(uint32_t msg_size,uint32_t msg_count)
{
	assert(msg_size > 16);
	speed_module_msg_t* msg = speed_memory_alloc(sizeof(speed_module_msg_t));
	if(msg)
	{
		memset(msg,0,sizeof(speed_module_msg_t));
		msg->client.rcv_bitmap  = bitmap_create(msg_count);
		msg->client.send_bitmap = bitmap_create(msg_count);
		msg->client.send_buf   = seq_msg_create(msg_size);
		msg->client.rcv_buf    = seq_msg_create(msg_size);
		
		msg->client.send_buf_len = msg_size;
		msg->client.rcv_buf_len  = msg_size;
		msg->client.msg_send_total = msg_count;
		msg->client.msg_rcv_total = msg_count;

		msg->module = NULL;

		msg->server.rcv_bitmap  = bitmap_create(msg_count);
		msg->server.send_bitmap = bitmap_create(msg_count);
		msg->server.send_buf   = seq_msg_create(msg_size);
		msg->server.rcv_buf    = seq_msg_create(msg_size);
		
		msg->server.send_buf_len = msg_size;
		msg->server.rcv_buf_len  = msg_size;
		msg->server.msg_send_total = msg_count;
		msg->server.msg_rcv_total = msg_count;

	}		
	return msg;
}

void speed_module_msg_destroy(speed_module_msg_t*msg)
{
	if(msg)
	{
		speed_memory_free(msg);
	}
}

