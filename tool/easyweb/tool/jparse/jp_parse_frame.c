/**
 * @author: along
 * @date : 2013-09-02
 * @brief :本文件用于实现解析json对象框架
 * @logic:
 *   1.要解析的对象有两种，一种是tag,一种是attribute
 */
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
#include "jp_tag_parse.h"
#include "jp_attribute_parse.h"
#include "jp_parse_frame.h"

static jp_parse_handle_t* s_jp_parse_handle[JP_MAX_TAG_PARSE_HANDLE];

static int32_t parse_handle_find_empty_room(jp_parse_handle_t*handle)
{
	int32_t i;
	jp_parse_handle_t* item;

	assert(handle);

	for (i = 0; i < JP_MAX_TAG_PARSE_HANDLE; ++i)
	{
		item = s_jp_parse_handle[i];
		if (!item)
		{
			return i;
		}
	}

	return -1;
}


static int32_t get_handle_idx(jp_parse_handle_t*handle)
{
	int32_t i;
	jp_parse_handle_t* item;

	assert(handle);

	for (i = 0; i < JP_MAX_TAG_PARSE_HANDLE; ++i)
	{
		item = s_jp_parse_handle[i];
		if (!item)
		{
			continue;
		}

		assert(item->name);
		//assert(item->xpath);
		if (!strcmp(item->name, handle->name) && item->type == handle->type
		/*&& !strcmp(item->xpath, handle->xpath)*/)
		{
			return i;
		}
	}

	return -1;
}

static jp_parse_handle_t* parse_handle_lookup(jp_parse_handle_t*handle)
{
	int32_t idx;

	if ((idx = get_handle_idx(handle)) < 0)
	{
		return NULL ;
	}

	return s_jp_parse_handle[idx];
}

static int32_t parse_handle_insert(jp_parse_handle_t*handle)
{
	int32_t idx;
	if (parse_handle_lookup(handle))
	{
		//已存在
		LIB_DEBUG(FRAME, " parse handle '%s' is exsit!\n", handle->name);
		return -1;
	}

	if ((idx = parse_handle_find_empty_room(handle)) < 0)
	{
		//无空闲节点
		LIB_DEBUG(FRAME,
				"lookfor empty room for parse handle '%s' insert fail!\n",
				handle->name);
		return -1;
	}

	s_jp_parse_handle[idx] = handle;
	return 0;
}

static void parse_handle_destroy(jp_parse_handle_t*handle)
{
	if (!handle)
	{
		return;
	}

	if (handle->name)
	{
		LIB_MEM_FREE(handle->name);
	}

#if 0
	if (handle->xpath)
	{
		LIB_MEM_FREE(handle->xpath);
	}
#endif

	LIB_MEM_FREE(handle);
}

static void parse_handel_delete(jp_parse_handle_t*handle)
{
	int32_t idx;

	if ((idx = get_handle_idx(handle)) < 0)
	{
		return;
	}

	parse_handle_destroy(s_jp_parse_handle[idx]);
}

int32_t jp_parse_handle_register(jp_parse_handle_t*handle)
{
	return parse_handle_insert(handle);
}

static int32_t parse_handle_tag_parse(json_t*json_tag, jp_tag_t*tag)
{
	json_t* property;
	assert(json_tag->type == JSON_TYPE_OBJECT);
	for (property = json_tag->child; property; property = property->next)
	{
		jp_parse_handle_t parse_handle;
		jp_parse_handle_t* handle;
		parse_handle.name = property->string;
		parse_handle.type = TAG_HANDLE;

		if (!(handle = jp_parse_handle_lookup(&parse_handle)))
		{
			LIB_ERROR(PARSER, "look parse handle for '%s' fail!\n",
					parse_handle.name);
			return -1;
		}

		if (handle->type_ops.tag_handle.init
				&& handle->type_ops.tag_handle.init(tag))
		{
			LIB_ERROR(PARSER, "do parse handle for '%s' init fail!\n",
					parse_handle.name);
			//TODO 注意会没有释放内存
			return -1;
		}

		if (!handle->type_ops.tag_handle.parse)
		{
			LIB_ERROR(PARSER, "parse handle '%s' parse is null!\n",
					parse_handle.name);
			//TODO 注意会没有释放内存
			return -1;
		}
		if (handle->type_ops.tag_handle.parse(property, tag))
		{
			LIB_ERROR(PARSER, "do parse handle for '%s' parse fail!\n",
					parse_handle.name);
			//TODO 注意会没有释放内存
			return -1;
		}
	}
	return 0;
}

int32_t jp_parse_handle_parse(json_t*json, jp_symbol_table_t* symbol_table)
{
	json_t* elem;

	assert(json->type == JSON_TYPE_ARRAY);
	for (elem = json->child; elem; elem = elem->next)
	{
		jp_tag_t *tag;

		assert(elem->type == JSON_TYPE_OBJECT);
		if (!(tag = jp_tag_create()))
		{
			LIB_ERROR(PARSER, "create empty tag fail!\n");
			return -1;
		}

		if (parse_handle_tag_parse(elem, tag))
		{
			LIB_ERROR(PARSER, "parse tag fail\n");
			jp_tag_destroy(tag);
			return -1;
		}

		jp_tag_dump(jparse_dump,tag,NULL);
		if (jp_tag_insert(symbol_table, tag))
		{
			LIB_ERROR(PARSER, "insert tag to symbol_table fail!\n");
			jp_tag_destroy(tag);
			return -1;
		}
	}
	return 0;
}

void jp_parse_handle_unregister(jp_parse_handle_t*handle)
{
	parse_handel_delete(handle);
}

jp_parse_handle_t* jp_parse_handle_lookup(jp_parse_handle_t*handle)
{
	return parse_handle_lookup(handle);
}

