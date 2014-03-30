/*
 * xp_plugin_easyweb_struct.h
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_STRUCT_H_
#define XP_PLUGIN_EASYWEB_STRUCT_H_

typedef enum xp_parse_struct_type
{
	STRUCT_NORMAL, STRUCT_UNION, STRUCT_ENUM,
	//为别的结构体的一部分
	STRUCT_PART,
} xp_parse_struct_type_t;

typedef struct xp_parse_struct
{
	char* name;
	xp_parse_struct_type_t type;
	xp_parse_member_t* member;
	struct xp_parse_struct*sub_struct;
	//指向并行的
	struct xp_parse_struct* next_struct;
} xp_parse_struct_t;

/**
 * struct 节点进入函数
 */
int32_t struct_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 节点离开函数
 */
int32_t struct_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t struct_attr_name_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

#endif /* XP_PLUGIN_EASYWEB_STRUCT_H_ */
