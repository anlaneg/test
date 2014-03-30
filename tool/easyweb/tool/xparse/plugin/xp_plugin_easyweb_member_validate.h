/*
 * xp_plugin_easyweb_member_validate.h
 *
 *  Created on: Dec 8, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_MEMBER_VALIDATE_H_
#define XP_PLUGIN_EASYWEB_MEMBER_VALIDATE_H_

typedef struct xp_parse_member_validate
{
	uint32_t max_length;
	char*comment;
}xp_parse_member_validate_t;


/**
 * input 节点进入函数
 */
int32_t member_validate_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 节点离开函数
 */
int32_t member_validate_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t member_validate_attr_max_length_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t member_validate_attr_comment_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

#endif /* XP_PLUGIN_EASYWEB_MEMBER_VALIDATE_H_ */
