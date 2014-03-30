/*
 * libsxpath.h
 *
 *  Created on: Oct 12, 2013
 *      Author: along
 *  bref:本文件用于实现简单xpath查询 ，记为sxpath
 *  1. '/' 表示层次分隔符，文档的顶层节点为'/'
 *  2. '/node-name/child-node[1]' 表示取第一个/node-name节点下的名称为child-node节点，注意当节点索引为1时，可省
 *     略，如以下示例，可简记为'/node-name/child-node'
 *  3. '.' 表示当前节点  [暂不支持]
 *  4. '..' 表示父节点   [暂不支持]
 *  5. '/node-name@attribute-name' 表示取节点node-name的属性名为attribute-name的属性值
 *  注意：和属性一起取时，需要向说明节点，再说明属性，如果节点不指明，默认为第一个节点
 */

#ifndef LIBSXPATH_H_
#define LIBSXPATH_H_

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * 获取符合sxpath要求的node
 * @param[in] node 父节点
 * @param[in] sxpath sxpath语法
 * @return NULL 没有找到符合要求的节点
 * @return !NULL 找到符合要求的节点
 */
libxml_node_t* libxml_sxpath_get_child(libxml_node_t* node, const char*sxpath);

/**
 * 获取指定node的属性值
 * @param[in] node 节点
 * @param[in] sxpath sxpath串
 * @return NULL 没有找到符合要求的属性
 * @return !NULL 返回此属性对应的字符串属性值
 */
const char* libxml_sxpath_get_attribute_value(libxml_node_t*dom, const char* sxpath);

/**
 * 获取指定node的内部text
 * @param[in] node 节点
 * @param[in] sxpath sxpath串
 * @return NULL node 没有inner text
 * @return !NULL 返回此inner text
 */
const char* libxml_sxpath_get_tag_inner_text(libxml_node_t*dom, const char*sxpath);

#ifdef __cplusplus
}
#endif

#endif /* LIBSXPATH_H_ */
