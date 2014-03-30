/*
 * xp_plugin_easyweb_member.h
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_MEMBER_H_
#define XP_PLUGIN_EASYWEB_MEMBER_H_

typedef enum xp_parse_pass_type
{
	PASS_TYPE_IN, PASS_TYPE_OUT, PASS_TYPE_INOUT,
} xp_parse_pass_type_t;

typedef struct xp_parse_member
{
	char* name;
	char* type;
	xp_parse_pass_type_t pass_type;
	char* comment;
	uint32_t is_const;
	char* value;
	xp_parse_member_validate_t*member_validate;
	struct xp_parse_member*next_member;
} xp_parse_member_t;

/**
 * member 节点进入函数
 */
int32_t member_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 节点离开函数
 */
int32_t member_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * name属性转换函数
 */
int32_t member_attr_name_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * type属性转换函数
 */
int32_t member_attr_type_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * comment属性转换函数
 */
int32_t member_attr_comment_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * pass_type属性转换函数
 */
int32_t member_attr_pass_type_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * is-const属性转换函数
 */
int32_t member_attr_is_const_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * value属性转换函数
 */
int32_t member_attr_value_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

#endif /* XP_PLUGIN_EASYWEB_MEMBER_H_ */
