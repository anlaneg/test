/*
 * xp_plugin_easyweb_member.c
 *
 *  Created on: Nov 25, 2013
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
 * member 节点进入函数
 */
int32_t member_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t* member = LIB_MEM_ALLOC(sizeof(xp_parse_member_t));
	if(!member)
	{
		LIB_ERROR(PLUGIN,"alloc memory for member tag fail!\n");
		return -1;
	}
	memset(member, 0, sizeof(xp_parse_member_t));
	member->pass_type = PASS_TYPE_IN;
	member->is_const = 0;
	me->user_data = member;

	return 0;
}

/**
 * 节点离开函数
 */
int32_t member_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	LIB_INFO(PLUGIN, "member name:%s,type:%s,comment:%s\n", member->name,
			member->type, member->comment);

	assert(me->parent);
	//assert(strcmp(me->parent->node_id, "struct") == 0);
	assert(!strcmp(me->parent->self_syntax->name, "struct"));

	xp_parse_struct_t*input_struct =
			(xp_parse_struct_t*) (me->parent->user_data);
	assert(input_struct);

	if (input_struct->member)
	{
		xp_parse_member_t*last = input_struct->member;
		while (last->next_member)
		{
			last = last->next_member;
		}
		last->next_member = member;
	}
	else
	{
		input_struct->member = member;
	}

	return 0;
}

/**
 * name属性转换函数
 */
int32_t member_attr_name_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	member->name = libstr_strdup(attr_value);
	return 0;
}

/**
 * type属性转换函数
 */
int32_t member_attr_type_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	member->type = libstr_strdup(attr_value);
	return 0;
}

/**
 * comment属性转换函数
 */
int32_t member_attr_comment_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	member->comment = libstr_strdup(attr_value);
	return 0;
}

/**
 * pass type属性转换函数
 */
int32_t member_attr_pass_type_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	if (strcmp(attr_value, "in") == 0)
	{
		member->pass_type = PASS_TYPE_IN;
	}
	else if (strcmp(attr_value, "inout") == 0)
	{
		member->pass_type = PASS_TYPE_INOUT;
	}
	else if (strcmp(attr_value, "out") == 0)
	{
		member->pass_type = PASS_TYPE_OUT;
	}
	else
	{
		LIB_ERROR(PLUGIN, "unkown pass type '%s'!\n", attr_value);
		return -1;
	}
	return 0;
}

/**
 * is-const属性转换函数
 */
int32_t member_attr_is_const_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	if (strcmp(attr_value, "true") == 0)
	{
		member->is_const = 1;
	}
	else if (strcmp(attr_value, "true") == 0)
	{
		member->is_const = 0;
	}
	else
	{
		LIB_ERROR(PLUGIN, "unkown 'is-const' '%s'!\n", attr_value);
		return -1;
	}
	return 0;
}

/**
 * value属性转换函数
 */
int32_t member_attr_value_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_t*member = me->user_data;
	member->value = libstr_strdup(attr_value);
	return 0;
}
