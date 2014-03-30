#include <stdlib.h>

/**
 * 实现内存申请
 * @param[in] size 要申请的内存大小
 * @return NULL 申请失败
 * @return !NULL 申请成功
 */
#define LIB_MEM_ALLOC(size) malloc(size)

/**
 * 实现内存释放
 * @param[in] mem 要释放的内存
 */
#define LIB_MEM_FREE(mem)  free(mem)
