#include <assert.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "gen.h"
#include "gen_args.h"
#include "libmem.h"
#include "libstr.h"
#include "gen_args_private.h"

static uint32_t args_var_hashcode(void*key)
{
	return 0;
}

static int32_t args_var_hashcompare(void*find_key, void*hash_store_key)
{
	assert(find_key && hash_store_key);
	return strcmp(find_key, hash_store_key);
}

static int32_t args_var_hashelem_destroy(void*key, void*value)
{
	return 0;
}

static void* hash_elem_alloc(uint32_t size)
{
	return LIB_MEM_ALLOC(size);
}

static void hash_elem_free(void*p)
{
	LIB_MEM_FREE(p);
}

static void hash_elem_dump(gen_output_fun output_fun, void* key, void* value)
{
	assert(output_fun);
	output_fun(NULL,"{ key= '%s',value='%s' }\n",(char*)key,(char*)value);
}

/**
 * arg hash初始化
 * @param[in] hash_args hash参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t args_hash_args_init(gen_hash_args_t*hash_args)
{
	hash_args->hashcode = args_var_hashcode;
	hash_args->compare = args_var_hashcompare;
	hash_args->elem_destroy = args_var_hashelem_destroy;
	hash_args->elem_dump = hash_elem_dump;
	hash_args->alloc = hash_elem_alloc;
	hash_args->free = hash_elem_free;
	hash_args->size = 1024;

	return 0;
}

/**
 * 为variable hash中添加一个变量
 * @param[in] args 参数
 * @param[in] variable 变量参数
 * @return 0 添加成功
 * @return !0 添加失败
 */
int32_t gen_args_hash_add_variable(gen_args_t* args, char*variable)
{
	args_variable_t result =
		{ .var_name = NULL, .var_value = NULL , };

	LIB_DEBUG(ARGS,"args try parse variable_parse '%s'!\n",variable);

	if (args_variable_parse(variable, &result, args->escape_char))
	{
		LIB_ERROR(ARGS, "args hash parse variable '%s' fail!\n", variable);
		return -1;
	}

	LIB_DEBUG(ARGS,"args parse valuriable '%s' ,variable name is '%s',variable value is '%s'!\n",
			variable,result.var_name,result.var_value);

	if (gen_hash_insert(&args->var_hash, result.var_name, result.var_value))
	{
		LIB_ERROR(ARGS,
				"args hash add variable '%s' , var name = %s, var value = %s fail! \n",
				variable, result.var_name, result.var_value);
		LIB_MEM_FREE(result.var_name);
		LIB_MEM_FREE(result.var_value);
		return -1;
	}

	LIB_DEBUG(ARGS,
			"args hash add variable var name= '%s',var value= '%s' success!\n",
			result.var_name, result.var_value);
	return 0;
}

