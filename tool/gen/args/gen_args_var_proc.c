#include <assert.h>
#include <ctype.h>

#include "gen.h"
#include "gen_args.h"
#include "libmem.h"
#include "libstr.h"
#include "gen_args_private.h"

static int32_t variable_value_is_escape_char(char c)
{
	static const char s_need_escape_char[] =
		{ '\\', ' ', '\t' };
	int32_t i;

	for (i = 0; i < sizeof(s_need_escape_char) / sizeof(char); ++i)
	{
		if (c == s_need_escape_char[i])
		{
			return 1;
		}
	}

	return 0;
}

static int32_t variable_value_is_need_skip(char c)
{
	static const char s_need_skip_char[] =
		{ '\r', '\n', '\f', '\v' };
	int32_t i;

	for (i = 0; i < sizeof(s_need_skip_char) / sizeof(char); ++i)
	{
		if (c == s_need_skip_char[i])
		{
			return 1;
		}
	}

	return 0;
}

static char* variable_value_alloc(char*begin, int32_t length, char escape_char)
{
	char* value;
	int32_t i;
	int32_t j = 0;

	assert(length > 0);
	if (!(value = LIB_MEM_ALLOC(sizeof(char) * length + 1)))
	{
		LIB_ERROR(ARGS, "alloc memory for variable fail!\n");
		return NULL ;
	}
	for (i = 1; i < length; j++)
	{
		if (begin[i - 1] != escape_char)
		{
			value[j] = begin[i - 1];
			i++;

			continue;
		}

		if (variable_value_is_need_skip(begin[i]))
		{
			i += 3;
		}
		else if (variable_value_is_escape_char(begin[i]))
		{
			i += 2;
		}
		else
		{
			LIB_ERROR(ARGS,
					"parser '%s' fail, charater '%c' be escape at %d but unkown!\n",
					begin, begin[i], i);
			LIB_MEM_FREE(value);
			return NULL ;
		}
	}

	value[j] = begin[i - 1];
	value[j + 1] = '\0';
	return value;
}

static char* args_variable_value_parse(char*begin, int32_t end,
		char escape_char)
{
	int32_t i = 0;
	int32_t expect = ' ';
	char* c = begin;

	assert(begin);
	assert(isgraph(escape_char));
	assert(end >= 0);

	if (begin[0] == '\"')
	{
		expect = '\"';
		c = begin + 1;
	}

	for (i = 0; i < end && (c[i] != expect || c[i - 1] == escape_char); ++i)
	{
		//noting to do;
	}

	//检查是否找到指定的expect
	if (c[i] == expect)
	{
		int j = c - begin + i + 1;

		//确保从c[i]开始到end均需要是空字符
		while (j < end)
		{
			if (!isspace(begin[j]))
			{
				//报错
				LIB_ERROR(ARGS,
						"parse '%s' have not space character '%c'='%x' at %d end %d\n",
						begin, begin[j], begin[j], j, end);
				return NULL ;
			}
			j++;
		}
		//begin
	}
	else
	{
		assert(i == end);
		//没有找到期待的字符,如果期待的是空格，则认为找到了
		if (expect != ' ')
		{
			//报错
			LIB_ERROR(ARGS,
					"parse '%s' expect character '%c' at %d,but not find before %c\n",
					c, expect, i, c[end - 1]);
			return NULL ;
		}
		//i = i - 1; //back to i -1
	}

	LIB_DEBUG(ARGS, "parse begin='%s' => '%s' length= '%d',escape ='%c'!\n",
			begin, c, i, escape_char);
	return variable_value_alloc(c, i, escape_char);
}
/**
 * 变量解析
 * @param[in] variable 要解析的变量
 * @param[in] result 解析结果
 * @param[in] escape_char 转义符
 */
int32_t args_variable_parse(char*variable, args_variable_t*result,
		char escape_char)
{
	char* equal_loc;
	char* var_name_begin;
	char* var_value_begin;

	assert(result);
	assert(isgraph(escape_char));

	equal_loc = (char*) libstr_find_char(variable, '=');
	if (!equal_loc)
	{
		LIB_ERROR(ARGS, "parse a variable '%s',but not a variable,need '='!\n",
				variable);
		return -1;
	}

	var_name_begin = (char*) libstr_find_graph_char(variable);
	if (!var_name_begin || var_name_begin >= equal_loc)
	{
		LIB_ERROR(ARGS, "parse a variable '%s', no find variable name!\n",
				variable);
		return -1;
	}

	LIB_DEBUG(ARGS, "variable name :'%s' length :%d\n", var_name_begin,
			(int32_t )(equal_loc - var_name_begin));
	if (!(result->var_name = args_variable_value_parse(var_name_begin,
			equal_loc - var_name_begin, escape_char)))
	{
		LIB_ERROR(ARGS, "parse a variable '%s' name fail!\n", variable);
		return -1;
	}

	LIB_DEBUG(ARGS, "variable name parse result :'%s'\n", result->var_name);

	var_value_begin = (char*) libstr_find_graph_char(equal_loc + 1);
	LIB_DEBUG(ARGS, "variable value :'%s' length :%d\n",
			var_value_begin ? var_value_begin : "",
			var_value_begin ? (int32_t )strlen(var_value_begin) : 0);
	if (var_value_begin)
	{
		if (!(result->var_value = args_variable_value_parse(var_value_begin,
				strlen(var_value_begin), escape_char)))
		{
			LIB_MEM_FREE(result->var_name);
			result->var_name = NULL;
			LIB_ERROR(ARGS, "parse a variable '%s' value fail!\n", variable);
			return -1;
		}
	}
	else
	{
		char* value;
		if (!(value = libstr_strdup("")))
		{
			LIB_ERROR(ARGS, "alloc variable value '' fail!\n");
			LIB_MEM_FREE(result->var_name);
			result->var_name = NULL;
			return -1;
		}
		result->var_value = value;
	}
	LIB_DEBUG(ARGS, "variable name parse result :'%s'\n", result->var_value);

	return 0;
}
