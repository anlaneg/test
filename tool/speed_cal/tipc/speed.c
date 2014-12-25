#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#define __USE_GNU
#include<sched.h>
#include <sys/types.h>

#define SPEED_PROTO_NAME_MAX_LENGTH (31ULL)
#define ERROR(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)

typedef int32_t (*proto_service_init_fun)(uint32_t,uint32_t);
typedef int32_t (*proto_client_init_fun)(uint32_t,uint32_t);
typedef int32_t (*proto_rcv_fun)(char*,uint32_t,int32_t);
typedef int32_t (*proto_send_fun)(char*,uint32_t,int32_t,uint32_t,uint32_t);

int32_t tipc_rdm_init(uint32_t,uint32_t);
int32_t tipc_rdm_rcv(char*,uint32_t,int32_t);
int32_t tipc_rdm_send(char*,uint32_t,int32_t,uint32_t,uint32_t);

struct speed_support_proto
{
	proto_service_init_fun sinit;
	proto_client_init_fun cinit;
	proto_rcv_fun rcv;
	proto_send_fun send;	
	char name[SPEED_PROTO_NAME_MAX_LENGTH+1];
};

struct speed_support_proto g_support_proto[]=
{
	{tipc_rdm_init,tipc_rdm_init,tipc_rdm_rcv,tipc_rdm_send,"TIPC_RDM"},
	{NULL,NULL,NULL,NULL,"\0"}
};

struct timeval begin_time, end_time, result_time;
/**
 * 功能：将当前进程绑定在指定的CPU上。
 * 参数:@cpu_id 指定要绑定的cpu
 * 返回：如果绑定cpu成功，返回0，否则返回－1
 */
int bind_cup(int cup_id)
{
	//绑定CPU
	int num = sysconf(_SC_NPROCESSORS_CONF);
	if (cup_id >= num)
	{
		ERROR("当前仅有%d个CPU,无法绑定至%d上(cpu编号自0起)\n", num, cup_id);
		return -1;
	}
	cpu_set_t mask, get;
	CPU_ZERO(&mask);

	//绑定CPU
	CPU_SET(cup_id, &mask);
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
	{
		ERROR("无法绑定到CPU 0\n");
		return -1;
	}
	//检查绑定情况
	CPU_ZERO(&get);
	if (sched_getaffinity(0, sizeof(get), &get) == -1)
	{
		ERROR("无法获取CPU绑定情况\n");
		return -1;
	}
	if (!(CPU_ISSET(0, &get)))
	{
		ERROR("绑定CPU 0后没有起效！");
		return -1;
	}
	return 0;
}

static int32_t do_service(struct speed_support_proto*proto, uint32_t msg_len,uint32_t msg_count)
{
	char*sbuf;
	char*rbuf;
	int32_t i;
	int32_t fd = proto->sinit(69,3);
	if(fd < 0)
	{
		ERROR("server init fail!\n");
		return -1;
	}
	
	sbuf=malloc(msg_len * 2);
	if(sbuf == NULL)
	{
		ERROR("malloc send and rcv buffer fail\n");
		return -1;
	}

	rbuf=sbuf+msg_len;
	if(proto->rcv(rbuf,msg_len,fd))
	{
		ERROR("rcv buffer fail!\n");
		return -1;
	}
	//开始计时
	if (gettimeofday(&begin_time, NULL) != 0)
	{
		ERROR("获得系统时间失败！");
		return -1;
	}
	for(i = 0 ; i < msg_count ;++i)
	{
		if(proto->send(sbuf,msg_len,fd,68,4))
		{
			ERROR("send buffer fail!\n");
			break;
		}

		if(proto->rcv(rbuf,msg_len,fd))
		{
			ERROR("rcv buffer fail!\n");
			break;
		}
	}
	//结束计时
	if (gettimeofday(&end_time, NULL) != 0)
	{
		ERROR("获得系统时间失败！");
		return -1;
	}
	return (i-msg_count);
}

static int32_t do_client(struct speed_support_proto*proto, uint32_t msg_len,uint32_t msg_count)
{	
	char*sbuf;
	char*rbuf;
	int32_t i;
	int32_t fd = proto->cinit(68,4);
	if(fd < 0)
	{
		ERROR("server init fail!\n");
		return -1;
	}
	
	sbuf=malloc(msg_len * 2);
	if(sbuf == NULL)
	{
		ERROR("malloc send and rcv buffer fail\n");
		return -1;
	}

	rbuf=sbuf+msg_len;
	if(proto->send(sbuf,msg_len,fd,69,3))
	{
		ERROR("send buffer fail!\n");
		return -1;
	}

	//开始计时
	if (gettimeofday(&begin_time, NULL) != 0)
	{
		ERROR("获得系统时间失败！");
		return -1;
	}
	for(i = 0 ; i < msg_count ;++i)
	{
		if(proto->send(sbuf,msg_len,fd,69,3))
		{
			ERROR("send buffer fail!\n");
			break;
		}

		if(proto->rcv(rbuf,msg_len,fd))
		{
			ERROR("rcv buffer fail!\n");
			break;
		}
	}
	//结束计时
	if (gettimeofday(&end_time, NULL) != 0)
	{
		ERROR("获得系统时间失败！");
		return -1;
	}
	return (i-msg_count);

}

int main(int argc,char**argv)
{
	struct speed_support_proto*proto;
	uint32_t msg_len = 140;
	uint32_t msg_count=200000;	
	for(proto=g_support_proto;proto->name[0]!='\0';proto++)
	{
		if(argc == 2)
		{
			ERROR("do_service\n");	
			if(do_service(proto,msg_len,msg_count))
			{
				ERROR("do server fail!\n");
				return -1;
			}
		}
		else
		{
			ERROR("do_client\n");	
			bind_cup(0);
			if(do_client(proto,msg_len,msg_count))
			{
				ERROR("do client fail!\n");
				return -1;
			}
		}
	}

	//计算时差
	result_time.tv_sec = end_time.tv_sec - begin_time.tv_sec;
	result_time.tv_usec = end_time.tv_usec - begin_time.tv_usec;

	//换算到微秒上去
	result_time.tv_usec = result_time.tv_usec + (result_time.tv_sec * 1000000);

	//求出结果(单位M/s)
	int64_t byte_transmission = (int64_t)msg_len 
			* (int64_t) msg_count;
	double transmission_m_byte = byte_transmission / (double) (1024 * 1024);

	double myresult = ((double) (transmission_m_byte * 1000000))
			/ (result_time.tv_usec);
	printf("%s传输数据量：缓冲%d发送%lldbyte 接受:%lldbyte 共计用时：%fs 速度：%fM/s\n", argv[0],
			msg_len, byte_transmission, byte_transmission, result_time.tv_usec / 1000000.0,
			myresult);
	return 0;
}
