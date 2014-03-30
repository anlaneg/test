/*
 * xp_plugin_easyweb_check.c
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
 * check节点进入函数
 */
int32_t check_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_check_t* check = LIB_MEM_ALLOC(sizeof(xp_parse_check_t));
	if (!check)
	{
		LIB_ERROR(PLUGIN, "alloc memory for check tag parse fail!\n");
		return -1;
	}
	memset(check, 0, sizeof(xp_parse_check_t));
	me->user_data = check;
	return 0;
}

/**
 * check节点离开函数
 */
int32_t check_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_check_t*check = me->user_data;
	assert(check);
	assert(!strcmp(me->parent->self_syntax->name, "state"));
	xp_parse_state_t*state = me->parent->user_data;
	assert(state);
	assert(!state->check);
	state->check = check;
	me->user_data = NULL;
	return 0;
}
