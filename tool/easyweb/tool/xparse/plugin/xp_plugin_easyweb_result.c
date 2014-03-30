/*
 * xp_plugin_easyweb_result.c
 *
 *  Created on: Dec 11, 2013
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

/**
 * result节点进入函数
 */
int32_t result_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_result_t* result = LIB_MEM_ALLOC(sizeof(xp_parse_result_t));
	if (!result)
	{
		LIB_ERROR(PLUGIN, "alloc memory for result tag parse fail!\n");
		return -1;
	}
	memset(result, 0, sizeof(xp_parse_result_t));
	if (!strcmp(me->self_syntax->name, "default"))
	{
		result->is_use_default = 1;
	}
	me->user_data = result;
	return 0;
}

/**
 * result节点离开函数
 */
int32_t result_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_result_t* result = me->user_data;
	LIB_INFO(PLUGIN,
			"result tag is type:%d,value:%s,forward:%s,redirect:%s,comment:%s!\n",
			result->action_type,
			result->is_use_default ? "default" : result->result_value,
			result->action.forward, result->action.redirect, result->comment)
	xp_parse_check_t* check = me->parent->user_data;
	assert(check);
	if(result->is_use_default)
	{
		assert(!check->default_result);
		check->default_result = result;
	}
	else
	{
		if(check->result)
		{
			xp_parse_result_t* last = check->result;
			while(last->next_result)
			{
				last = last->next_result;
			}
			last->next_result = result;
		}
		else
		{
			check->result = result;
		}
	}
	me->user_data = NULL;
	return 0;
}

/**
 * value属性转换函数
 */
int32_t result_attr_value_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_result_t*result = me->user_data;
	result->result_value = libstr_strdup(attr_value);
	return 0;
}

/**
 * comment属性转换函数
 */
int32_t result_attr_comment_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_result_t*result = me->user_data;
	result->comment = libstr_strdup(attr_value);
	return 0;
}

/**
 * forward属性转换函数
 */
int32_t result_attr_forward_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_result_t*result = me->user_data;
	result->action.forward = libstr_strdup(attr_value);
	result->action_type = XP_PARSE_FORWARD_RESULT;
	return 0;
}

/**
 * redirect属性转换函数
 */
int32_t result_attr_redirect_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_result_t*result = me->user_data;
	result->action.redirect = libstr_strdup(attr_value);
	result->action_type = XP_PARSE_REDIRECT_RESULT;
	return 0;
}
