/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse定义的tag_attribute
 * @logic:
 */

#ifndef JP_TAG_ATTRIBUTE_H_
#define JP_TAG_ATTRIBUTE_H_

#include <stdint.h>

enum jp_type;

/**
 * 定义xml中的类型值
 */
typedef enum jp_type
{
	JP_TYPE_INVALID = 0, //
	JP_TYPE_STRING, //字符串类型

	JP_TYPE_MAXVALUE,
} jp_type_t;

/**
 * 定义属性项
 */
typedef struct jp_tag_attribute
{
	char* name; //指出属性名称
	enum jp_type type; //指出类型
	char* comment; //指出注释
	char* text_value; //指出字符串
	uint32_t flag; //指出flag
	void* value; //类型对应值
} jp_tag_attribute_t;

/**
 * 创建一个tag attribute对象
 * @return NULL 创建失败
 * @return !NULL 创建成功
 */
jp_tag_attribute_t* jp_tag_attribute_create();

/**
 * 销毁tag attribute对象
 * @param[in] attribute 属性
 */
void jp_tag_attribute_destroy(jp_tag_attribute_t* attribute);

/**
 * 设置属性名称
 * @param[in] attribute 属性对象
 * @param[in] name 属性名称
 */
void jp_tag_attribute_set_name(jp_tag_attribute_t* attribute, char*name);

/**
 * 设置属性类型
 * @param[in] attribute 属性对象
 * @param[in] type 属性类型
 */
void jp_tag_attribute_set_type(jp_tag_attribute_t* attribute, enum jp_type type);

/**
 * 设置属性注释
 * @param[in] attribute 属性对象
 * @param[in] comment 注释
 */
void jp_tag_attribute_set_comment(jp_tag_attribute_t* attribute, char*comment);

/**
 * 设置属性字面值
 * @param[in] attribute 属性对象
 * @param[in] text_value 字面值
 */
void jp_tag_attribute_set_text_value(jp_tag_attribute_t* attribute,
		char*text_value);

/**
 * 获取属性名称
 * @param[in] attribute 属性对象
 * @return 属性名称
 */
char* jp_tag_attribute_get_name(jp_tag_attribute_t*attribute);

/**
 * 获取属性类型
 * @param[in] attribute 属性对象
 * @return 属性类型
 */
enum jp_type jp_tag_attribute_get_type(jp_tag_attribute_t*attribute);

/**
 * 获取属性注释信息
 * @param[in] attribute 属性对象
 * @return 注释信息
 */
char* jp_tag_attribute_get_comment(jp_tag_attribute_t*attribute);

/**
 * 获取属性字面值
 * @param[in] attribute 属性对象
 * @return 字面值
 */
char* jp_tag_atrribute_get_text_value(jp_tag_attribute_t*attribute);

/**
 * dump tag
 * @param[in] out 输出函数
 * @param[in] tag 标签
 * @param[in] arg 输出参数
 * @return NULL 格式化失败
 * @return !NULL 格式化成功
 */
void jp_tag_attribute_dump(dump_out_fun out,jp_tag_attribute_t* attribute, void*arg);

#endif /* JP_TAG_ATTRIBUTE_H_ */
