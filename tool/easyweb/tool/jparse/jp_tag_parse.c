/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse使用的tag
 * @logic:
 */

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "jp_debug.h"
#include "json_parse.h"
#include "jp.h"
#include "jp_tag_attribute.h"
#include "jp_tag.h"
#include "jp_symbol_table.h"
#include "json_parse.h"
#include "jp_debug.h"
#include "libstr.h"
#include "libmem.h"
#include "jp_attribute_parse.h"
#include "jp_tag_parse.h"

int32_t json_parse_property_parent(json_t* json_parent, jp_tag_t* tag)
{
	char* tag_value;

	if (!json_parent->valuestring)
	{
		jp_tag_set_parent(tag, NULL );
		return 0;
	}

	tag_value = libstr_strdup(json_parent->valuestring);
	if (!tag_value)
	{
		return -1;
	}
	jp_tag_set_parent(tag, tag_value);
	return 0;
}

int32_t json_parse_property_require(json_t* json_require, jp_tag_t*tag)
{
	if (!strcmp(json_require->valuestring, "true"))
	{
		jp_tag_flag_set_require(tag);
	}
	else if (!strcmp(json_require->valuestring, "false"))
	{
		jp_tag_flag_set_eliminate(tag);
	}
	else
	{
		return -1;
	}

	return 0;
}

int32_t json_parse_property_comment(json_t* json_comment, jp_tag_t*tag)
{
	char* tag_value = libstr_strdup(json_comment->valuestring);
	if (!tag_value)
	{
		return -1;
	}
	jp_tag_set_comment(tag, tag_value);
	return 0;
}


int32_t json_parse_property_attribute(json_t* json_attribute, jp_tag_t*tag)
{
	json_t* property;
	jp_tag_attribute_t* attribute;

	assert(json_attribute);
	assert(json_attribute->type == JSON_TYPE_ARRAY);

	for (property = json_attribute->child; property; property = property->next)
	{
		assert(property->type == JSON_TYPE_OBJECT);
		if (!(attribute = jp_tag_attribute_create()))
		{
			LIB_ERROR(PARSER, "create empty attribute fail!\n");
			return -1;
		}

		assert(property->type == JSON_TYPE_OBJECT);
		if (json_parse_attribute(property, attribute))
		{
			LIB_ERROR(PARSER, "parse attribute fail!\n");
			jp_tag_attribute_destroy(attribute);
			return -1;
		}

		jp_tag_set_attribute(tag, attribute);
	}
	return 0;
}

int32_t json_parse_property_tag(json_t* json_tag, jp_tag_t*tag)
{
	char* tag_value = libstr_strdup(json_tag->valuestring);
	if (!tag_value)
	{
		return -1;
	}
	jp_tag_set_name(tag, tag_value);
	return 0;
}

