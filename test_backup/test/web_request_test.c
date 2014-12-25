/**
 * 此文件用于测试普通读取，select ,poll,信号驱动I/O ,异步I/O
 * 的使用及其效果。
 * 测试站点为:
 * www.baidu.com
 * www.renren.com
 * www.google.com
 * www.weibo.com
 * www.126.com
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ERROR(fmt,...)  fprintf(stderr,fmt,##__VA_ARGS__)

#define CHECK_ARG_NULL(p,ret,msg)  do\
{\
	if((p) == NULL)\
	{\
		ERROR(msg);\
		return ret;\
	}\
}while(0)

static inline void *memory_malloc(size_t size)
{
	void*p = malloc(size);
	if (p == NULL)
	{
		ERROR("apply memory fail!\n");
		exit(1);
	}
	return p;
}

/**
 * 如果成功连接，返回socket,否则返回－１
 */
int request_inner(char*web_host, int port)
{
	int sockfd = -1;
	struct sockaddr_in host_addr;

	CHECK_ARG_NULL(web_host,-1,"argment host is null!\n");

	//在请求域名解析时不加端口号
	char*colon = strstr(web_host, ":");
	(colon != NULL) ? *colon = '\0' : NULL;//先删除':'
	struct hostent* hostaddr = gethostbyname(web_host);
	(colon != NULL) ? *colon = ':' : NULL;//再还原':'

	if (hostaddr == NULL)
	{
		ERROR("request web host %s addr error,error=%s!\n",web_host,hstrerror(h_errno));
		return -1;
	}
	if (hostaddr->h_addrtype != AF_INET)
	{
		ERROR("current only support AF_INET\n");
		return -1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ERROR("create inet socket error,error=%s",strerror(errno));
		return -1;
	}

	//初始化地址
	bzero(&host_addr, sizeof(struct sockaddr_in));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);

	//尝试各种地址
	char** addr_list = (hostaddr->h_addr_list);
	while (*addr_list != NULL)
	{
		bcopy(*addr_list, &(host_addr.sin_addr.s_addr), hostaddr->h_length);
		if (connect(sockfd, (struct sockaddr*) &host_addr,
				sizeof(struct sockaddr_in)) == 0)
		{
			break;
		}
		else
		{
			ERROR("connect %s(%s) error,error=%s\n",web_host,inet_ntoa(host_addr.sin_addr),strerror(errno));
			addr_list++;
		}
	}

	if (addr_list == NULL)
	{
		return -1;
	}

	return sockfd;
}

int send_get_request(int sockfd, char*web_host, char*request_document)
{
	//GET $REQUEST_DOCUMENT HTTP/1.1\r\n
	//Host: $web_host
	//Connect: close
	//Content-Encoding: gzip, compress
	CHECK_ARG_NULL(web_host,-1,"argment host is null!\n");

	int request_document_length = 1;
	if (request_document == NULL)
	{
		request_document = "/";
	}
	else
	{
		request_document_length = strlen(request_document);
	}

	const char
			* const str_format =
					"GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\nContent-Encoding: gzip, compress\r\n\r\n\r\n";
	int total_length = strlen(web_host) + request_document_length + strlen(
			str_format) + 1;
	char*buffer = memory_malloc(total_length * sizeof(char));

	int length = snprintf(buffer, total_length, str_format, request_document,
			web_host);
	buffer[length] = '\0';

	if (write(sockfd, buffer, length) != length)
	{
		ERROR("send :%s to %s error!\n",buffer,web_host);
		free(buffer);
		return -1;
	}

	//ERROR("send :%s to %s\n",buffer,web_host);
	free(buffer);
	return 0;
}

/**
 *功能：与指定URL站点建立连接，并发出请求
 *参数：@weburl 站点地址
 *返回：如果建立连接成功，返回连接描述符，否则返回－１
 */
int request(char* weburl)
{
	int sockfd;
	int port = 80;
	int web_host_name_length;
	char*web_host, *request_document;

	web_host = request_document = NULL;

	//定位request_document
	if ((request_document = strstr(weburl, "/")) != NULL)
	{
		web_host_name_length = request_document - weburl;

		//定位端口号
		char*port_end;
		if ((port_end = strstr(weburl, ":")) != NULL && port_end
				< request_document)
		{
			port = atoi(port_end + 1);
		}
	}
	else
	{
		web_host_name_length = strlen(weburl);

		//定位端口号
		char*port_end;
		if ((port_end = strstr(weburl, ":")) != NULL)
		{
			port = atoi(port_end + 1);
		}
	}

	web_host = (char*) memory_malloc(sizeof(char) * web_host_name_length + 1);
	strncpy(web_host, weburl, web_host_name_length);
	web_host[web_host_name_length] = '\0';

	if ((sockfd = request_inner(web_host, port)) < 0)
	{
		goto dealfail;
	}

	//请求数据
	if (send_get_request(sockfd, web_host, request_document) < 0)
	{
		goto dealfail;
	}

	free(web_host);
	return sockfd;

	dealfail: free(web_host);
	return -1;

}

//test
int deal_response(int fd, int size)
{
	//首先我们得有一个size大小的数组
	char*buffer = (char*) malloc(sizeof(char) * size + 1);

	if (buffer == NULL)
	{
		return -1;
	}

	int length = 0;
	while ((length = read(fd, buffer, size)) > 0)
	{
		buffer[length + 1] = '\0';
		printf("%s", buffer);
	}

	free(buffer);
	return 0;
}

int do_select(int* sockfds, int test_count)
{
	int maxfd;
	int i;
	fd_set fd_reads;

	do
	{
		FD_ZERO(&fd_reads);
		for (i = 0; i < test_count; ++i)
		{
			(maxfd < sockfds[i]) ? maxfd = sockfds[i] : NULL;
			FD_SET(sockfds[i],&fd_reads);
		}

		if (select(maxfd + 1, &fd_reads, NULL, NULL, NULL) <= 0)
		{
			break;
		}

		for (i = 0; i < test_count; ++i)
		{
			if (FD_ISSET(sockfds[i],&fd_reads))
			{
				deal_response(sockfds[i], 1024);
			}
		}
	} while (1);

	return 0;
}
int main(int argc, char**argv)
{
	char*sites[] = { "www.alongsoft.com","www.baidu.com", "www.renren.com:80", "www.google.com",
			"www.weibo.com", "www.126.com", "www.163.com/index.html" };
	int test_count = sizeof(sites) / sizeof(char*);

	int* sockfds = (int*) memory_malloc(sizeof(int) * test_count);
	int i = 0;
	for (; i < test_count; ++i)
	{
		if ((sockfds[i] = request(sites[i])) < 0)
		{
			ERROR("request %s error!\n",sites[i]);
			free(sockfds);
			return -1;
		}
	}

	if (do_select(sockfds, test_count) != 0)
	{
		ERROR("select deal error\n");
		return -1;
	}

	//关闭
	for (i = 0; i < test_count; ++i)
	{
		close(sockfds[i]);
	}

	return 0;
}
