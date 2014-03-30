/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse tag attribute
 * @logic:
 */
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "json_parse.h"
#include "jp.h"
#include "jp_tag_attribute.h"
#include "libmem.h"

/**
 * 创建一个tag attribute对象
 * @return NULL 创建失败
 * @return !NULL 创建成功
 */
jp_tag_attribute_t* jp_tag_attribute_create()
{
	jp_tag_attribute_t* attribute = (jp_tag_attribute_t*) LIB_MEM_ALLOC(
			sizeof(jp_tag_attribute_t));
	if (!attribute)
	{
		return NULL ;
	}

	memset(attribute, 0, sizeof(jp_tag_attribute_t));
	return attribute;
}

/**
 * 销毁tag attribute对象
 * @param[in] attribute 属性
 */
void jp_tag_attribute_destroy(jp_tag_attribute_t* attribute)
{
	assert(attribute);
	if (attribute->name)
	{
		LIB_MEM_FREE(attribute->name);
	}

	if (attribute->comment)
	{
		LIB_MEM_FREE(attribute->comment);
	}

	if (attribute->text_value)
	{
		LIB_MEM_FREE(attribute->text_value);
	}

	if (attribute->value)
	{
		LIB_MEM_FREE(attribute->value);
	}

	LIB_MEM_FREE(attribute);
}

/**
 * dump tag
 * @param[in] out 输出函数
 * @param[in] tag 标签
 * @param[in] arg 输出参数
 * @return NULL 格式化失败
 * @return !NULL 格式化成功
 */
void jp_tag_attribute_dump(dump_out_fun out,jp_tag_attribute_t* attribute, void*arg)
{
	out(arg,"\tname:%s,type:%d,comment:%s\n",attribute->name,attribute->type,attribute->comment);
}
/**
 * 设置属性名称
 * @param[in] attribute 属性对象
 * @param[in] name 属性名称
 */
void jp_tag_attribute_set_name(jp_tag_attribute_t* attribute, char*name)
{
	assert(attribute);
	if (attribute->name)
	{
		LIB_MEM_FREE(attribute->name);
	}

	attribute->name = name;
}

/**
 * 设置属性类型
 * @param[in] attribute 属性对象
 * @param[in] type 属性类型
 */
void jp_tag_attribute_set_type(jp_tag_attribute_t* attribute, enum jp_type type)
{
	assert(attribute);
	attribute->type = type;
}

/**
 * 设置属性注释
 * @param[in] attribute 属性对象
 * @param[in] comment 注释
 */
void jp_tag_attribute_set_comment(jp_tag_attribute_t* attribute, char*comment)
{
	assert(attribute);
	if (attribute->comment)
	{
		LIB_MEM_FREE(attribute->comment);
	}

	attribute->comment = comment;
}

/**
 * 设置属性字面值
 * @param[in] attribute 属性对象
 * @param[in] text_value 字面值
 */
void jp_tag_attribute_set_text_value(jp_tag_attribute_t* attribute,
		char*text_value)
{
	assert(attribute);
	if (attribute->text_value)
	{
		LIB_MEM_FREE(attribute->text_value);
	}

	attribute->text_value = text_value;
}

/**
 * 获取属性名称
 * @param[in] attribute 属性对象
 * @return 属性名称
 */
char* jp_tag_attribute_get_name(jp_tag_attribute_t*attribute)
{
	assert(attribute);
	return attribute->name;
}

/**
 * 获取属性类型
 * @param[in] attribute 属性对象
 * @return 属性类型
 */
enum jp_type jp_tag_attribute_get_type(jp_tag_attribute_t*attribute)
{
	assert(attribute);
	return attribute->type;
}

/**
 * 获取属性注释信息
 * @param[in] attribute 属性对象
 * @return 注释信息
 */
char* jp_tag_attribute_get_comment(jp_tag_attribute_t*attribute)
{
	assert(attribute);
	return attribute->comment;
}

/**
 * 获取属性字面值
 * @param[in] attribute 属性对象
 * @return 字面值
 */
char* jp_tag_atrribute_get_text_value(jp_tag_attribute_t*attribute)
{
	assert(attribute);
	return attribute->text_value;
}
