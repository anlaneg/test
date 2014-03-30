/*
 * xp_plugin_easyweb_state.c
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

static void member_tag_info_dump(xp_parse_member_t* member_info)
{
	for (; member_info; member_info = member_info->next_member)
	{
		xp_parse_member_validate_t* validate = member_info->member_validate;
		printf(
				"---member name:%s,type:%s,pass_type:%d,is_const:%d,value:%s,comment:%s,",
				member_info->name, member_info->type, member_info->pass_type,
				member_info->is_const, member_info->value,
				member_info->comment);
		if (validate)
		{
			printf("validate:{comment:%s,max_length:%d}\n", validate->comment,
					validate->max_length);
		}
		else
		{
			printf("\n");
		}
	}
}

static void struct_tag_info_dump(xp_parse_struct_t*struct_info)
{

	for (; struct_info; struct_info = struct_info->next_struct)
	{
		printf("--struct name:%s,type:%d\n", struct_info->name,
				struct_info->type);
		member_tag_info_dump(struct_info->member);
		struct_tag_info_dump(struct_info->sub_struct);
	}
}

static void result_tag_info_dump(xp_parse_result_t*result)
{
	for (; result; result = result->next_result)
	{
		printf(
				"---result action type:%d,action:%s,%s comment:%s,is_use_default:%d,result_value:%s,output style:%d\n",
				result->action_type, result->action.forward,
				result->action.redirect, result->comment,
				result->is_use_default, result->result_value,
				result->output->style);

		struct_tag_info_dump(result->output->output_struct);
	}
}

static void state_tag_info_dump(xp_parse_state_t*state)
{
	xp_parse_input_t* input = state->input_struct;
	printf("state dump <<<\n");
	printf("-name:%s,packet:%s,version:%s,input style:%d\n", state->name, state->packet,
			state->version,input->style);

	//printf("-input style:%d\n", input->style);
	struct_tag_info_dump(input->input_struct);
	result_tag_info_dump(state->check->result);
	result_tag_info_dump(state->check->default_result);
	printf("state dump end<<<\n");
}

/**
 * state 节点进入函数
 */
int32_t state_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	me->user_data = LIB_MEM_ALLOC(sizeof(xp_parse_state_t));
	if (!me->user_data)
	{
		LIB_ERROR(PLUGIN, "alloc memory for state fail!\n");
		return -1;
	}
	memset(me->user_data,0,sizeof(xp_parse_state_t));
	return 0;
}

/**
 * 节点离开函数
 */
int32_t state_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_state_t*state = me->user_data;
	assert(state);
	LIB_INFO(PLUGIN, "hello name:%s,packet:%s,version:%s\n", state->name,
			state->packet, state->version);
	me->parent->user_data = me->user_data;
	me->user_data = NULL;
	state_tag_info_dump(state);
	return 0;
}

/**
 * 属性转换函数
 */
int32_t state_attr_name_convert_fun(const char*attr_name, const char*attr_value,
		struct xp_syntax_tree_node*me)
{
	xp_parse_state_t*state = me->user_data;
	assert(state);
	state->name = libstr_strdup(attr_value);
	if (!state->name)
	{
		LIB_ERROR(PLUGIN, "alloc memory for state name fail!\n");
		return -1;
	}
	return 0;
}

/**
 * 属性转换函数
 */
int32_t state_attr_packet_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_state_t*state = me->user_data;
	state->packet = libstr_strdup(attr_value);
	if (!state->packet)
	{
		LIB_ERROR(PLUGIN, "alloc memory for state packet fail!\n");
		return -1;
	}
	return 0;
}

/**
 * 属性转换函数
 */
int32_t state_attr_version_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_state_t*state = me->user_data;
	state->version = libstr_strdup(attr_value);
	if (!state->version)
	{
		LIB_ERROR(PLUGIN, "alloc memory for state version fail!\n");
		return -1;
	}
	return 0;
}
