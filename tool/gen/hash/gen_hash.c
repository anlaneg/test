
#include "gen.h"
#include "gen_hash.h"

/**
 * hash初始化
 * @param[in] hash 要初始化的hash
 * @param[in] hash_args hash参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t gen_hash_init(gen_hash_t*hash,gen_hash_args_t* hash_args)
{
	return -1;
}

/**
 * hash插入
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 * @param[in] value 值
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t gen_hash_insert(gen_hash_t*hash,void*key,void*value)
{
	return -1;
}

/**
 * hash查找
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 * @return NULL 未找到
 * @return !NULL 找到
 */
void* gen_hash_lookfor(gen_hash_t*hash,void*key)
{
	return NULL;
}

/**
 * hash删除
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 */
void gen_hash_delete(gen_hash_t*hash,void*key)
{

}

/**
 * hash稍毁
 * @param[in] hash 要操作的hash
 */
void gen_hash_destroy(gen_hash_t*hash)
{

}
