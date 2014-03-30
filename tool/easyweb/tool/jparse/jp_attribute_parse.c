/**
 * @author: along
 * @date : 2013-09-02
 * @brief :本文件用于解析json对象
 * @logic:
 */
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


#include "jp_debug.h"
#include "json_parse.h"
#include "jp.h"
#include "jp_tag_attribute.h"
#include "jp_tag.h"
#include "jp_symbol_table.h"
#include "json_parse.h"
#include "jp_debug.h"
#include "libstr.h"
#include "libmem.h"
#include "jp_parse_frame.h"


int32_t json_parse_attribute_property_attribute_name(json_t*json_name,
		jp_tag_attribute_t*attribute)
{
	char* tag_value = libstr_strdup(json_name->valuestring);
	if (!tag_value)
	{
		return -1;
	}
	jp_tag_attribute_set_name(attribute, tag_value);
	return 0;
}

int32_t json_parse_attribute_property_type(json_t*json_type,
		jp_tag_attribute_t*attribute)
{
	char*tag_value = libstr_strdup(json_type->valuestring);
	if (!tag_value)
	{
		return -1;
	}

	jp_tag_attribute_set_type(attribute,JP_TYPE_STRING);
	//TODO 这里需要做转换（搞成一个回调函数？）
	return 0;
}

int32_t json_parse_attribute_property_require(json_t*json_type,
		jp_tag_attribute_t*attribute)
{
	char*tag_value = libstr_strdup(json_type->valuestring);
	if (!tag_value)
	{
		return -1;
	}
	return -1;
}

int32_t json_parse_attribute_property_comment(json_t*json_type,
		jp_tag_attribute_t*attribute)
{
	char*tag_value = libstr_strdup(json_type->valuestring);
	if (!tag_value)
	{
		return -1;
	}
	jp_tag_attribute_set_comment(attribute, tag_value);
	return 0;
}

int32_t json_parse_attribute(json_t* json_attribute,
		jp_tag_attribute_t*attribute)
{
	json_t* property;

	for (property = json_attribute->child; property; property = property->next)
	{
		jp_parse_handle_t parse_handle;
		jp_parse_handle_t* handle;
		parse_handle.name = property->string;
		parse_handle.type = ATTRIBUTE_HANDLE;

		if (!(handle = jp_parse_handle_lookup(&parse_handle)))
		{
			LIB_ERROR(PARSER, "look parse handle for '%s' fail!\n",
					parse_handle.name);
			return -1;
		}

		if (handle->type_ops.attribute_handle.init
				&& handle->type_ops.attribute_handle.init(attribute))
		{
			LIB_ERROR(PARSER, "do parse handle for '%s' init fail!\n",
					parse_handle.name);
			//TODO 注意会没有释放内存
			return -1;
		}

		if (!handle->type_ops.attribute_handle.parse)
		{
			LIB_ERROR(PARSER, "parse handle '%s' parse is null!\n",
					parse_handle.name);
			//TODO 注意会没有释放内存
			return -1;
		}
		if (handle->type_ops.attribute_handle.parse(property, attribute))
		{
			LIB_ERROR(PARSER, "do parse handle for '%s' parse fail!\n",
					parse_handle.name);
			//TODO 注意会没有释放内存
			return -1;
		}
	}
	return 0;
}
