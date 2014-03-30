#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "gen.h"
#include "gen_cfg_parse.h"
#include "libmem.h"

static int32_t is_noblank_char(char c)
{
	static const char s_noblank_char[] =
		{ '\t', ' ', '\r', '\n' };
	int32_t i;
	for (i = 0; i < sizeof(s_noblank_char) / sizeof(char); ++i)
	{
		if (s_noblank_char[i] == c)
		{
			return 1;
		}
	}
	return 0;
}

static int32_t cfg_read_first_noblank(FILE*file)
{
	int c;

	while ((c = fgetc(file)) != EOF)
	{
		if (!is_noblank_char(c))
		{
			break;
		}
	}
	return c;
}

static void cfg_skip_comment_line(FILE*file)
{
	int c;
	while (1)
	{
		c = fgetc(file);
		if (c == '\n' || c == EOF)
		{
			break;
		}
	}
}

static void cfg_read_variable_line(FILE*file)
{
	int c;
	while (1)
	{
		c = fgetc(file);
		if (c == '\\')
		{
			fgetc(file);
		}
		else if (c == '\n' || c == EOF)
		{
			break;
		}
	}
}

static int32_t read_variable(FILE*file, long length, char**variable)
{
	char* var;

	var = LIB_MEM_ALLOC(sizeof(char) * length + 1);
	if (!var)
	{
		LIB_ERROR(PARSER, "alloc memory for variable fail!\n");
		return -1;
	}

	fread(var, length, sizeof(char), file);
	var[length] = '\0';

	*variable = var;
	return 0;
}

static int32_t cfg_read_variable(FILE*file, long *start, long* finish)
{
	long begin;
	long end;
	char c;

	while (1)
	{
		c = cfg_read_first_noblank(file);

		if (c == '#')
		{
			cfg_skip_comment_line(file);
			continue;
		}
		else if( c == EOF)
		{
			*start = *finish = 0;
			return 0;
		}
		break;
	}

	begin = ftell(file)-1;
	cfg_read_variable_line(file);
	end = ftell(file);
	*start = begin;
	*finish = end;
#if 0
	if(begin == end)
	{
		assert(fgetc(file) == EOF);
		return 0;
	}
	fseek(file, begin, SEEK_SET);
	return read_variable(file, end - begin, variable);
#endif
	return 0;
}
/**
 * 配置解析
 * @param[in] file 配置文件
 * @param[in] item_tbl 配置项表
 * @param[in] max_size 最大配置项表
 * @return 0 配置解析成功
 * @return !0 配置解析失败
 */
static int32_t cfg_parse(gen_args_t* args, FILE*file)
{
	while (1)
	{
		long start;
		long finish;
		char*variable;
		if (cfg_read_variable(file, &start, &finish))
		{
			LIB_ERROR(PARSER, "load variable fail!\n");
			return -1;
		}

		if (start == finish)
		{
			assert(fgetc(file) == EOF);
			break;
		}

		fseek(file, start, SEEK_SET);
		if (read_variable(file, finish - start, &variable))
		{
			LIB_ERROR(PARSER, "read variable fail!\n");
			return -1;
		}

		//add variable to hash
		if (gen_args_hash_add_variable(args, variable))
		{
			LIB_ERROR(PARSER, "args hash add variable '%s' fail!\n", variable);
			LIB_MEM_FREE(variable);
			return -1;
		}
		LIB_MEM_FREE(variable);
	}

	return 0;
}

/**
 * 通过配置装载变量
 * @param[in] args 配置参数
 * @return 0 配置解析装载成功
 * @return !0 配置解析装载失败
 */
int32_t gen_cfg_load_variable(gen_args_t* args)
{
	FILE*file = fopen(args->cfg_file_path, "r");
	if (!file)
	{
		LIB_ERROR(PARSER,"open config file '%s' fail,error=%s!\n", args->cfg_file_path,
				strerror(errno));
		return -1;
	}

	if (cfg_parse(args, file))
	{
		LIB_ERROR(PARSER,"parser config file '%s' fail!\n",args->cfg_file_path);
		fclose(file);
		return -1;
	}
	fclose(file);
	return 0;
}
