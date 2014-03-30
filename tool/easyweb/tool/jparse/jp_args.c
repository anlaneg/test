/**
 * @author: along
 * @date : 2013-08-31
 * @brief :本文件用于实现参数解析
 * @logic:
 */
#include <assert.h>
#include <getopt.h>
#include <stdint.h>

#include "jp_debug.h"
#include "libmem.h"
#include "libstr.h"
#include "json_parse.h"
#include "jp.h"


/**
 * 短选项
 */
static const char* s_jparse_short_options = "hc:vVo:";

/**
 * 长选项
 */
static const struct option s_jparse_long_options[] = { //
		{ "help", 0, NULL, 'h' }, //
				{ "complier", 1, NULL, 'c' }, //
				{ "verbose", 0, NULL, 'v' }, //
				{ "version", 0, NULL, 'V' }, //
				{ "output-path", 1, NULL, 'o' }, //
				{ NULL, 0, NULL, 0 } //
		};

/**
 * 用于记录命令行参数
 */
jp_jparse_args_t g_jparse_args;

static void jparse_version_show(const char*prgm_name)
{
	static const char* s_jparse_version =
			"%s 0.01 (complier@" __DATE__ " " __TIME__ ")\n";
	printf(s_jparse_version, prgm_name);
}

static void jparse_help_show(const char*prgm_name)
{
	static const char* s_jparse_help =
			"\n"
			"\t-h,--help		显示本帮助信息\n"
			"\t-c,--complier	指出要编译的文件\n"
			"\t-v,--verbose		指明采用详细输出\n"
			"\t-v,--version		显示版本号\n"
			"\t-o,--output-path	指出输出目录\n"
			"\n"
			;

	jparse_version_show(prgm_name);
	printf("%s", s_jparse_help);
}

static int32_t args_parse(jp_jparse_args_t*local_args, int argc, char**argv)
{
	int c;
	while ((c = getopt_long(argc, argv, s_jparse_short_options,
			s_jparse_long_options, NULL )) != -1)
	{
		//hc:vVo:
		switch (c)
		{
		case 'h':
			local_args->is_need_show_help = 1;
			break;
		case 'c':
			if (!(local_args->complier_file = libstr_strdup(optarg)))
			{
				LIB_ERROR(CORE, "alloc memory for args complier-file fail!\n");
				return -1;
			}
			break;
		case 'v':
			local_args->is_need_verbose = 1;
			break;
		case 'V':
			local_args->is_need_show_version = 1;
			break;
		case 'o':
			if (!(local_args->output_path = libstr_strdup(optarg)))
			{
				LIB_ERROR(CORE, "alloc memory for args output-path fail!\n");
				return -1;
			}
			break;
		default:
			LIB_ERROR(CORE,"sorry,unkown option value '%d' \n",c);
			return -1;
		}
	}
	return 0;

}
static int32_t args_process(jp_jparse_args_t*local_args, int argc, char**argv)
{
	if (args_parse(local_args, argc, argv))
	{
		LIB_ERROR(CORE, "args process error!\n");
		return -1;
	}

	//显示帮助
	if (local_args->is_need_show_help)
	{
		jparse_help_show(argv[0]);
		return -1;
	}

	//显示版本
	if (local_args->is_need_show_version)
	{
		jparse_version_show(argv[0]);
		return -1;
	}

	//设置log
	if (local_args->is_need_verbose)
	{
		debug_set_module_log_level(DEBUG_LEVEL);
	}
	else
	{
		debug_set_module_log_level(INFO_LEVEL);
	}

	if (local_args->complier_file == NULL
			|| !libstr_strlen(local_args->complier_file))
	{
		LIB_ERROR(CORE, "parameter error,need complier file path!\n");
		return -1;
	}

	return 0;
}
/**
 * jparser参数解析
 * @param[out] local_args 出参，记录转换后的命令行输入
 * @param[in] argc 参数数目
 * @param[in] argv 参数
 * @return 0 参数解析成功
 * @return !0 参数解析失败
 */
int32_t jparse_args_process(jp_jparse_args_t*local_args, int argc, char**argv)
{
	assert(argv && argv[0]);
	assert(local_args);

	//参数处理
	return args_process(local_args, argc, argv);
}

/**
 * jparse参数销毁
 * @param[in] local_args 要销毁的参数
 */
void jparse_args_destroy(jp_jparse_args_t*local_args)
{
	assert(local_args);
	LIB_MEM_FREE(local_args->complier_file);
	LIB_MEM_FREE(local_args->output_path);
	memset(local_args, 0, sizeof(jp_jparse_args_t));
}
