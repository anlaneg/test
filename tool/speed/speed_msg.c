/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件用于实现消息框架构造，
 * 发送，双方信息互换的框架。
 * 1.指定序号，说明发包数目及大小。说明
 */

typedef struct speed_module_msg{
	uint64_t* rcv_bitmap;//已接收消息	
	uint64_t* send_bitmap;//已发送消息
	char* write_buf;
	char* read_buf;
	uint32_t msg_send_cur;
	uint32_t msg_rcv_cur;
	speed_module_t * module;
	uint32_t write_buf_len;
	uint32_t read_buf_len;
	uint32_t msg_send_total;//总共需要发送多少消息
	uint32_t msg_rcv_total;//总共需要接收多少消息
}speed_module_msg_t;


int32_t speed_rcv_msg_validate(speed_module_msg_t*msg)
{
	//TODO  检查read_buf是否正确，如果正确，则确认收到，并更新状态
}

int32_t speed_send_msg(speed_module_msg_t*msg)
{
	//TODO 发送消息
}

int32_t speed_rcv_msg(speed_module_msg_t*msg)
{
	//TODO 
}
