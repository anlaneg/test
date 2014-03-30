/*
 * tinyxml_sxpath_adapter.cpp
 *
 *  Created on: Oct 12, 2013
 *      Author: along
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "libxml.h"
#include "libsxpath.h"
#include "tinyxml_private.h"

/**
 * 子节点获取
 * @param[in] parent 父节点
 * @param[in] child_node_name 子节点名 注意，此节点名并不一定以'\0'结尾
 * @param[in] child_node_name_length 子节点名长度
 * @param[in] number 子节点索引 注意，此索引自1开始编号
 * @return NULL 获取失败
 * @return !NULL 获取成功
 */
static inline libxml_node_t* sxpath_get_child_node(libxml_node_t*parent,
		const char* child_node_name, uint32_t child_node_name_length,
		uint32_t number)
{
	assert(parent);
	assert(child_node_name);
	assert(child_node_name_length > 0);

	TiXmlElement*child;
	uint32_t find = 0;

	for (child = ((TiXmlElement*) parent)->FirstChildElement(); child; child =
			child->NextSiblingElement())
	{
		assert(child->Value());
		if (!strncmp(child->Value(), child_node_name, child_node_name_length))
		{
			find++;
			if (find == number)
			{
				break;
			}
		}
	}

	return (libxml_node_t*) child;
}

/**
 * 子节点获取
 * @param[in] parent 父节点
 * @param[in] child_node_name 子节点名 注意，此节点名并不一定以'\0'结尾
 * @param[in] child_node_name_length 子节点名长度
 * @param[in] number 子节点索引 注意，此索引自1开始编号
 * @return NULL 获取失败
 * @return !NULL 获取成功
 */
static inline libxml_node_t* sxpath_get_child_node(libxml_node_t*parent,
		const char* child_node_name, uint32_t child_node_name_length)
{
	assert(parent);
	assert(child_node_name);
	assert(child_node_name_length > 0);

	uint32_t i = 0;
	for (i = 0; i < child_node_name_length; ++i)
	{
		assert(child_node_name[i]);
		if (child_node_name[i] == '[' || child_node_name[i] == '@')
		{
			assert(child_node_name[i + 1]);
			unsigned long number = 1;
			if (child_node_name[i] == '[')
			{
				char* endptr = NULL;
				number = strtoul(&child_node_name[i + 1], &endptr, 10);
				if (endptr == NULL || *endptr != ']' || number == 0)
				{
					return NULL;
				}
			}

			return sxpath_get_child_node(parent, child_node_name, i, number);
		}
	}

	return sxpath_get_child_node(parent, child_node_name,
			child_node_name_length, 1);
}

/**
 * 父节点获取
 * @param[in] node 要获取父节点的节点
 * @return NULL 获取失败或者此节点无父节点
 * @return !NULL 获取成功
 */
static inline libxml_node_t* sxpath_get_parent_node(libxml_node_t*node)
{
//暂不支持，直接返回NULL
	return NULL;
}

static const char* sxpath_get_next_level(const char*sxpath, uint32_t*offset,
		uint32_t* match_text_length)
{
	assert(sxpath);
	assert(offset);
	assert(match_text_length);

	//assert(sxpath[0]=='/' || assert(sxpath[0]=='.'));

	//发现 . ..
	if (sxpath[0] == '.')
	{
		if (sxpath[1] == '/')
		{

			*offset += 2; //skip "./"
			return sxpath_get_next_level(&sxpath[2], offset, match_text_length);
		}
		else if (sxpath[1] == '.' && sxpath[2] == '/')
		{
			*match_text_length = 2;
			return &sxpath[3];
		}
	}

	//发现'/'
	if (sxpath[0] == '/')
	{
		//maybe '.' or '..'
		*offset += 1; //skip '/'
		return sxpath_get_next_level(&sxpath[1], offset, match_text_length);
	}

#if 0
	//不需要考虑，下列代码可处理
	if(sxpath[0] =='\0')
	{
		match_text_length=0;
		return NULL;
	}
#endif

	const char* separate = strchr(sxpath, '/');
	if (separate)
	{
		*match_text_length = (uint32_t) (separate - sxpath);
		return separate + 1; //skip '/'
	}

	*match_text_length = strlen(sxpath);
	return NULL;
}

/**
 * 获取符合sxpath要求的node
 * @param[in] node 父节点
 * @param[in] sxpath sxpath语法
 * @return NULL 没有找到符合要求的节点
 * @return !NULL 找到符合要求的节点
 */
libxml_node_t* libxml_sxpath_get_child(libxml_node_t* node, const char*sxpath)
{
	uint32_t match_text_length;
	const char* current_level = sxpath;

	while (current_level && node)
	{
		uint32_t offset = 0;
		const char* next_level = sxpath_get_next_level(current_level, &offset,
				&match_text_length);
		if (!match_text_length)
		{
			assert(!next_level);
			break;
		}

		if (match_text_length == 2
				&& strncmp("..", &current_level[offset], match_text_length))
		{
			node = sxpath_get_parent_node(node);
		}
		else
		{
			node = sxpath_get_child_node(node, &current_level[offset],
					match_text_length);
		}
	}

	return node;
}

/**
 * 获取指定node的属性值
 * @param[in] node 节点
 * @param[in] sxpath sxpath串
 * @return NULL 没有找到符合要求的属性
 * @return !NULL 返回此属性对应的字符串属性值
 */
const char* libxml_sxpath_get_attribute_value(libxml_node_t*node,
		const char* sxpath)
{
	const char* attribute = strrchr(sxpath, '@');
	if (!attribute)
	{
		return NULL;
	}

	node = libxml_sxpath_get_child(node, sxpath);
	if (!node)
	{
		return NULL;
	}

	return ((TiXmlElement*) node)->Attribute(attribute);
}

/**
 * 获取指定node的内部text
 * @param[in] node 节点
 * @param[in] sxpath sxpath串
 * @return NULL node 没有inner text
 * @return !NULL 返回此inner text
 */
const char* libxml_sxpath_get_tag_inner_text(libxml_node_t*node,
		const char*sxpath)
{
	node = libxml_sxpath_get_child(node, sxpath);
	if (!node)
	{
		return NULL;
	}

	return ((TiXmlElement*) node)->GetText();
}
