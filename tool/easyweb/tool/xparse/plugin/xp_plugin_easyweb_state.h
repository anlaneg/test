/*
 * xp_plugin_easyweb_state.h
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_STATE_H_
#define XP_PLUGIN_EASYWEB_STATE_H_

typedef struct xp_parse_state
{
	char*name;
	char*packet;
	char*version;
	xp_parse_struct_t*first_predef_struct;
	xp_parse_input_t* input_struct;
	xp_parse_check_t* check;
#if 0
	xp_parse_result_t* result;
	xp_parse_result_t* default_result;
#endif
} xp_parse_state_t;

/**
 * state 节点进入函数
 */
int32_t state_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 节点离开函数
 */
int32_t state_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t state_attr_name_convert_fun(const char*attr_name, const char*attr_value,
		struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t state_attr_packet_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t state_attr_version_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

#endif /* XP_PLUGIN_EASYWEB_STATE_H_ */
