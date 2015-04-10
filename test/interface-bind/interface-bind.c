
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <assert.h>

/**
 * 根据接口ID获取kernel中mac地址
 * @param [in] 接口ID
 * @param [out] 接口mac地址
 * @return 0 成功
 * @return  -1 失败
 */
int32_t if_ioctl(uint32_t request, caddr_t buffer)
{
    int32_t sock;
    int32_t ret = 0;

    sock = socket(AF_INET, SOCK_DGRAM, 0); //1
    if (sock < 0)
    {
        perror("networkd socket error:");
        printf("[interface] local interface socket create failed, errno=%d %s\n", errno, strerror(errno));
        return -1;
    }

    ret = ioctl(sock, request, buffer);
    if (ret < 0)
    {
        perror("networkd io error:");
        printf("[interface] Local interface ioctl failed, errno=%d %s\n", errno, strerror(errno));
        return -1;
    }

    close(sock);
    return ret;
}

/**
 * 设为混杂模式
 *
 */
int set_nic_promisc(const char *nic_name)
{
	struct ifreq ethreq;
	strncpy(ethreq.ifr_name, nic_name, IFNAMSIZ);
        if_ioctl(SIOCGIFFLAGS, (caddr_t)&ethreq);
        ethreq.ifr_flags |= IFF_PROMISC;
        if_ioctl(SIOCSIFFLAGS, (caddr_t)&ethreq);
        return 0;
}


int32_t if_get_ifindex(char*ifname)
{
    assert(ifname);
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));

    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name) - 1);
    if (if_ioctl(SIOCGIFINDEX, (caddr_t)&ifr) < 0)
    {
        printf("[interface] Local interface %s get ifindex failed\n",
                       ifr.ifr_name);
        return -1;
    }

    return (ifr.ifr_ifindex);
}
//       测试接口绑定问题
//
//
//
//
int main(int argc,char**argv)
{
    int32_t ifindex = if_get_ifindex("eth0"); 
    struct sockaddr_ll sock;
    memset(&sock,0,sizeof(struct sockaddr_ll));
    int fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    //sock = socket(PF_PACKET,SOCK_RAW,0);//2
    //    sock = socket(AF_INET,SOCK_RAW,htons(ETH_P_IP));//3
    //   sock = socket(PF_PACKET, SOCK_RAW, htons (ETH_P_ALL));
    if (fd < 0)
    {
        printf("socket create failed: %s\n", strerror(errno));
        return -1;
    }
    printf("Got raw socket fd %d,bind to interface eth0,ifindex is %d\n", fd,ifindex);

    sock.sll_family = AF_PACKET;
    sock.sll_protocol = htons(ETH_P_ALL);
    sock.sll_ifindex = ifindex;
    if (bind(fd, (struct sockaddr *)&sock, sizeof(sock)) < 0)
    {
        printf("socket bind failed: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    if_read(fd); 
}

ssize_t safe_read(int fd, void * buf, size_t count)
{
    ssize_t n;

    do
    {
        n = read(fd, buf, count);
    }
    while (n < 0 && (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN));

    return n;
}

int if_read(int fd)
{
    fd_set rset, wset, eset;

    FD_ZERO(&rset);
    FD_ZERO(&wset);
    FD_ZERO(&eset);

    FD_SET(fd, &rset);

    while(1)
    {
            if (select(fd+1, &rset, NULL, &eset, NULL) < 0)
            {
                    /* otherwise undefined after error */
                    FD_ZERO(&rset); 
                    FD_ZERO(&wset); 
                    FD_ZERO(&eset);

                    printf("select fd failed: %s\n",strerror(errno));
            }

            if(FD_ISSET(fd, &rset))
            {
                //read unit
                char buffer[65536];
                ssize_t readn= safe_read(fd, &buffer,65536);//make sure no byte to read
                printf("we read %d bytes \n",readn);
            }
            else if(FD_ISSET(fd,&eset))
            {
                printf("what happen ?\n");
            }
    }
}





