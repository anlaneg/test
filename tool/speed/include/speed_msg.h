/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件用于实现消息框架构造，
 * 发送，双方信息互换的框架。
 * 1.指定序号，说明发包数目及大小。说明
 */
#include <stdint.h>
#include "speed_module_register.h"
#include "bitmap.h"
#include "seq_msg.h"

typedef struct speed_module_single_msg{
	bitmap_t* rcv_bitmap;//已接收消息	
	bitmap_t* send_bitmap;//已发送消息
	seq_msg_t* send_buf;//发送缓冲
	seq_msg_t* rcv_buf;//接收缓冲
	uint32_t send_buf_len;//发送缓冲大小
	uint32_t rcv_buf_len;//接收缓冲大小
	uint32_t msg_send_total;//总共需要发送多少消息
	uint32_t msg_rcv_total;//总共需要接收多少消息
	uint32_t msg_send_success;//总共成功发送的消息数(含重发）
	uint32_t msg_send_fail;//总共发送失败的消息数(含重发)
	uint32_t msg_rcv_success;//总共接收成功的消息数(含重发)
	uint32_t msg_rcv_fail;//总共接收失败的消息数(含重发)
	struct timeval send_begin;//send开始时间
	struct timeval send_end;//send终止时间
	struct timeval rcv_begin;//rcv开始时间
	struct timeval rcv_end;//rcv终止时间
} speed_module_single_msg_t __attribute__((aligned(64)));

/**
 * 定义模块消息
 */
typedef struct speed_module_msg{
	speed_module_single_msg_t client;
	speed_module_single_msg_t server;
	speed_module_t* module;
}speed_module_msg_t;


int32_t speed_send_msg(speed_module_type_t type,speed_module_msg_t*msg);

int32_t speed_rcv_msg(speed_module_type_t type,speed_module_msg_t*msg);

int32_t speed_rcv_msg_validate(speed_module_msg_t*msg);
speed_module_msg_t* speed_module_msg_create(uint32_t msg_size,uint32_t msg_count);
void speed_module_msg_destroy(speed_module_msg_t*msg);

static inline speed_module_single_msg_t* speed_module_single_msg_get(speed_module_type_t type,speed_module_msg_t*msg)
{
	if(type == MODULE_CLIENT)
	{
		return &(msg->client);
	}
	assert(type == MODULE_SERVER);
	return &(msg->server);
}

