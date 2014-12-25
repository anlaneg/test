#include <stdint.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <linux/tipc.h>
#include <unistd.h>

#include "speed_log.h"

//do rdm init
int32_t tipc_rdm_init(uint32_t type, uint32_t instance)
{
	struct sockaddr_tipc server_addr = {
		.family = AF_TIPC,
		.addrtype = TIPC_ADDR_NAME,
		.scope = TIPC_ZONE_SCOPE,
		.addr.name = {  .name = {.type = type, .instance=instance }, 
			.domain =0 }
	};

	int sd = socket(AF_TIPC, SOCK_RDM, 0);
	if (sd < 0) 
	{
		SPEED_CAL_ERR("ipc socket create fail. errno=%d %s\n", errno, strerror(errno));
		return -1;
	}

	if (0 != bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr))) 
	{
		SPEED_CAL_ERR("ipc socket bind fail. errno=%d %s\n", errno, strerror(errno));
		return -1;
	}

	return sd;
}


int32_t tipc_rdm_rcv(char*msg,uint32_t len,int32_t sock)
{
	struct sockaddr_tipc tipc_addr;
	uint32_t tipc_addr_len;
	uint32_t rcv_size = 0;
	uint32_t total_len = 0;

	while(total_len < len)
	{	
		rcv_size = recvfrom(sock,msg+total_len,len-total_len,0,(struct sockaddr*)&tipc_addr,&tipc_addr_len);
		if(rcv_size < 0)
		{
			SPEED_CAL_ERR("recvform fail!\n");
			return -1;
		}
		total_len += rcv_size;
	}
	return 0;
}

int32_t tipc_rdm_send(char*msg,uint32_t len,int32_t sock,uint32_t type,uint32_t instance)
{
	struct sockaddr_tipc tipc_addr = {
		.family = AF_TIPC,
		.addrtype = TIPC_ADDR_NAME,
		.scope = TIPC_ZONE_SCOPE,
		.addr.name = {  .name = {.type = type, .instance=instance }, .domain =0 }
	};
	uint32_t send_size = 0;
	uint32_t total_len = 0;
	while(total_len < len)
	{
		send_size = sendto(sock,msg+total_len,len-total_len,0,(struct sockaddr*) &tipc_addr,sizeof(struct sockaddr_tipc));
		if(send_size < 0)
		{
			SPEED_CAL_ERR("sendto fail!\n");
			return -1;
		}
		total_len += send_size;
	}
	return 0;
}


