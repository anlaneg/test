/*
 * xp_plugin_easyweb_input_sql.c
 *
 *  Created on: Dec 8, 2013
 *      Author: along
 */

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "libstr.h"
#include "libmem.h"
#include "libxml.h"
#include "xp_debug.h"
#include "xp_vector.h"
#include "xp_syntax.h"
#include "xp_plugin_easyweb_member_validate.h"
#include "xp_plugin_easyweb_member.h"
#include "xp_plugin_easyweb_struct.h"
#include "xp_plugin_easyweb_input.h"
#include "xp_plugin_easyweb_output.h"
#include "xp_plugin_easyweb_result.h"
#include "xp_plugin_easyweb_check.h"
#include "xp_plugin_easyweb_state.h"
#include "xp_plugin_easyweb_input_sql.h"

/**
 * input sql节点进入函数
 */
int32_t input_sql_tag_entry_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me)
{
	xp_parse_input_sql_t*sql_input = LIB_MEM_ALLOC(sizeof(xp_parse_input_sql_t));
	memset(sql_input, 0, sizeof(xp_parse_input_sql_t));
	XP_VECTOR_INIT_FUN(&sql_input->sql_param);
	me->user_data = sql_input;

	return 0;
}

/**
 * 节点离开函数
 */
int32_t input_sql_tag_exit_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me)
{
	xp_parse_input_sql_t*sql_input = me->user_data;
	LIB_INFO(PLUGIN, "input sql statement:%s\n", sql_input->sql_statement);
	LIB_ERROR(PLUGIN, "input sql no up!\n");
	return 0;
}

/**
 * 属性转换函数
 */
int32_t struct_attr_sql_statement_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_input_sql_t*sql_input = me->user_data;
	sql_input->sql_statement = libstr_strdup(attr_value);
	return 0;
}

/**
 * input sql param节点进入函数
 */
int32_t input_sql_param_tag_entry_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me)
{
	xp_parse_input_sql_param_t*sql_param =
			LIB_MEM_ALLOC(sizeof(xp_parse_input_sql_param_t));
	memset(sql_param, 0, sizeof(xp_parse_input_sql_param_t));
	me->user_data = sql_param;
	return 0;
}

/**
 * input sql param节点离开函数
 */
int32_t input_sql_param_tag_exit_fun(libxml_node_t*node,
		struct xp_syntax_tree_node*me)
{

	xp_parse_input_sql_param_t*sql_param = me->user_data;
	assert(me->parent);
	assert(!strcmp(me->parent->self_syntax->name,"input-sql"));
	//assert(strcmp(me->parent->node_id, "input-sql") == 0);
	xp_parse_input_sql_t*sql_input = me->parent->user_data;
	if (xp_vector_append(&sql_input->sql_param, sql_param))
	{
		LIB_ERROR(PLUGIN, "append sql param type:%s,value:%s\n",
				sql_param->type, sql_param->value);
		return -1;
	}
	LIB_INFO(PLUGIN, "input sql param type:%s,value:%s\n", sql_param->type,sql_param->value);
	return 0;
}

/**
 * sql param type属性转换函数
 */
int32_t struct_attr_sql_param_type_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_input_sql_param_t*sql_param = me->user_data;
	sql_param->type = libstr_strdup(attr_value);
	return 0;
}

/**
 * sql param value属性转换函数
 */
int32_t struct_attr_sql_param_value_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_input_sql_param_t*sql_param = me->user_data;
	sql_param->value = libstr_strdup(attr_value);
	return 0;
}
