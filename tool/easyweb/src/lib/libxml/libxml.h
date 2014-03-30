/*
 * libxml.h
 *
 *  Created on: Oct 1, 2013
 *      Author: along
 */

#ifndef LIBXML_H_
#define LIBXML_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct libxml_node
{
} libxml_node_t;

typedef enum libxml_node_type
{
	LIBXML_DOCUMENT,
	LIBXML_ELEMENT,
	LIBXML_COMMENT,
	LIBXML_UNKNOWN,
	LIBXML_TEXT,
	LIBXML_DECLARATION,
	LIBXML_TYPECOUNT
} libxml_node_type_t;

typedef enum libxml_node_access_result
{
	LIBXML_ACCESS_STOP = -1,
	LIBXML_ACCESS_CHILD = 0,
	LIBXML_ACCESS_NEXT_BROTHER = 1,
}libxml_node_access_result_t;
/**
 * node 访问函数
 * @param[in] node 要访问的节点
 * @param[in] args 参数
 * @return libxml_node_access_result_t 访问结果
 */
typedef libxml_node_access_result_t (*libxml_node_access_fun)(libxml_node_t*node, void*args);

/**
 * node 访问函数
 * @param[in] attr_name 属性名
 * @param[in] attr_value 属性值
 * @param[in] args 参数
 * @return 0 访问成功
 * @return !0 访问失败
 */
typedef int32_t (*libxml_node_attribute_access_fun)(const char*attr_name,
		const char*attr_value, void*args);

/**
 * 实现xml文件装载
 * ＠param[in] xml_file_path xml文件路径
 * @return NULL 装载失败
 * @return !NULL xml dom根节点
 */
libxml_node_t* libxml_file_load(const char* xml_path);

/**
 * 销毁xml dom节点
 * @param[in]node 要销毁的dom节点
 */
void libxml_node_destroy(libxml_node_t* node);

/**
 * xml节点遍历
 * @param[in] root xml dom 节点
 * @param[in] entry_access 访问函数（进入时）
 * @param[in] exit_access 访问函数（离开时）
 * @param[in] args 参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t libxml_node_travel(libxml_node_t* root, libxml_node_access_fun entry_access,libxml_node_access_fun exit_access,
		void*args);

/**
 * xml节点属性遍历
 * @param[in] node 节点
 * @param[in] access 属性访问函数
 * @param[in] args 参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t libxml_node_attribute_travel(libxml_node_t*node,
		libxml_node_attribute_access_fun access, void*args);

/**
 * 获取指定节点的名称
 * @param[in] node 节点
 * @return 结点名称
 */
const char* libxml_node_name_get(libxml_node_t*node);

/**
 * 获取指定节点的text
 * @param[in] node 节点
 * @return 结点text
 */
const char* libxml_node_text_get(libxml_node_t*root);

/**
 * 获取指定节点的类型
 * @param[in] node 节点
 * @return 节点类型
 */
libxml_node_type_t libxml_node_type_get(libxml_node_t*node);

/**
 * 获取指定属性值
 * @param[in] node 节点
 * @param[in] attribute_name 属性名
 * @return 属性值
 */
const char* libxml_node_attribute_get(libxml_node_t*node,char* attribute_name);

/**
 * 获取首个子节点
 * @param[in] node 节点
 * return 获得的节点
 */
libxml_node_t* libxml_node_child_get(libxml_node_t*node);

/**
 * 获取父节点
 * @param[in] node 节点
 * @return 获得的节点
 */
libxml_node_t* libxml_node_parent_get(libxml_node_t*node);

/**
 * 获得首个brother节点
 * @param[in] node 节点
 * @return 获得的节点
 */
libxml_node_t* libxml_node_brother_get(libxml_node_t*node);

#if 0
/**
 * 获取首个属性名称
 * @param[in] node 节点
 * @return NULL 获取失败
 * @return !NULL 获取成功
 */
const char* libxml_node_first_attribute_get(libxml_node_t*node);

/**
 * 获取下一个属性名称
 * @param[in] node 节点
 * @return NULL 获取失败
 * @return !NULL 获取成功
 */
const char* libxml_node_next_attribute_get(libxml_node_t*node);
#endif
#ifdef __cplusplus
}
#endif

#endif /* LIBXML_H_ */
