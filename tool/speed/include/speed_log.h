/**
 * @author:along
 * @date  :2013-04-06
 * @brief : 本文用于提供log
 */
#include <stdio.h>

/**
 * 错误输出
 */
#define speed_log(fmt,...) fprintf(stdout,fmt,##__VA_ARGS__)

/**
 * 日志输出
 */
#define speed_err(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)
