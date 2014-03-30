/*
 * xp_plugin_easyweb_input_sql.h
 *
 *  Created on: Dec 8, 2013
 *      Author: along
 */

#ifndef XP_PLUGIN_EASYWEB_INPUT_SQL_H_
#define XP_PLUGIN_EASYWEB_INPUT_SQL_H_

typedef struct xp_parse_input_sql_param
{
	char* type;
	char* value;
}xp_parse_input_sql_param_t;

typedef struct xp_parse_input_sql
{
	char* sql_statement;
	xp_vector_t sql_param;
	xp_parse_struct_t sql_struct;
} xp_parse_input_sql_t;

/**
 * input sql节点进入函数
 */
int32_t input_sql_tag_entry_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me);
/**
 * 节点离开函数
 */
int32_t input_sql_tag_exit_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me);
/**
 * 属性转换函数
 */
int32_t struct_attr_sql_statement_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * input sql param节点进入函数
 */
int32_t input_sql_param_tag_entry_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me);

/**
 * input sql param节点离开函数
 */
int32_t input_sql_param_tag_exit_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me);

/**
 * sql param type属性转换函数
 */
int32_t struct_attr_sql_param_type_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * sql param value属性转换函数
 */
int32_t struct_attr_sql_param_value_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);


#endif /* XP_PLUGIN_EASYWEB_INPUT_SQL_H_ */
