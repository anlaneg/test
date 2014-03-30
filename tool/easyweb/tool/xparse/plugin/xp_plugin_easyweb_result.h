/*
 * xp_plugin_easyweb_result.h
 *
 *  Created on: Dec 11, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_RESULT_H_
#define XP_PLUGIN_EASYWEB_RESULT_H_

enum xp_parse_action_type
{
	XP_PARSE_REDIRECT_RESULT, XP_PARSE_FORWARD_RESULT,
};

typedef struct xp_parse_result
{
	int32_t is_use_default;
	char* result_value;
	enum xp_parse_action_type action_type;
	char* comment;
	union
	{
		char* redirect;
		char* forward;
	} action;
	xp_parse_output_t* output;
	struct xp_parse_result*next_result;
} xp_parse_result_t;

/**
 * result节点进入函数
 */
int32_t result_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);
/**
 * result节点离开函数
 */
int32_t result_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * value属性转换函数
 */
int32_t result_attr_value_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * comment属性转换函数
 */
int32_t result_attr_comment_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * forward属性转换函数
 */
int32_t result_attr_forward_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * redirect属性转换函数
 */
int32_t result_attr_redirect_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

#endif /* XP_PLUGIN_EASYWEB_CHECK_H_ */
