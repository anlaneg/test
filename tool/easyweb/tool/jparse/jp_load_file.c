/**
 * @author: along
 * @date : 2013-09-02
 * @brief :本文件用于格式化文件的装载
 * @logic:
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "libmem.h"
#include "json_parse.h"
#include "jp_debug.h"

/**
 * 解析指定文件，返回json对象
 * @param[in] filename 要解析的文件名称
 * @return NULL 解析失败
 * @return !NULL 解析成功
 */
json_t* jparse_file_load(const char*filename)
{
	FILE* file;
	long file_length;
	char* json_text = NULL;
	json_t* json = NULL;

	assert(filename);

	file = fopen(filename, "rb");
	if (!file)
	{
		LIB_ERROR(PARSER, "try open file :'%s' fail,error=%s!\n",
				filename, strerror(errno));
		goto OUT;
	}

	if (fseek(file, 0, SEEK_END))
	{
		LIB_ERROR(PARSER,
				"try move file:'%s' read poisition to end fail,error=%s!\n",
				filename, strerror(errno));
		goto CLOSE_FILE;
	}

	if ((file_length = ftell(file)) < 0 )
	{
		LIB_ERROR(PARSER, "get file:'%s' length fail,error=%s!\n",
				filename, strerror(errno));
		goto CLOSE_FILE;
	}

	if (fseek(file, 0, SEEK_SET))
	{
		LIB_ERROR(PARSER,
				"try move file:'%s' read poisition to end fail,error=%s!\n",
				filename, strerror(errno));
		goto CLOSE_FILE;
	}

	LIB_INFO(PARSER,"try alloc memory for file'%s' size equal %lu\n",filename,file_length);

	if (!(json_text = LIB_MEM_ALLOC(file_length + 1)))
	{
		LIB_ERROR(PARSER, "alloc memory %lu for read fail!\n", file_length + 1);
		goto CLOSE_FILE;
	}

	if (fread(json_text, 1, file_length, file) < file_length)
	{
		LIB_ERROR(PARSER, "try to read file '%s' length:%lu fail,error=%s\n",
				filename, file_length, strerror(errno));
		goto CLOSE_FILE;
	}

	json_text[file_length] = '\0';

	char*error_msg= NULL;
	if (!(json = json_text_parse(json_text,(const char**)&error_msg)))
	{
		LIB_ERROR(PARSER, "parse file '%s' fail! error=%s\n", filename,error_msg);
		goto OUT;
	}

	CLOSE_FILE:
	{
		fclose(file);
	}
	OUT:
	{
		LIB_MEM_FREE(json_text);
	}
	return json;
}
