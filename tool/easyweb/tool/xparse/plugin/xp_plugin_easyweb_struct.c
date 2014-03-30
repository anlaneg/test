/*
 * xp_plugin_easyweb_struct.c
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
 * struct 节点进入函数
 */
int32_t struct_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_struct_t*input_struct = LIB_MEM_ALLOC(sizeof(xp_parse_struct_t));
	memset(input_struct, 0, sizeof(xp_parse_struct_t));
	input_struct->type = STRUCT_NORMAL;
	me->user_data = input_struct;

	return 0;
}

/**
 * 节点离开函数
 */
int32_t struct_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_struct_t*input_struct = me->user_data;
	assert(input_struct);
	LIB_INFO(PLUGIN, "%s struct name:%s\n", me->parent->self_syntax->name,
			input_struct->name);
	if (!strcmp(me->parent->self_syntax->name, "struct"))
	{
		xp_parse_struct_t* parent_struct = me->parent->user_data;
		assert(parent_struct);
		if(parent_struct->sub_struct)
		{
			xp_parse_struct_t*last=parent_struct->sub_struct;
			while(last->next_struct)
			{
				last = last->next_struct;
			}
			last->next_struct = input_struct;
		}
		else
		{
			parent_struct->sub_struct = input_struct;
		}
	}
	else if(!strcmp(me->parent->self_syntax->name,"input"))
	{
		xp_parse_input_t* input = me->parent->user_data;
		assert(input);
		input->input_struct = input_struct;
	}
	else if(!strcmp(me->parent->self_syntax->name,"output"))
	{
		xp_parse_output_t*output = me->parent->user_data;
		assert(output);
		output->output_struct= input_struct;
	}

	me->user_data = NULL;
	return 0;
}

/**
 * 属性转换函数
 */
int32_t struct_attr_name_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_struct_t*input_struct = me->user_data;
	input_struct->name = libstr_strdup(attr_value);
	return 0;
}
