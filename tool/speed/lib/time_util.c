/**
 * @author:along
 * @date  :2013-04-06
 * @brief : 本文用于提供time实用函数
 */

#include "time_util.h"

/**
 * 内部时间差函数
 * @param[in] a_sec 较大时间的秒数
 * @param[in] a_usec 较大时间的微秒数
 * @param[in] b_sec 较小时间的秒数
 * @param[in] b_usec 较小时间的微秒数
 * @return 时间差，注意返回的时间差恒大于０
 */
static uint64_t time_diff_inner(uint64_t a_sec,uint64_t a_usec,uint64_t b_sec,uint64_t b_usec)
{
	return (( a_usec + 1000000ULL ) - b_usec ) + (( a_sec - b_sec - 1ULL ) * 1000000ULL);
}

/**
 * 实现两个时间差计算
 * @param[in] a_tv a时间
 * @param[in] b_tv b时间
 * @return 无论a,b两个时间哪个大，总是返回两个之间的差的绝对值。
 * 注意：考虑到uint64可表示的microsecond,约为583,344年,故请确保时间差不会超过此年限
 */

uint64_t time_diff(struct timeval *a_tv,struct timeval* b_tv)
{
	if(a_tv->tv_sec > b_tv->tv_sec)
	{
		return time_diff_inner(a_tv->tv_sec,a_tv->tv_usec,b_tv->tv_sec,b_tv->tv_usec);
	}
	else if(b_tv->tv_sec > a_tv->tv_sec)
	{	
		return time_diff_inner(b_tv->tv_sec,b_tv->tv_usec,a_tv->tv_sec,a_tv->tv_usec);
	}
	else
	{
		if(a_tv->tv_usec >= b_tv->tv_usec)
		{
			return a_tv->tv_usec - b_tv->tv_usec;
		}

		return b_tv->tv_usec - a_tv->tv_usec;
	}
}
