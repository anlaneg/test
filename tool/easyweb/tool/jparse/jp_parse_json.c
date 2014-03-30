/**
 * @author: along
 * @date : 2013-09-02
 * @brief :本文件用于解析json对象
 * @logic:
 */
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

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

static jp_parse_handle_t s_tag_parse_handle[] =
	{
		{ .type = TAG_HANDLE, .name = "tag", .type_ops =
			{ .tag_handle =
				{ .init = NULL, .parse = json_parse_property_tag, .dump = NULL,
						.uninit = NULL } } },
		{ .type = TAG_HANDLE, .name = "parent", .type_ops =
			{ .tag_handle =
				{ .init = NULL, .parse = json_parse_property_parent, .dump =
						NULL, .uninit = NULL } } },

		{ .type = TAG_HANDLE, .name = "require", .type_ops =
			{

			.tag_handle =
				{ .init = NULL, .parse = json_parse_property_require, .dump =
						NULL, .uninit = NULL } } },

				{ .type = TAG_HANDLE, .name = "attribute", .type_ops =
					{ .tag_handle =
						{ .init = NULL, .parse = json_parse_property_attribute, .dump = NULL, .uninit =
								NULL } } },

				{ .type = TAG_HANDLE, .name = "comment", .type_ops =
					{ .tag_handle =
						{ .init = NULL, .parse = json_parse_property_comment,
								.dump = NULL, .uninit = NULL } } }, };

static jp_parse_handle_t s_attribute_parse_handle[] =
	{
		{ .type = ATTRIBUTE_HANDLE, .name = "attribute-name", .type_ops =
			{ .attribute_handle =
				{ .init = NULL, .parse =
						json_parse_attribute_property_attribute_name, .dump =
						NULL, .uninit = NULL } } },

		{ .type = ATTRIBUTE_HANDLE, .name = "type", .type_ops =
			{ .attribute_handle =
				{ .init = NULL, .parse = json_parse_attribute_property_type,
						.dump = NULL, .uninit = NULL } } },

		{ .type = ATTRIBUTE_HANDLE, .name = "comment", .type_ops =
			{ .attribute_handle =
				{ .init = NULL, .parse = json_parse_attribute_property_comment,
						.dump = NULL, .uninit = NULL } } },

		{ .type = ATTRIBUTE_HANDLE, .name = "require", .type_ops =
			{ .attribute_handle =
				{ .init = NULL, .parse = json_parse_attribute_property_require,
						.dump = NULL, .uninit = NULL } } } };

/**
 * 注册数组形式的解析集
 * @param[in] handle 控制集
 * @param[in] size 控制集数目
 * @return 0 注册成功
 * @return !0 注册失败
 */
static int32_t parse_handle_register(jp_parse_handle_t*handle, uint32_t size)
{
	int32_t i;
	for (i = 0; i < size; ++i)
	{
		if (jp_parse_handle_register(&handle[i]))
		{
			const char*type =
					(handle[i].type == TAG_HANDLE) ? "tag" : "attribute";
			LIB_ERROR(PARSER, "register '%s':'%s' fail!\n", type,
					handle[i].name);
			return -1;
		}
	}
	return 0;
}

/**
 * 解析句柄初始化
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t jp_parse_handle_init()
{
	if (parse_handle_register(s_tag_parse_handle,
			sizeof(s_tag_parse_handle) / sizeof(jp_parse_handle_t))
			|| parse_handle_register(s_attribute_parse_handle,
					sizeof(s_attribute_parse_handle)
							/ sizeof(jp_parse_handle_t)))
	{
		return -1;
	}
	return 0;
}
