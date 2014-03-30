/*
 * xp_plugin_easyweb_check.h
 *
 *  Created on: Dec 11, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_CHECK_H_
#define XP_PLUGIN_EASYWEB_CHECK_H_

typedef struct xp_parse_check
{
	xp_parse_result_t* result;
	xp_parse_result_t* default_result;
} xp_parse_check_t;

/**
 * check节点进入函数
 */
int32_t check_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);
/**
 * check节点离开函数
 */
int32_t check_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me);
#endif /* XP_PLUGIN_EASYWEB_CHECK_H_ */
