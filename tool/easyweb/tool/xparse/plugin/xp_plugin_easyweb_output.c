/*
 * xp_plugin_easyweb_output.c
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
 * output 节点进入函数
 */
int32_t output_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_output_t*output = LIB_MEM_ALLOC(sizeof(xp_parse_output_t));
	output->style = STRUCT_SINGLE_STYLE;
	me->user_data = output;

	return 0;
}

/**
 * 节点离开函数
 */
int32_t output_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_output_t*output = me->user_data;
	LIB_INFO(PLUGIN, "output style:%d\n", output->style);

	//assert(!strcmp(me->parent->node_id, "state"));
	assert(
			!strcmp(me->parent->self_syntax->name, "result")
					|| !strcmp(me->parent->self_syntax->name, "default"));
	xp_parse_result_t*result = me->parent->user_data;
	assert(!result->output);
	result->output = output;
	me->user_data = NULL;
	return 0;
}

/**
 * 属性转换函数
 */
int32_t output_attr_style_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_output_t*output = me->user_data;
	if (!strcmp(attr_value, "array"))
	{
		output->style = STRUCT_ARRAY_STYLE;
		return 0;
	}

	LIB_ERROR(PLUGIN, "we can not covert output style for:'%s'!\n", attr_value);
	return -1;
}

