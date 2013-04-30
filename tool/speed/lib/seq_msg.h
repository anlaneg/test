/**
 * @author:along
 * @date: 2013-04-06
 * @brief:本文件实现speed的序号消息
 */
#include <stdint.h>
#include <arpa/inet.h>

typedef struct seq_msg
{
	uint32_t magic;
	uint32_t seq;
	uint32_t len;
	uint8_t data[0];	
}seq_msg_t;

#define SEQ_MSG_MAGIC (0X0deadadd)

static inline void seq_msg_head_set_len(seq_msg_t*msg,uint32_t len)
{
	assert(msg);
	msg->len = htonl(len);	
}

static inline uint32_t seq_msg_head_get_len(seq_msg_t*msg)
{
	assert(msg);
	return ntohl(msg->len);
}

static inline void seq_msg_head_set_seq(seq_msg_t*msg,uint32_t seq)
{
	assert(msg);
	msg->seq = htonl(seq);
}

static inline uint32_t seq_msg_head_get_seq(seq_msg_t*msg)
{
	assert(msg);
	return ntohl(msg->seq);
}

static inline void seq_msg_head_set_magic(seq_msg_t*msg,uint32_t magic)
{
	assert(msg);
	msg->magic = htonl(magic);	
}

static inline uint32_t seq_msg_head_get_magic(seq_msg_t*msg)
{
	assert(msg);
	return ntohl(msg->magic);
}

static inline seq_msg_t* seq_msg_create(uint32_t len)
{
	seq_msg_t* msg;
	if((msg=speed_memory_alloc(sizeof(seq_msg_t)+sizeof(uint8_t)*len)))
	{
		seq_msg_head_set_magic(msg,SEQ_MSG_MAGIC);
		seq_msg_head_set_seq(msg,0);
		seq_msg_head_set_len(msg,len);
	}
		
	return msg;		
}

static inline void seq_msg_destroy(seq_msg_t*msg)
{
	assert(msg);
	speed_memory_free(msg);
}

static inline uint8_t* seq_msg_get_data(seq_msg_t*msg)
{
	assert(msg);
	return msg->data;
}
