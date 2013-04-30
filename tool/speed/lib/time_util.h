/**
 * @author:along
 * @date  :2013-04-06
 * @brief : 本文用于提供time实用函数
 */

#include <stdint.h>
#include <sys/time.h>

/**
 * 实现两个时间差计算
 * @param[in] a_tv a时间
 * @param[in] b_tv b时间
 * @return 无论a,b两个时间哪个大，总是返回两个之间的差的绝对值。
 * 注意：考虑到uint64可表示的microsecond,约为583,344年,故请确保时间差不会超过此年限
 */

uint64_t time_diff(struct timeval *a_tv,struct timeval* b_tv);
