

#ifndef GEN_HASH_H_
#define GEN_HASH_H_

/**
 * hashcode计算函数
 * @param[in] key 键
 * @return hashcode
 */
typedef uint32_t (*gen_hashcode_fun)(void*key);

/**
 * hash比对
 * @param[in] find_key 查找的key
 * @param[in] hash_store_key hash表存储的key
 * @return 0 相等
 * @return >0 find_key > hash_store_key
 * @return < 0 find_key < hash_store_key
 */
typedef int32_t (*gen_hashcompare_fun)(void*find_key,void*hash_store_key);

/**
 * hashelem销毁
 * @param[in] key 键
 * @param[in] value 值
 * @return 0 成功
 * @return !0 失败
 */
typedef int32_t (*gen_hashelem_destroy_fun)(void*key,void*value);

/**
 * hash申请
 * @param[in] size 大小
 * @return NULL 申请失败
 * @return !NULL 申请成功
 */
typedef void* (*gen_hash_alloc_fun)(uint32_t size);

/**
 * hash释放
 * @param[in] p 要释放的指针
 */
typedef void (*gen_hash_free_fun)(void*p);

/**
 * hash elem
 */
typedef struct gen_hash_elem
{
	void*key;
	void*value;
	struct gen_hash_elem*next;
}gen_hash_elem_t;

/**
 * hash args
 */
typedef struct gen_hash_args
{
	gen_hashcode_fun hashcode;
	gen_hashcompare_fun compare;
	gen_hashelem_destroy_fun elem_destroy;
	gen_hash_alloc_fun alloc;
	gen_hash_free_fun free;
	uint32_t size;
}gen_hash_args_t;

/**
 * hash表
 */
typedef struct gen_hash
{
	gen_hash_elem_t* bucket;
	gen_hash_args_t args;
}gen_hash_t ;

/**
 * hash初始化
 * @param[in] hash 要初始化的hash
 * @param[in] hash_args hash参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t gen_hash_init(gen_hash_t*hash,gen_hash_args_t* hash_args);

/**
 * hash插入
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 * @param[in] value 值
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t gen_hash_insert(gen_hash_t*hash,void*key,void*value);

/**
 * hash查找
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 * @return NULL 未找到
 * @return !NULL 找到
 */
void* gen_hash_lookfor(gen_hash_t*hash,void*key);

/**
 * hash删除
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 */
void gen_hash_delete(gen_hash_t*hash,void*key);

/**
 * hash稍毁
 * @param[in] hash 要操作的hash
 */
void gen_hash_destroy(gen_hash_t*hash);


#endif /* GEN_HASH_H_ */
