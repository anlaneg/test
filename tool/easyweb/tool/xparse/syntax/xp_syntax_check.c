/*
 * xp_syntax_check.c
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "libmem.h"
#include "libxml.h"
#include "xp_debug.h"
#include "xp_vector.h"
#include "xp_syntax.h"

/**
 * node 未知属性检查函数
 * @param[in] attr_name 属性名
 * @param[in] attr_value 属性值
 * @param[in] args 参数
 * @return 0 访问成功
 * @return !0 访问失败
 */
static int32_t syntax_attribute_unkown_check(const char*attr_name,
		const char*attr_value, void*args)
{
	xp_syntax_item_t* parent_syntax = (xp_syntax_item_t*) args;
	xp_syntax_item_t* attr_syntax;
	if (!(attr_syntax = xp_syntax_attribte_item_lookfor(parent_syntax->id,
			attr_name)))
	{
		LIB_ERROR(SYNTAX_CHECK,
				"syntax-error:attribute node:'%s' unkown,parent is '%s'!\n",
				attr_name, parent_syntax->name);
		return -1;
	}
	return 0;
}

/**
 * node 必须属性检查函数
 * @param[in] attr_name 属性名
 * @param[in] attr_value 属性值
 * @param[in] args 参数
 * @return 0 访问成功
 * @return !0 访问失败
 */
static int32_t syntax_attribute_require_check(const xp_syntax_item_t*tag_syntax,
		void*args)
{
	libxml_node_t*node = args;
	if (tag_syntax->is_require
			&& !libxml_node_attribute_get(node, tag_syntax->name))
	{
		LIB_ERROR(SYNTAX_CHECK,
				"syntax-error:attribute node:'%s' is require,parent is '%s'!\n",
				tag_syntax->name, libxml_node_name_get(node));
		return -1;
	}
	return 0;
}

/**
 * 语法检查内部函数
 * @param[in] root 节点
 * @param[in] 父语法项
 * @return 0 检查通过
 * @return !0 检查失败
 */
static int32_t syntax_check_inner(libxml_node_t*root,
		xp_syntax_item_t* parent_syntax)
{
	assert(root);
	assert(parent_syntax);

	libxml_node_t*child;
	xp_syntax_item_t*tag_syntax;
	const char*node_name = libxml_node_name_get(root);

	if (!(tag_syntax = xp_syntax_tag_item_lookfor(parent_syntax->id, node_name)))
	{

		LIB_ERROR(SYNTAX_CHECK,
				"syntax-error:tag node:'%s' unkown,parent is '%s'!\n",
				node_name, parent_syntax->name);
		return -1;
	}

	//未知属性检查
	if (libxml_node_attribute_travel(root, syntax_attribute_unkown_check, tag_syntax))
	{
		return -1;
	}

	//必须属性检查
	if (xp_syntax_child_attribute_item_travel(tag_syntax,
			syntax_attribute_require_check, root))
	{
		return -1;
	}

	if ((child = libxml_node_child_get(root)))
	{
		if (syntax_check_inner(child, tag_syntax))
		{
			return -1;
		}
	}

	if (child)
	{
		libxml_node_t*brother;
		for (brother = libxml_node_brother_get(child); brother; brother =
				libxml_node_brother_get(brother))
		{
			if (syntax_check_inner(brother, tag_syntax))
			{
				return -1;
			}
		}
	}

	return 0;
}

/**
 * 语法检查
 * @param[in] node 要检查的节点
 * @param[in] parent_id 父节点id
 * @return 0 检查通过
 * @return !0 检查失败
 * @注意：此函数要求parent_id 一定存在于语法项中
 */
int32_t xp_syntax_check(libxml_node_t*node, uint32_t parent_id)
{
	xp_syntax_item_t* parent = xp_syntax_item_lookfor(parent_id);
	if (!parent)
	{
		LIB_ERROR(SYNTAX_CHECK, "we can not find syntax item by id '%d'!\n",
				parent_id);
		return -1;
	}

	return syntax_check_inner(node, parent);
}
