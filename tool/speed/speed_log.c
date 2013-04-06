/**
 * @author:along
 * @date  :2013-04-06
 * @brief : 本文用于提供log
 */
#include <stdio.h>


#define speed_log(fmt,...) fprintf(stdout,fmt,##__VA_ARGS__)
#define speed_log(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)
