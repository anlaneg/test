/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse使用的tag
 * @logic:
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "json_parse.h"
#include "jp.h"
#include "libmem.h"
#include "jp_tag_attribute.h"
#include "jp_tag.h"

#define MAKE_SURE_ATTRIBUTE_NULL(start,tag) ({\
	for( ; start < JP_TAG_MAX_ATTRIBUTE_SIZE; ++start)\
	{\
		assert(!tag->attribute[start]);\
	}\
	i;\
})

/**
 * 删除tag 属性
 * @param[in] tag 标签
 */
static void tag_attribute_destroy(jp_tag_t*tag)
{
	uint32_t i;
	for (i = 0; i < JP_TAG_MAX_ATTRIBUTE_SIZE; ++i)
	{
		if (!tag->attribute[i])
		{
			break;
		}
		assert(tag->attribute);
		jp_tag_attribute_destroy(tag->attribute[i]);
	}

	//确认后面的都为NULL
	assert(MAKE_SURE_ATTRIBUTE_NULL(i,tag));
}

/**
 * 查询出属性项中空的room索引号
 * @param[in] tag 标签
 * @return 索引号
 */
static uint32_t tag_attribute_empty_room_index_find(jp_tag_t* tag)
{
	uint32_t i;
	for (i = 0; i < JP_TAG_MAX_ATTRIBUTE_SIZE; ++i)
	{
		if (!tag->attribute[i])
		{
			break;
		}
	}
	return i;
}

/**
 * 查询出属性项中指定索引项索引
 * @param[in] tag 标签
 * @param[in] attribute 属性
 * @return 索引号
 */
static int32_t tag_attribute_room_index_find(jp_tag_t*tag,
		jp_tag_attribute_t*attribute)
{
	uint32_t i;
	assert(attribute);

	for (i = 0; i < JP_TAG_MAX_ATTRIBUTE_SIZE; ++i)
	{
		if (tag->attribute[i] == attribute)
		{
			return i;
		}
	}
	return -1;
}

/**
 * 查询指定属性名称
 * @param[in] tag 标签
 * @param[in] attribute_name 要查询的属性名称
 * @return NULL 查询失败
 * @return !NULL 查询成功
 */
static jp_tag_attribute_t* tag_attribute_lookup(jp_tag_t* tag,
		char*attribute_name)
{
	assert(tag);
	assert(attribute_name);

	uint32_t i;
	for (i = 0; i < JP_TAG_MAX_ATTRIBUTE_SIZE; ++i)
	{
		if (!tag->attribute[i])
		{
			break;
		}

		if (!strcmp(tag->attribute[i]->name, attribute_name))
		{
			return tag->attribute[i];
		}
	}

	//确认后面的都为NULL
	assert(MAKE_SURE_ATTRIBUTE_NULL(i,tag));
	return NULL ;
}

/**
 * 创建tag
 * @return NULL 创建失败
 * @return !NULL 创建成功
 */
jp_tag_t* jp_tag_create()
{
	jp_tag_t* tag = (jp_tag_t*) LIB_MEM_ALLOC(sizeof(jp_tag_t));
	if (!tag)
	{
		return NULL ;
	}

	memset(tag, 0, sizeof(jp_tag_t));

	return tag;
}

/**
 * 销毁tag
 * @param[in] tag 要销毁的tag
 */
void jp_tag_destroy(jp_tag_t*tag)
{
	assert(tag);

	if (tag->name)
	{
		LIB_MEM_FREE(tag->name);
	}

	if (tag->parent)
	{
		LIB_MEM_FREE(tag->parent);
	}

	if (tag->comment)
	{
		LIB_MEM_FREE(tag->comment);
	}

	if (tag->text_value)
	{
		LIB_MEM_FREE(tag->text_value);
	}

	if (tag->value)
	{
		LIB_MEM_FREE(tag->value);
	}

	if (tag->attribute)
	{
		//assert(tag->attribute_count);
		tag_attribute_destroy(tag);
	}

	LIB_MEM_FREE(tag);
}

/**
 * 设置tag名称
 * @param[in] tag 要设置的tag
 * @param[in] name 要设置的名称
 */
void jp_tag_set_name(jp_tag_t*tag, char*name)
{
	assert(tag);
	assert(name);

	if (tag->name)
	{
		LIB_MEM_FREE(tag->name);
	}

	tag->name = name;
}

/**
 * 设置tag父节点名称
 * @param[in] tag 要设置的tag
 * @param[in] parent 指定父节点
 */
void jp_tag_set_parent(jp_tag_t*tag, char*parent)
{
	assert(tag);
	//assert(parent);

	if (tag->parent)
	{
		LIB_MEM_FREE(tag->parent);
	}

	tag->parent = parent;
}

/**
 * 设置tag节点注释
 * @param[in] tag 要设置的tag
 * @param[in] comment 要设置的注释
 */
void jp_tag_set_comment(jp_tag_t*tag, char*comment)
{
	assert(tag);
	assert(comment);

	if (tag->comment)
	{
		LIB_MEM_FREE(tag->comment);
	}

	tag->comment = comment;
}

/**
 * 设置tag字面值
 * @param[in] tag 要设置的tag
 * @param[in] text_value 要设置的字面值
 */
void jp_tag_set_text_value(jp_tag_t*tag, char*text_value)
{
	assert(tag);
	assert(text_value);

	if (tag->text_value)
	{
		LIB_MEM_FREE(tag->text_value);
	}

	tag->text_value = text_value;
}

/**
 * 设置tag类型
 * @param[in] tag 要设置的类型
 * @param[in] type 类型
 */
void jp_tag_set_type(jp_tag_t*tag, enum jp_type type)
{
	assert(tag);
	tag->type = type;
}

/**
 * 设置tag属性
 * @param[in] tag 要设置的类型
 * @param[in] attribute 要设置的类型
 */
void jp_tag_set_attribute(jp_tag_t*tag, struct jp_tag_attribute* attribute)
{
	assert(tag);
	assert(attribute);
	assert(attribute->name);

	int32_t idx;
	jp_tag_attribute_t* old = tag_attribute_lookup(tag, attribute->name);
	if (old)
	{
		idx = tag_attribute_room_index_find(tag, old);
		assert(idx != -1);

		//destroy old
		jp_tag_attribute_destroy(old);
	}
	else
	{
		uint32_t tmp_idx = tag_attribute_empty_room_index_find(tag);
		idx = (int32_t) tmp_idx;
		assert(idx >= 0 && (uint32_t ) idx == tmp_idx);
	}

	tag->attribute[idx] = attribute;
}

/**
 * 设置tag真实value
 * @param[in] tag 要设置的类型
 * @param[in] value 要设置的真实value
 */
void jp_tag_set_value(jp_tag_t* tag, void*value)
{
	assert(tag);
	tag->value = value;
}

/**
 * 设置tag必须flag
 * @param[in] tag 要设置的类型
 */
void jp_tag_flag_set_require(jp_tag_t*tag)
{
	assert(tag);
	tag->flag |= JP_TAG_FLAG_IS_REQUIRE;
}

/**
 * 设置tag非必须flag
 * @param[in] tag 要设置的类型
 */
void jp_tag_flag_set_eliminate(jp_tag_t*tag)
{
	assert(tag);
	tag->flag &= ~(JP_TAG_FLAG_IS_REQUIRE);
}

/**
 * 获取tag名称
 * @param[in] tag 要获取的tag
 * @return tag名称
 */
char* jp_tag_get_name(jp_tag_t*tag)
{
	assert(tag);
	return tag->name;
}

/**
 * 获取tag父节点
 * @param[in] tag 要获取的tag
 * @return tag父节点
 */
char* jp_tag_get_parent(jp_tag_t*tag)
{
	assert(tag);
	return tag->parent;
}

/**
 * 获取tag注释
 * @param[in] tag 要获取的tag
 * @return 注释内容
 */
char* jp_tag_get_comment(jp_tag_t*tag)
{
	assert(tag);
	return tag->comment;
}

/**
 * 获取tag字面值
 * @param[in] tag 要获取的tag
 * @return 字面值
 */
char* jp_tag_get_text_value(jp_tag_t*tag)
{
	assert(tag);
	return tag->text_value;
}

/**
 * 获取类型
 * @param[in] tag 获取的tag
 * @return 类型值
 */
enum jp_type jp_tag_get_type(jp_tag_t*tag)
{
	assert(tag);
	return tag->type;
}

/**
 * 获取tag真实value
 * @param[in] tag 获取的tag
 * @return 真实的value
 */
void* jp_tag_get_value(jp_tag_t*tag)
{
	assert(tag);
	return tag->value;
}

/**
 * 获取tag必须flag
 * @param[in] tag 要设置的类型
 * @return 0 非必须
 * @return !0 必须
 */
int32_t jp_tag_flag_get_require(jp_tag_t*tag)
{
	return tag->flag & JP_TAG_FLAG_IS_REQUIRE;
}

/**
 * 获取tag属性
 * @param[in] tag 标签
 * @param[in] attribute_name 属性名称
 * @return NULL 获取属性失败
 * @reutrn !NULL 获取属性成功
 */
jp_tag_attribute_t* jp_tag_get_attribute(jp_tag_t*tag, char*attribute_name)
{
	return tag_attribute_lookup(tag, attribute_name);
}

/**
 * dump tag
 * @param[in] out 输出函数
 * @param[in] tag 标签
 * @param[in] arg 输出参数
 * @return NULL 格式化失败
 * @return !NULL 格式化成功
 */
void jp_tag_dump(dump_out_fun out, jp_tag_t* tag, void*arg)
{
	uint32_t i = 0;
	uint32_t idx = 0;
	out(arg, "name:%s,parent:%s,comment:%s\n", tag->name, tag->parent,
			tag->comment);
	idx = tag_attribute_empty_room_index_find(tag);
	for (i = 0; i < idx; ++i)
	{
		jp_tag_attribute_dump(out, tag->attribute[i], arg);
	}
}
