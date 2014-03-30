/*
 * xp_plugin_easyweb.c
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

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


static xp_syntax_item_t s_easyweb[] =
	{
			//XP_SYNTAX_TAG_ITEM_INIT(1,XP_SYNTAX_TAG_ITEM_PARENT_LIST(1),"root",0,(xp_tag_entry_fun)1,(xp_tag_exit_fun)1),
			XP_SYNTAX_TAG_ITEM_INIT(2,XP_SYNTAX_TAG_ITEM_PARENT_LIST(1),"state",1,state_tag_entry_fun,state_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(3,XP_SYNTAX_TAG_ITEM_PARENT_LIST(2),"name",1,state_attr_name_convert_fun,NULL),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(4,XP_SYNTAX_TAG_ITEM_PARENT_LIST(2),"packet",1,state_attr_packet_convert_fun,NULL),
			XP_SYNTAX_TAG_ITEM_INIT(5,XP_SYNTAX_TAG_ITEM_PARENT_LIST(2),"input",1,input_tag_entry_fun,input_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(6,XP_SYNTAX_TAG_ITEM_PARENT_LIST(5),"style",0,input_attr_style_convert_fun,"single"),
			XP_SYNTAX_TAG_ITEM_INIT(7,XP_SYNTAX_TAG_ITEM_PARENT_LIST(5,16,31),"struct",1,struct_tag_entry_fun,struct_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(8,XP_SYNTAX_TAG_ITEM_PARENT_LIST(7),"name",0,struct_attr_name_convert_fun,""),
			XP_SYNTAX_TAG_ITEM_INIT(9,XP_SYNTAX_TAG_ITEM_PARENT_LIST(7),"member",1,member_tag_entry_fun,member_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(10,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"name",1,member_attr_name_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(11,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"type",1,member_attr_type_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(12,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"pass-type",0,member_attr_pass_type_convert_fun,"in"),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(13,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"comment",1,member_attr_comment_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(14,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"is-const",0,member_attr_is_const_convert_fun,"false"),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(15,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"value",0,member_attr_value_convert_fun,""),
			XP_SYNTAX_TAG_ITEM_INIT(16,XP_SYNTAX_TAG_ITEM_PARENT_LIST(7),"input-sql",0,input_sql_tag_entry_fun,input_sql_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(17,XP_SYNTAX_TAG_ITEM_PARENT_LIST(16),"sql-statement",1,struct_attr_sql_statement_convert_fun,""),
			XP_SYNTAX_TAG_ITEM_INIT(18,XP_SYNTAX_TAG_ITEM_PARENT_LIST(16),"param",0,input_sql_param_tag_entry_fun,input_sql_param_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(19,XP_SYNTAX_TAG_ITEM_PARENT_LIST(18),"type",1,struct_attr_sql_param_type_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(20,XP_SYNTAX_TAG_ITEM_PARENT_LIST(18),"value",1,struct_attr_sql_param_value_convert_fun,""),
			XP_SYNTAX_TAG_ITEM_INIT(21,XP_SYNTAX_TAG_ITEM_PARENT_LIST(9),"validate",0,member_validate_tag_entry_fun,member_validate_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(22,XP_SYNTAX_TAG_ITEM_PARENT_LIST(21),"max-length",0,member_validate_attr_max_length_convert_fun,"0"),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(23,XP_SYNTAX_TAG_ITEM_PARENT_LIST(21),"comment",1,member_validate_attr_comment_convert_fun,""),
			XP_SYNTAX_TAG_ITEM_INIT(24,XP_SYNTAX_TAG_ITEM_PARENT_LIST(2),"check",1,check_tag_entry_fun,check_tag_exit_fun),
			XP_SYNTAX_TAG_ITEM_INIT(25,XP_SYNTAX_TAG_ITEM_PARENT_LIST(24),"result",1,result_tag_entry_fun,result_tag_exit_fun),
			XP_SYNTAX_TAG_ITEM_INIT(26,XP_SYNTAX_TAG_ITEM_PARENT_LIST(24),"default",1,result_tag_entry_fun,result_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(27,XP_SYNTAX_TAG_ITEM_PARENT_LIST(25),"value",1,result_attr_value_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(28,XP_SYNTAX_TAG_ITEM_PARENT_LIST(25,26),"comment",1,result_attr_comment_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(29,XP_SYNTAX_TAG_ITEM_PARENT_LIST(25,26),"redirect",0,result_attr_redirect_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(30,XP_SYNTAX_TAG_ITEM_PARENT_LIST(25,26),"forward",0,result_attr_forward_convert_fun,""),
			XP_SYNTAX_TAG_ITEM_INIT(31,XP_SYNTAX_TAG_ITEM_PARENT_LIST(25,26),"output",1,output_tag_entry_fun,output_tag_exit_fun),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(32,XP_SYNTAX_TAG_ITEM_PARENT_LIST(31),"style",0,output_attr_style_convert_fun,"single"),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(33,XP_SYNTAX_TAG_ITEM_PARENT_LIST(26),"value",0,result_attr_value_convert_fun,""),
			XP_SYNTAX_ATTRIBUTE_ITEM_INIT(34,XP_SYNTAX_TAG_ITEM_PARENT_LIST(2),"version",1,state_attr_version_convert_fun,NULL),

	};

/**
 * 返回语法项数组
 * @return 语法项数组
 */
xp_syntax_item_t* xp_plugin_easyweb_syntax_array_get()
{
	return s_easyweb;
}

/**
 * 返回语法项数组大小
 * @return 语法项数组大小
 */
int32_t xp_plugin_easyweb_syntax_size_get()
{
	return sizeof(s_easyweb)/sizeof(xp_syntax_item_t);
}
