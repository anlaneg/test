/*
 * xp_plugin_easyweb_member_validate.c
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

/**
 * input 节点进入函数
 */
int32_t member_validate_tag_entry_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_member_validate_t*validate = LIB_MEM_ALLOC(sizeof(xp_parse_member_validate_t));
	memset(validate,0,sizeof(xp_parse_member_validate_t));
	me->user_data = validate;

	return 0;
}

/**
 * 节点离开函数
 */
int32_t member_validate_tag_exit_fun(libxml_node_t*node, struct xp_syntax_tree_node*me)
{
	xp_parse_member_validate_t*validate = me->user_data;
	LIB_INFO(PLUGIN, "validate max-length:%d,comment:%s\n", validate->max_length,validate->comment);
	xp_parse_member_t*member = me->parent->user_data;
	assert(member);
	assert(!member->member_validate);
	member->member_validate = validate;
	me->user_data = NULL;
	return 0;
}

/**
 * 属性转换函数
 */
int32_t member_validate_attr_max_length_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_validate_t*validate = me->user_data;
	char*end=NULL;
	uint32_t tmp;
	tmp=strtoul(attr_value,&end,10);
	if((*end!='\0'))
	{
		LIB_ERROR(PLUGIN,"conversion fail!\n");
		return -1;
	}
	validate->max_length=tmp;
	return 0;
}

/**
 * 属性转换函数
 */
int32_t member_validate_attr_comment_convert_fun(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me)
{
	xp_parse_member_validate_t*validate = me->user_data;
	validate->comment=libstr_strdup(attr_value);
	return 0;
}
