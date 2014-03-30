/*
 * xp_plugin_easyweb_input.c
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
 * input 节点进入函数
 */
int32_t input_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_input_t*input = LIB_MEM_ALLOC(sizeof(xp_parse_input_t));
	if(!input)
	{
		LIB_ERROR(PLUGIN,"alloc memory for input tag fail!\n");
		return -1;
	}
	input->style = STRUCT_SINGLE_STYLE;
	me->user_data = input;

	return 0;
}

/**
 * 节点离开函数
 */
int32_t input_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_input_t*input = me->user_data;
	assert(input);
	LIB_INFO(PLUGIN, "input style:%d\n", input->style);
	assert(!strcmp(me->parent->self_syntax->name,"state"));
	xp_parse_state_t*state = me->parent->user_data;
	assert(state);
	assert(!state->input_struct);
	state->input_struct=input;
	me->user_data = NULL;
	return 0;
}

/**
 * 属性转换函数
 */
int32_t input_attr_style_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_input_t*input = me->user_data;
	assert(input);
	if (!strcmp(attr_value, "array"))
	{
		input->style = STRUCT_ARRAY_STYLE;
		return 0;
	}
	else if(!strcmp(attr_value,"single"))
	{
		input->style = STRUCT_SINGLE_STYLE;
		return 0;
	}

	LIB_ERROR(PLUGIN, "we can not covert input style for:'%s'!\n", attr_value);
	return -1;
}

