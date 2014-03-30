/*
 * xp_plugin_easyweb_output.h
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_OUTPUT_H_
#define XP_PLUGIN_EASYWEB_OUTPUT_H_

typedef struct xp_parse_output
{
	xp_parse_struct_style_t style;
	xp_parse_struct_t* output_struct;
} xp_parse_output_t;


/**
 * output 节点进入函数
 */
int32_t output_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 节点离开函数
 */
int32_t output_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
int32_t output_attr_style_convert_fun(const char*attr_name, const char*attr_value,
		struct xp_syntax_tree_node*me);
#endif /* XP_PLUGIN_EASYWEB_INPUT_H_ */
