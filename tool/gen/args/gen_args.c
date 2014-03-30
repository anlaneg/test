#include <assert.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdarg.h>

#include "gen.h"
#include "gen_args.h"
#include "libmem.h"
#include "libstr.h"
#include "gen_args_private.h"
#include "gen_cfg_parse.h"

#define GEN_GLOBAL_BUFFEER_MIN_SIZE (1*1024*1024ULL)

#define GEN_STR(no_str) #no_str
/**
 * 长选项
 */
static const struct option s_gen_long_option[] =
	{
		{ "variable", 1, NULL, 'v' },
		{ "config-file", 1, NULL, 'c' },
		{ "template-file", 1, NULL, 't' },
		{ "output-file", 1, NULL, 'o' },
		{ "help", 0, NULL, 'h' },
		{ "version", 0, NULL, 'V' },
		{ "debug", 0, NULL, 'd' },
		{ NULL, 0, NULL, 0 } };

/**
 * 短选项
 */
const char* s_gen_short_option = "v:c:t:o:hVd";

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
	while ((opt = getopt_long(argc, argv, s_gen_short_option, s_gen_long_option,
			NULL )) != EOF)
	{
		switch (opt)
		{
		case 'v':
			//add varviable to hash tabel;
			if (gen_args_hash_add_variable(args, optarg))
			{
				LIB_ERROR(ARGS, "add variable '%s' fail!\n", optarg);
				return -1;
			}
			break;
		case 'c':
			if (!(args->cfg_file_path = libstr_strdup(optarg)))
			{
				LIB_ERROR(ARGS, "alloc memory for args cfg-file-path fail!\n");
				return -1;
			}
			break;
		case 't':
			if (!(args->template_file_path = libstr_strdup(optarg)))
			{
				LIB_ERROR(ARGS,
						"alloc memory for args template-file-path fail!\n");
				return -1;
			}
			break;
		case 'o':
			if (!(args->output_file_path = libstr_strdup(optarg)))
			{
				LIB_ERROR(ARGS,
						"alloc memory for args output-file-path fail!\n");
				return -1;
			}
			break;
		case 'h':
			args->is_need_show_help = 1;
			break;
		case 'V':
			args->is_need_show_version = 1;
			break;
		case 'd':
			args->debug_level = 1;
			break;
		default:
			LIB_ERROR(ARGS, "sorry,unkown option value '%d' \n", opt)
			;
			return -1;
			break;
		}
	}
	return 0;
}

/**
 * 显示版本
 */
static void show_version(const char*prgm_name)
{
	static const char* s_jparse_version =
			"%s 0.01 (complier@" __DATE__ " " __TIME__ ")\n";
	printf(s_jparse_version, prgm_name);
}

/**
 * 显示帮助
 */
static void show_help(const char*prgm_name)
{
	static const char* s_jparse_help = "\n"
			"\t-v,--variable			指明变量<key>=<value>\n"
			"\t-c,--config-file		指明配置位置\n"
			"\t-t,--template-file 		指出模块文件所在位置\n"
			"\t-o,--output-file		指出输出文件所在位置\n"
			"\t-h,--help			显示本帮助信息\n"
			"\t-V,--version			显示版本号\n"
			"\t-d,--debug			指明采用详细输出\n"
			"\n";

	show_version(prgm_name);
	printf("%s", s_jparse_help);

}

/**
 * 参数校验
 * @param[in] args 要校验的参数
 * @return 0 校验成功
 * @return !0 校验失败
 */
static int32_t args_validate(gen_args_t*args)
{
	if (!args->cfg_file_path)
	{
		LIB_WARN(ARGS, "config file path is empty!\n");
	}
	else
	{
		//build variable hashtable
		if (gen_cfg_load_variable(args))
		{
			LIB_ERROR(PARSER, "load variable fail!\n");
			//gen_args_destroy(args);
			return -1;
		}
	}
	//hashtable must no empty
	if (gen_hash_is_empty(&args->var_hash))
	{
		LIB_ERROR(ARGS, "variable hash is empty!\n");
		return -1;
	}

	//char* my_name; is not null
	if (!args->my_name)
	{
		LIB_ERROR(ARGS, "args my name is empty!\n");
		return -1;
	}

	if (!args->template_file_path)
	{
		LIB_ERROR(ARGS, "template file path is empty!\n");
		return -1;
	}

	if (!args->output_file_path)
	{
		LIB_ERROR(ARGS, "output file path is empty!\n");
		return -1;
	}

	if (!args->split_char)
	{
		LIB_ERROR(ARGS, "split char is empty!\n");
		return -1;
	}

	if (!args->escape_char)
	{
		LIB_ERROR(ARGS, "escape char is empty!\n");
		return -1;
	}

	if (args->global_buffer_size < GEN_GLOBAL_BUFFEER_MIN_SIZE)
	{
		LIB_ERROR(ARGS,
				"global buffer size is to small,must big than" GEN_STR(GEN_GLOBAL_BUFFEER_MIN_SIZE) "!\n");
		return -1;
	}

	if (!args->output_fun)
	{
		LIB_ERROR(ARGS, "args output is null!\n");
		return -1;
	}

#if 0
	if(!args->out_buffer)
	{
		LIB_ERROR(ARGS,"out buffer is null!\n");
		return -1;
	}
#endif
	assert(!args->out_buffer);

	return 0;
}

static void gen_output(void*arg, char* fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}

/**
 * 参数初始化
 * @param[in] args 参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t gen_args_init(gen_args_t* args, char* prg_name)
{
	if (args_hash_args_init(&args->hash_args))
	{
		LIB_ERROR(ARGS, "arghash args init fail!\n");
		return -1;
	}

	if (gen_hash_init(&args->var_hash, &args->hash_args))
	{
		LIB_ERROR(ARGS, "arghash init fail!\n");
		return -1;
	}

	args->my_name = libstr_strdup(prg_name);
	args->cfg_file_path = NULL;
	args->template_file_path = NULL;
	args->output_file_path = NULL;
	args->split_char = '@';
	args->escape_char = '\\';
	args->debug_level = 0;
	args->is_need_show_help = 0;
	args->is_need_show_version = 0;
	args->global_buffer_size = 2 * 1024 * 1024;
	args->output_fun = gen_output;

#if 0
	if (!(args->out_buffer = gen_buffer_create(args->global_buffer_size,
							args->output_fun, NULL )))
	{
		LIB_ERROR(ARGS, "args outbuffer create fail!\n");
		return -1;
	}
#endif

	return 0;
}

/**
 * 参数销毁
 * @param[in] args 参数
 */
void gen_args_destroy(gen_args_t* args)
{
	gen_hash_destroy(&args->var_hash);
	LIB_MEM_FREE(args->cfg_file_path);
	LIB_MEM_FREE(args->my_name);
	LIB_MEM_FREE(args->output_file_path);
	LIB_MEM_FREE(args->template_file_path);
	LIB_MEM_FREE(args->out_buffer);
}

/**
 * 参数处理
 * @param[in] args 参数
 * @param[in] argc 参数数目
 * @param[in] argv 参数集
 * @return 0 处理成功
 * @return !0 处理失败
 */
static int32_t args_process(gen_args_t*args, int argc, char**argv)
{
	//解析
	if (args_parse(args, argc, argv))
	{
		LIB_ERROR(ARGS, "args process fail!\n");
		return -1;
	}

	//是否为输出帮助信息
	if (args->is_need_show_help)
	{
		show_help(argv[0]);
		return -1;
	}

	//是否需要显示帮助信息
	if (args->is_need_show_version)
	{
		show_version(argv[0]);
		return -1;
	}

	//设置log
	if (args->debug_level)
	{
		debug_set_module_log_level(DEBUG_LEVEL);
	}
	else
	{
		debug_set_module_log_level(INFO_LEVEL);
	}

	if (args_validate(args))
	{
		LIB_ERROR(ARGS, "args validate fail!\n");
		return -1;
	}
	return 0;
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
	return args_process(args, argc, argv);
}

