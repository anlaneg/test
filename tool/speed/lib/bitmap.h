/**
 * @author:along
 * @date: 2013-04-26
 * @brief:本文件用于实现bitmap操作
 */

#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "speed_mem.h"

typedef struct bitmap {
	uint32_t length;
	uint32_t map[0];	
}bitmap_t;

/**
 * 定义map中位的大小
 */
#define BITMAP_VALUE_WIDTH  (sizeof(uint32_t) * 8)

/**
 * 创建位图
 * @param[in] length 要创建的位图的长度
 * @return NULL 创建失败
 * @return !NULL 创建成功
 */
static inline bitmap_t* bitmap_create(uint32_t length)
{
	assert(length > 0);
	uint32_t real_length = length / BITMAP_VALUE_WIDTH + 1;
	bitmap_t* map = speed_memory_alloc(sizeof(bitmap_t) + BITMAP_VALUE_WIDTH * real_length);
	if(map)
	{
		memset(map->map,0,sizeof(uint32_t)*real_length);
		map->length = length;
	}
	
	return map;
}

/**
 * 测试指定位置的标记
 * @param[in] bitmap 要设置的bitmap
 * @param[in] loc 位置
 * @return 0 此位置为0
 * @return !0 此位置为1
 */
static inline int32_t bitmap_test(bitmap_t*bitmap,uint32_t loc)
{
	uint32_t idx = loc / BITMAP_VALUE_WIDTH;
	uint32_t offset = loc % BITMAP_VALUE_WIDTH;
	
	assert(bitmap);
	assert(bitmap->length >= loc);
	
	return bitmap->map[idx]  & (1ULL << offset);

}

/**
 * 标记指定位置
 * @param[in] bitmap 要设置的bitmap
 * @param[in] loc 位置
 */
static inline void bitmap_set(bitmap_t* bitmap,uint32_t loc)
{	
	uint32_t idx = loc / BITMAP_VALUE_WIDTH;
	uint32_t offset = loc % BITMAP_VALUE_WIDTH;
	
	assert(bitmap);
	assert(bitmap->length >= loc);
	
	bitmap->map[idx]  |= (1ULL << offset);
}

/**
 * 清除指定位置
 * @param[in] bitmap 要设置的bitmap
 * @param[in] loc 位置
 */
static inline void bitmap_clear(bitmap_t* bitmap,uint32_t loc)
{
	uint32_t idx = loc / BITMAP_VALUE_WIDTH;
	uint32_t offset = loc % BITMAP_VALUE_WIDTH;
	
	assert(bitmap);
	assert(bitmap->length >= loc);
	
	bitmap->map[idx]  &= (~(1ULL << offset));
}

/**
 * 销毁bitmap
 * @param[inout] bitmap 要销毁的bitmap
 */
static inline void bitmap_destroy(bitmap_t*bitmap)
{
	assert(bitmap);
	speed_memory_free(bitmap);
}
 
