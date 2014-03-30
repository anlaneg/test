#include <errno.h>
#include <assert.h>
#include <stdarg.h>

#include "gen.h"
#include "gen_parse.h"
#include "libstr.h"
#include "libmem.h"

/**
 * 文件输出函数
 * @param[in] arg 参数
 * @param[in] str 要输出的字符串
 * @param[in] ... 其它参数
 */
void output_file_write(void*arg, char* fmt, ...)
{
	FILE* output_file = (FILE*) arg;
	va_list va;

	va_start(va, fmt);
	vfprintf(output_file, fmt, va);
	va_end(va);
}

static gen_buffer_t* parse_buffer_create(FILE* output_file, int32_t buffer_size,
		gen_output_fun output)
{
	gen_buffer_t* out_buffer;
	if (!(out_buffer = gen_buffer_create(buffer_size, output, output_file)))
	{
		LIB_ERROR(ARGS, "outbuffer create fail!\n");
		return NULL ;
	}
	return out_buffer;
}

static void parse_buffer_destroy(gen_buffer_t* out_buffer)
{
	assert(out_buffer);
	assert(out_buffer->arg);

	gen_buffer_flush(out_buffer);

	//fclose(s_out_buffer->arg);
	gen_buffer_destroy(out_buffer);
}

static int32_t find_split_char_loc(char*line, char escape_char, char split_char,
		int offset)
{
	assert(line);

	int32_t i = offset;

	while (1)
	{
		while (line[i] != split_char && line[i] != '\0')
		{
			i++;
		}

		if (line[i] == '\0')
		{
			return -1;
		}

		if (i > offset && line[i - 1] == escape_char)
		{
			continue;
		}

		return i;
	}
}
/**
 * 解析行信息并输出至out_buffer中
 * @param[in] out_buffer 输出缓存
 * @param[in] args 参数
 * @param[in] line 行
 * @return 0 成功
 * @return !0 失败
 */
static int32_t parse_line(gen_buffer_t* out_buffer, gen_args_t*args, char*line)
{
	//int32_t start;
	int32_t offset = 0;

	int32_t length = libstr_strlen(line);
	while (1)
	{
		char* variable_value;
		char old_value;
		int start = find_split_char_loc(line, args->escape_char, args->split_char, offset);
		if(start < 0)
		{
			gen_buffer_append(out_buffer,line+offset,length-offset);
			return 0;
		}
		else if(start > 0)
		{
			gen_buffer_append(out_buffer,line+offset,start-offset);
		}

		int end = find_split_char_loc(line,args->escape_char,args->split_char,start+1);
		if(end < 0)
		{
			gen_buffer_append(out_buffer,line+start,length-start);
			return 0;
		}

		//检查start-end位置是否有相应字符串
		old_value = line[end];
		line[end] = '\0';
		if(!(variable_value=(char*)gen_hash_lookfor(&args->var_hash,&line[start+1])))
		{
			LIB_WARN(PARSER,"we can not find variable name:'%s'!\n",&line[start+1]);
			line[end]=old_value;
			gen_buffer_append(out_buffer,line+start,end-start);
		}
		else
		{
			gen_buffer_append(out_buffer,variable_value,strlen(variable_value));
			line[end]=old_value;
		}

		offset=end+1;
	}
}

static char* readline(FILE*file)
{
	int c;
	long begin;
	long end;
	char* line;

	begin = ftell(file);
	for (c = fgetc(file); c != EOF && c != '\n'; c = fgetc(file))
	{
		/**/
	}
	end = ftell(file);
	if (end - begin == 0)
	{
		assert(c == fgetc(file));
		return NULL ;
	}

	fseek(file, begin, SEEK_SET);
	line = LIB_MEM_ALLOC((end - begin + 1) * sizeof(char));
	if (!line)
	{
		LIB_ERROR(PARSER, "alloc memory for readline fail,size=%ld!\n",
				end - begin + 1);
		return NULL ;
	}

	fread(line, end - begin, sizeof(char), file);
	line[end - begin] = '\0';
	return line;
}

/**
 * 模块文件解析
 * @param[in] args 参数
 * @return 0 成功
 * @return !0 失败
 */
int32_t gen_parse_tmplate_file_process(gen_args_t*args)
{
	int32_t ret = -1;
	FILE* template_file = NULL;
	FILE* output_file = NULL;
	gen_buffer_t* out_buffer = NULL;
	char* line = NULL;

	if (!(template_file = fopen(args->template_file_path, "r")))
	{
		LIB_ERROR(PARSER, "open template file '%s' fail,error=%s!\n",
				args->template_file_path, strerror(errno));
		goto OUT;
	}

	if (!(output_file = fopen(args->output_file_path, "w")))
	{
		LIB_ERROR(PARSER, "open output file '%s' fail,error=%s!\n",
				args->output_file_path, strerror(errno));
		goto CLOSE_TEMPLATE_FILE;
	}

	if (!(out_buffer = parse_buffer_create(output_file,
			args->global_buffer_size, output_file_write)))
	{
		LIB_ERROR(PARSER, "create parser output buffer fail!\n");
		goto CLOSE_OUTPUT_FILE;
	}

	while (1)
	{

		if (!(line = readline(template_file)))
		{
			if (feof(template_file))
			{
				break;
			}
			else
			{
				LIB_ERROR(PARSER, "readline from '%s' fail!\n",
						args->template_file_path);
				goto DESTROY_PARSER_BUFFER;
			}
		}

		LIB_INFO(PARSER,"parse line:%s\n",line);
		if (parse_line(out_buffer, args, line))
		{
			LIB_ERROR(PARSER, "parse line '%s' fail!\n", line);
			goto FREE_LINE;
		}

		LIB_MEM_FREE(line);
	}

	ret = 0;

	FREE_LINE:
	{
		LIB_MEM_FREE(line);
	}
	DESTROY_PARSER_BUFFER:
	{
		parse_buffer_destroy(out_buffer);
	}
	CLOSE_OUTPUT_FILE:
	{
		fclose(output_file);
	}
	CLOSE_TEMPLATE_FILE:
	{
		fclose(template_file);
	}
	OUT:
	{
		return ret;
	}
}
