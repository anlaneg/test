/**
 * 实现bitmap操作
 * author:along
 * #utf-8
 */

#include <stdint.h>

typedef struct bitmap
{
	uint64_t bitmap_len;//bitmap长度
	uint64_t* bitmap;//bitmap内存首指针
}bitmap_t


static inline bitmap_t* bitmap_create(uint64_t);
static inline bitmap_t* bitmap_array_create(uint64_t,uint64_t len);
static inline void bitmap_free(bitmap_t*bitmap);
static inline void bitmap_reset(bitmap_t*bitmap);

static inline int32_t bitmap_and_operator2(bitmap_t*a,bitmap_t*b);
static inline int32_t bitmap_or_operator2(bitmap_t*a,bitmap_t*b);
static inline int32_t bitmap_xor_operator2(bitmap_t*a,bitmap_t*b);
static inline int32_t bitmap_not_operator1(bitmap_t*a);
static inline int32_t bitmap_and_operator3(bitmap_t*result,bitmap_t*a,bitmap_t*b);
static inline int32_t bitmap_or_operator3(bitmap_t*result,bitmap_t*a,bitmap_t*b);
static inline int32_t bitmap_xor_operator3(bitmap_t*result,bitmap_t*a,bitmap_t*b);
static inline int32_t bitmap_not_operator2(bitmap_t*result,bitmap_t*a);

static inline int32_t bitmap_get_state_by_index(bitmap_t*bitmap,uint64_t index);
static inline int32_t bitmap_set_one_state_by_index(bitmap_t*bitmap,uint64_t index);
static inline int32_t bitmap_set_zero_state_by_index(bitmap_t*bitmap,uint64_t index);

static inline int32_t bitmap_move(bitmap_t*bitmap,uint64_t index,uint64_t new_index)
static inline uint64_t bitmap_find_one_state(bitmap_t*bitmap,uint64_t offset);
static inline uint64_t bitmap_find_zero_state(bitmap_t*bitmap,uint64_t offset);
static inline int32_t bitmap_is_equal(bitmap_t*bitmap,bitmap_t*other);
static inline int32_t bitmap_copy(bitmap_t*dest,bitmap_t*src);

