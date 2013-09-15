
#include <assert.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "gen.h"
#include "gen_args.h"

/**
 * 长选项
 */
static const struct option s_gen_long_option[]=
{
	{"--variable",1,0,'v'},
	{"--config-file",1,0,'c'},
	{"--template-file",1,0,'t'},
	{"--output-file",1,0,'o'},
	{"--help",0,0,'h'},
	{"--version",0,0,'V'},
	{"--debug",0,0,'d'},
	{NULL,0,0,0}
};

/**
 * 短选项
 */
const char* s_gen_short_option="v:c:t:o:hVd";

/**
 * 解析参数
 * @param[in] args 参数
 * @param[in] argc 参数数目
 * @param[in] argv 参数集
 * @return 0 解析成功
 * @return !0 解析失败
 */
static int32_t args_parse(gen_args_t*args, int argc, char**argv)
{
	int opt;
	int long_idx;
	while ((opt = getopt_long(argc, argv, s_gen_short_option,
                              s_gen_long_option, &long_idx)) != EOF) 
	{
		switch(opt)
		{
			case 'v':
				//add varviable to hash tabel;
			break;
			case 'c':
				args->cfg_file_path=NULL;
			break;
			case 't':
				args->template_file_path=NULL;
			break;
			case 'o':
				args->output_file_path=NULL;
			break;
			case 'h':
				args->is_need_show_help = 1;
			break;
			case 'V':
				args->is_need_show_version = 1;
			break;
			case 'd':
				args->debug_level=1;
			break;
			default:
				//TODO unkown
				return -1;	
			break;
		}
	}
	return 0;
}


/**
 * 显示版本
 */
static void show_version()
{

}

/**
 * 显示帮助
 */
static void show_help()
{

}

/**
 * 参数校验
 * @return 0 校验成功
 * @return !0 校验失败
 */
static int32_t args_validate()
{
	return -1;
}

/**
 * 参数处理
 * @return 0 处理成功
 * @return !0 处理失败
 */
static int32_t args_process()
{
	return -1;
}

static uint32_t args_var_hashcode(void*key)
{
	return 0;
}

static int32_t args_var_hashcompare(void*find_key,void*hash_store_key)
{
	assert(find_key && hash_store_key);
	return strcmp(find_key,hash_store_key);
}

static int32_t args_var_hashelem_destroy(void*key,void*value)
{
	return 0;
}

static int32_t args_hash_args_init(gen_hash_args_t*hash_args)
{
	hash_args->hashcode = args_var_hashcode;
	hash_args->compare  = args_var_hashcompare;
	hash_args->elem_destroy = args_var_hashelem_destroy;
	hash_args->alloc = malloc;
	hash_args->free = free;
	hash_args->size = 1024;

	return 0;
}

/**
 * 参数初始化
 * @param[in] args 参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t gen_args_init(gen_args_t* args)
{
	if(args_hash_args_init(&args->hash_args))
	{
		return -1;
	}

	if(gen_hash_init(&args->var_hash,&args->hash_args))
	{
		return -1;
	}
	args->my_name=NULL;
	args->cfg_file_path=NULL;
	args->template_file_path=NULL;
	args->output_file_path=NULL;
	args->split_char="@";
	args->escape_char="\\";
	args->debug_level = 0;
	args->is_need_show_help = 0;
	args->is_need_show_version = 0;
	args->global_buffer_size = 2*1024*1024;
	args->output_fun = NULL;
	return -1;
}

/**
 * 参数销毁
 * @param[in] args 参数
 */
void gen_args_destroy(gen_args_t* args)
{

}

/**
 * 解析参数
 * @param[in] args 参数
 * @param[in] argc 参数数目
 * @param[in] argv 参数集
 * @return 0 解析成功
 * @return !0 解析失败
 */
int32_t gen_args_parse(gen_args_t*args, int argc, char**argv)
{
	return -1;
}

