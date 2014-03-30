/*
 * libxml.c
 *
 *  Created on: Oct 1, 2013
 *      Author: along
 */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "libxml.h"
#include "tinyxml_private.h"

/**
 * 实现xml文件装载
 * ＠param[in] xml_file_path xml文件路径
 * @return NULL 装载失败
 * @return !NULL xml dom根节点
 */
libxml_node_t* libxml_file_load(const char* xml_file_path)
{
	TiXmlDocument* doc = new TiXmlDocument(xml_file_path);
	bool loadOkay = doc->LoadFile();

	if (!loadOkay)
	{
		printf("Could not load file '%s'. Error='%s'\n", xml_file_path,
				doc->ErrorDesc());
		return NULL;
	}

	doc->Print(stdout);
	return (libxml_node_t*) doc->RootElement();
}

/**
 * 销毁xml dom节点
 * @param[in]node 要销毁的dom节点
 */
void libxml_node_destroy(libxml_node_t*node)
{
	assert(node);
	delete node;
}

/**
 * xml节点遍历
 * @param[in] root xml dom 节点
 * @param[in] entry_access 访问函数（进入时）
 * @param[in] exit_access 访问函数（离开时）
 * @param[in] args 参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t libxml_node_travel(libxml_node_t* root,
		libxml_node_access_fun entry_access, libxml_node_access_fun exit_access,
		void*args)
{
	TiXmlElement*node = (TiXmlElement*) root;
	assert(entry_access || exit_access);
	libxml_node_access_result_t result;

	for (node = (TiXmlElement*) root; node; node = node->NextSiblingElement())
	{
		if (entry_access)
		{
			result = entry_access((libxml_node_t*) node, args);
			switch (result)
			{
			case LIBXML_ACCESS_STOP:
				printf("trave node '%s' fail\n", node->Value());
				return -1;
			case LIBXML_ACCESS_NEXT_BROTHER:
				return 0; //需要访问下一个项
			case LIBXML_ACCESS_CHILD:
				break; //继续访问下一个项
			}
		}
#if 0
		if (entry_access && entry_access((libxml_node_t*) node, args))
		{
			printf("trave node '%s' fail", node->Value());
			return -1;
		}
#endif
		if (libxml_node_travel((libxml_node_t*) (node->FirstChild()),
				entry_access, exit_access, args))
		{
			printf("travel node '%s' sibling fail\n", node->Value());
			return -1;
		}
#if 0
		if (exit_access && exit_access((libxml_node_t*) node, args))
		{
			printf("trave node '%s' fail", node->Value());
			return -1;
		}
#endif
		if (exit_access)
		{
			result = exit_access((libxml_node_t*) node, args);
			switch (result)
			{
			case LIBXML_ACCESS_STOP:
				printf("trave node '%s' fail\n", node->Value());
				return -1;
			case LIBXML_ACCESS_CHILD:
				printf(
						"trave node exit access fail,exit result is can not child!\n");
				return -1;
			case LIBXML_ACCESS_NEXT_BROTHER:
				return 0; //需要访问下一个项
			}
		}
	}
	return 0;
}

/**
 * xml节点属性遍历
 * @param[in] node 节点
 * @param[in] access 属性访问函数
 * @param[in] args 参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t libxml_node_attribute_travel(libxml_node_t*root,
		libxml_node_attribute_access_fun access, void*args)
{
	TiXmlElement*node = (TiXmlElement*) root;
	TiXmlAttribute*attribute;
	for (attribute = node->FirstAttribute(); attribute; attribute=attribute->Next())
	{
		if (access(attribute->Name(), attribute->Value(), args))
		{
			printf("travel node '%s' attribute fail!\n", node->Value());
			return -1;
		}
	}

	return 0;
}

/**
 * 获取指定节点的名称
 * @param[in] node 节点
 * @return 结点名称
 */
const char* libxml_node_name_get(libxml_node_t*root)
{
	TiXmlElement*node = (TiXmlElement*) root;
	assert(node);
	return node->Value();
}

/**
 * 获取指定节点的text
 * @param[in] node 节点
 * @return 结点text
 */
const char* libxml_node_text_get(libxml_node_t*root)
{
	TiXmlElement*node = (TiXmlElement*) root;
	assert(node);
	return node->GetText();
}

/**
 * 获取指定属性值
 * @param[in] node 节点
 * @param[in] attribute_name 属性名
 * @return 属性值
 */
const char* libxml_node_attribute_get(libxml_node_t*root, char* attribute_name)
{
	TiXmlElement*node = (TiXmlElement*) root;
	assert(node);
	return node->Attribute(attribute_name);
}

/**
 * 获取指定节点的类型
 * @param[in] node 节点
 * @return 节点类型
 */
libxml_node_type_t libxml_node_type_get(libxml_node_t*root)
{
	TiXmlElement*node = (TiXmlElement*) root;
	assert(node);
	switch (node->Type())
	{
	case TiXmlElement::TINYXML_DOCUMENT:
		return LIBXML_DOCUMENT;
	case TiXmlElement::TINYXML_ELEMENT:
		return LIBXML_ELEMENT;
	case TiXmlElement::TINYXML_COMMENT:
		return LIBXML_COMMENT;
	case TiXmlElement::TINYXML_UNKNOWN:
		return LIBXML_UNKNOWN;
	case TiXmlElement::TINYXML_TEXT:
		return LIBXML_TEXT;
	case TiXmlElement::TINYXML_DECLARATION:
		return LIBXML_DECLARATION;
	case TiXmlElement::TINYXML_TYPECOUNT:
		return LIBXML_TYPECOUNT;
	default:
		assert(0);
		*(uint32_t*) 0 = 0;
		return LIBXML_UNKNOWN;
	}
}

/**
 * 获取首个子节点
 * @param[in] node 节点
 * return 获得的节点
 */
libxml_node_t* libxml_node_child_get(libxml_node_t*node)
{
	TiXmlElement*root = (TiXmlElement*) node;
	assert(root);
	return (libxml_node_t*) (root->FirstChildElement());
}

/**
 * 获取父节点
 * @param[in] node 节点
 * @return 获得的节点
 */
libxml_node_t* libxml_node_parent_get(libxml_node_t*node)
{
	TiXmlElement*root = (TiXmlElement*) node;
	assert(root);
	return (libxml_node_t*) (root->Parent());
}

/**
 * 获得首个brother节点
 * @param[in] node 节点
 * @return 获得的节点
 */
libxml_node_t* libxml_node_brother_get(libxml_node_t*node)
{
	TiXmlElement*root = (TiXmlElement*) node;
	assert(root);
	return (libxml_node_t*) (root->NextSiblingElement());
}

#if 0
/**
 * 获取首个属性名称
 * @param[in] node 节点
 * @return NULL 获取失败
 * @return !NULL 获取成功
 */
const char* libxml_node_first_attribute_get(libxml_node_t*node)
{
	TiXmlElement*root = (TiXmlElement*) node;
	node->FirstAttribute(); attribute; attribute->Next()
}

/**
 * 获取下一个属性名称
 * @param[in] node 节点
 * @return NULL 获取失败
 * @return !NULL 获取成功
 */
const char* libxml_node_next_attribute_get(libxml_node_t*node)
{

}
#endif
