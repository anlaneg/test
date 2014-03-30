/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse符号表
 * @logic:
 */
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include "json_parse.h"
#include "jp.h"
#include "jp_symbol_table.h"
#include "jp_tag_attribute.h"
#include "jp_tag.h"

/**
 *  符号表
 */
jp_symbol_table_t g_symbol_table;

/**
 * 查询出符号表中空的tag索引号
 * @param[in] symbol_table 符号表
 * @return 索引号
 */
static uint32_t tag_symbol_table_empty_room_index_find(
		jp_symbol_table_t* symbol_table)
{
	uint32_t i;
	for (i = 0; i < JP_TAG_MAX_SYMBOL_TABLE_SIZE; ++i)
	{
		if (!symbol_table->tag_table[i])
		{
			break;
		}
	}
	return i;
}

/**
 * 查询出符号表中指定标签项索引
 * @param[in] symbol_table 符号表
 * @param[in] tag 标签
 * @return < 0 索引号查询失败
 * @return >= 0 索引号查询成功
 */
static int32_t tag_attribute_room_index_find(jp_symbol_table_t* symbol_table,
		jp_tag_t* tag)
{
	uint32_t i;
	assert(tag);

	for (i = 0; i < JP_TAG_MAX_SYMBOL_TABLE_SIZE; ++i)
	{
		if (symbol_table->tag_table[i] == tag)
		{
			return i;
		}
	}
	return -1;
}
/**
 * 符号初始化
 * @param[in] symbol_table 符号表
 * @return 0 符号表初始化成功
 * @return !0 符号表初始化失败
 */
int32_t jp_tag_symbol_table_init(jp_symbol_table_t* symbol_table)
{
	memset(symbol_table, 0, sizeof(jp_symbol_table_t));
	return 0;
}

/**
 * 符号表反初始化
 * @paramp[in] symbol_table 符号表
 */
void jp_tag_symbol_table_uninit(jp_symbol_table_t* symbol_table)
{
	uint32_t i;
	for (i = 0; i < JP_TAG_MAX_SYMBOL_TABLE_SIZE; ++i)
	{
		jp_tag_t* tag = symbol_table->tag_table[i];
		if(tag)
		{
			jp_tag_destroy(tag);
		}
	}

	memset(symbol_table, 0, sizeof(jp_symbol_table_t));
}

/**
 * 属性值插入
 * @param[in] symbol_table 符号表
 * @param[in] tag_name 标签名
 * @param[in] tag_parent 标签父节点名称
 * @param[in] attribute 属性
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t jp_tag_attribute_insert(jp_symbol_table_t*symbol_table,
		const char*tag_name, const char*tag_parent,
		struct jp_tag_attribute * attribute)
{
	jp_tag_t* tag;

	assert(symbol_table);
	assert(tag_name);
	assert(tag_parent);
	assert(attribute);

	tag = jp_tag_lookup(symbol_table, tag_name, tag_parent);
	if (!tag)
	{
		return -1;
	}

	jp_tag_set_attribute(tag, attribute);
	return 0;
}

/**
 * 标签插入
 * @param[in] symbol_table 符号表
 * @param[in] tag 要插入的标签
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t jp_tag_insert(jp_symbol_table_t*symbol_table, struct jp_tag*tag)
{
	jp_tag_t* old;

	assert(symbol_table);
	assert(tag);
	assert(tag->name);
	//assert(tag->parent);

	int32_t idx;
	old = jp_tag_lookup(symbol_table, tag->name, tag->parent);
	if (old)
	{
		idx = tag_attribute_room_index_find(symbol_table, old);
		assert(idx != -1);

		//destroy old
		jp_tag_destroy(old);
	}
	else
	{
		uint32_t tmp_idx = tag_symbol_table_empty_room_index_find(symbol_table);
		idx = (int32_t) tmp_idx;
		assert(idx >= 0 && (uint32_t ) idx == tmp_idx);
	}

	symbol_table->tag_table[idx] = tag;
	symbol_table->tag_table_length++;

	return 0;
}

/**
 * 标签查询
 * @param[in] symbol_table 符号表
 * @param[in] name 标签名
 * @param[in] parent 父节点名称
 * @return NULL 查询失败
 * @return !NULL 查询成功
 */
struct jp_tag*jp_tag_lookup(jp_symbol_table_t*symbol_table, const char*name,
		const char*parent)
{
	uint32_t i;
	for (i = 0; i < JP_TAG_MAX_SYMBOL_TABLE_SIZE; ++i)
	{
		jp_tag_t* tag = symbol_table->tag_table[i];
		if (!tag)
		{
			break;
		}

		if (strcmp(tag->name, name))
		{
			continue;
		}

		if (!tag->parent && parent == NULL )
		{
			return tag;
		}

		if (!strcmp(tag->parent, parent))
		{
			return tag;
		}
	}

	return NULL ;
}

/**
 * 属性查询
 * @param[in] symbol_table 符号表
 * @param[in] tag_name 标签名称
 * @param[in] tag_parent 父标签名称
 * @param[in] attribute_name 属性名称
 * @return NULL 查询失败
 * @reutrn !NULL 查询成功
 */
struct jp_tag_attribute* jp_tag_attribute_lookup(jp_symbol_table_t*symbol_table,
		const char*tag_name, const char*tag_parent, const char*attribute_name)
{
	jp_tag_t* tag;
	jp_tag_attribute_t* attribute;

	assert(symbol_table);
	assert(tag_name);
	assert(attribute_name);

	tag = jp_tag_lookup(symbol_table, tag_name, tag_parent);
	if (!tag)
	{
		return NULL ;
	}

	attribute = jp_tag_get_attribute(tag, (char*) attribute_name);
	if (!attribute)
	{
		return NULL ;
	}

	return attribute;
}
