#include <assert.h>
#include <string.h>

#include "gen.h"
#include "gen_hash.h"

static gen_hash_elem_t* hash_elem_head(gen_hash_t* hash, uint32_t hashcode)
{
	assert(hashcode < hash->args.size);
	return hash->bucket[hashcode];
}

static gen_hash_elem_t* hash_elem_alloc(gen_hash_t*hash)
{
	gen_hash_elem_t* elem = hash->args.alloc(sizeof(gen_hash_elem_t));
	if (elem)
	{
		memset(elem, 0, sizeof(gen_hash_elem_t));
	}
	return elem;
}

static void hash_elem_free(gen_hash_t*hash, gen_hash_elem_t* hash_elem)
{
	assert(hash);
	assert(hash_elem);
	hash->args.elem_destroy(hash_elem->key, hash_elem->value);
	hash->args.free(hash_elem);

}

static int32_t hash_elem_set(gen_hash_t*hash, uint32_t hashcode,
		gen_hash_elem_t*before, void* key, void *value)
{
	gen_hash_elem_t* new_elem;
	assert(hash);
	assert(hashcode < hash->args.size);
	assert(hashcode == hash->args.hashcode(key));

	if (!(new_elem = hash_elem_alloc(hash)))
	{
		return -1;
	}

	new_elem->key = key;
	new_elem->value = value;
	if (before)
	{
		new_elem->next = before->next;
		before->next = new_elem;
	}
	else
	{
		new_elem->next = hash->bucket[hashcode];
		hash->bucket[hashcode] = new_elem;
	}
	return 0;
}

static void hash_elem_remove(gen_hash_t*hash, uint32_t hashcode,
		gen_hash_elem_t*before, gen_hash_elem_t* remove_elem)
{
	assert(hash);
	assert(hashcode < hash->args.size);
	assert(remove_elem);
	assert(hashcode == hash->args.hashcode(remove_elem->key));

	if (before)
	{
		before->next = remove_elem->next;
	}
	else
	{
		assert(hash->bucket[hashcode] == remove_elem);
		hash->bucket[hashcode] = remove_elem->next;
	}
}

static gen_hash_elem_t* hash_lookfor(gen_hash_t*hash, uint32_t hashcode,
		void*key, gen_hash_elem_t**before)
{
	int32_t ret;
	gen_hash_elem_t* elem;

	assert(hash);
	assert(key);
	assert(before);
	assert(*before == NULL);
	assert(hashcode == hash->args.hashcode(key));

	for (elem = hash_elem_head(hash, hashcode); elem; *before = elem, elem =
			elem->next)
	{
		if (!(ret = hash->args.compare(key, elem->key)))
		{
			return elem;
		}

		if (ret > 0)
		{
			//no need continue lookfor
			break;
		}
	}

	return NULL ;

}

/**
 * hash初始化
 * @param[in] hash 要初始化的hash
 * @param[in] hash_args hash参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t gen_hash_init(gen_hash_t*hash, gen_hash_args_t* hash_args)
{
	assert(hash);
	assert(hash_args);
	assert(hash_args->size);
	assert(hash_args->alloc);
	assert(hash_args->compare);
	assert(hash_args->elem_destroy);
	assert(hash_args->free);
	assert(hash_args->hashcode);

	uint32_t bucket_memory_size = hash->args.size * sizeof(gen_hash_elem_t*);
	memcpy(&(hash->args), hash_args, sizeof(gen_hash_args_t));
	if (!(hash->bucket = (gen_hash_elem_t**) hash->args.alloc(
			bucket_memory_size)))
	{
		LIB_ERROR(HASH, "alloc bucket for hash fail!\n");
		return -1;
	}
	memset(hash->bucket, 0, bucket_memory_size);
	return 0;
}

/**
 * hash插入
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 * @param[in] value 值
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t gen_hash_insert(gen_hash_t*hash, void*key, void*value)
{
	gen_hash_elem_t* elem = NULL;
	gen_hash_elem_t* before_elem = NULL;

	assert(hash);
	assert(key);

	uint32_t hashcode = hash->args.hashcode(key);
	elem = hash_lookfor(hash, hashcode, key, &before_elem);
	if (elem)
	{
		LIB_ERROR(HASH, "insert hash fail,key exist yet!\n");
		return -1;
	}

	if (before_elem)
	{
		return hash_elem_set(hash, hashcode, before_elem, key, value);
	}
	else
	{
		return hash_elem_set(hash, hashcode, NULL, key, value);
	}
}

/**
 * hash查找
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 * @return NULL 未找到
 * @return !NULL 找到
 */
void* gen_hash_lookfor(gen_hash_t*hash, void*key)
{

	gen_hash_elem_t* elem = NULL;
	gen_hash_elem_t* before_elem = NULL;

	assert(hash);
	assert(key);

	uint32_t hashcode = hash->args.hashcode(key);
	elem = hash_lookfor(hash, hashcode, key, &before_elem);
	if (elem)
	{
		return elem->value;
	}

	return NULL ;
}

/**
 * hash删除
 * @param[in] hash 要操作的hash
 * @param[in] key 键
 */
void gen_hash_delete(gen_hash_t*hash, void*key)
{
	assert(hash);
	assert(key);

	gen_hash_elem_t* elem = NULL;
	gen_hash_elem_t* pre_elem = NULL;

	assert(hash);
	assert(key);

	uint32_t hashcode = hash->args.hashcode(key);
	elem = hash_lookfor(hash, hashcode, key, &pre_elem);
	if (elem)
	{
		hash_elem_remove(hash, hashcode, pre_elem, elem);
		hash_elem_free(hash,pre_elem);
	}
}

/**
 * hash稍毁
 * @param[in] hash 要操作的hash
 */
void gen_hash_destroy(gen_hash_t*hash)
{
	assert(hash);
	uint32_t i;

	for (i = 0; i < hash->args.size; ++i)
	{
		gen_hash_elem_t* elem = NULL;
		while ((elem = hash_elem_head(hash, i)))
		{
			hash_elem_remove(hash, i, NULL, elem);
		}
	}
}

/**
 * 检查hash表是否为空
 * @param[in] hash 要操作的hash table
 * @return 0 不为空
 * @return !0 为空
 */
int32_t gen_hash_is_empty(gen_hash_t*hash)
{
	assert(hash);
	uint32_t i;
	for (i = 0; i < hash->args.size; ++i)
	{
		if (hash_elem_head(hash, i))
		{
			return 0;
		}
	}
	return 1;
}

/**
 * dump hash表
 * @param[in] hash 要操作的hash table
 * @param[in] output_fun 输出函数
 */
void gen_hash_dump(gen_hash_t*hash, gen_output_fun output_fun)
{
	assert(hash);
	uint32_t i;

	for (i = 0; i < hash->args.size; ++i)
	{
		gen_hash_elem_t* head;
		head = hash_elem_head(hash, i);
		while (head)
		{
			hash->args.elem_dump(output_fun, head->key, head->value);
			head = head->next;
		}
	}

}
