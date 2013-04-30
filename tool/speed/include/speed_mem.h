/**
 * @author: along
 * @date: 2013-04-06
 * @brief: 本文件实现内存申请
 */

#include <stdlib.h>

/**
 * 内存申请
 */
#define speed_memory_alloc(size) malloc(size)

/**
 * 内存释放
 */
#define speed_memory_free(p) free(p)
