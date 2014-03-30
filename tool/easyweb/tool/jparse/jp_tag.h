/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse使用的tag
 * @logic:
 */

#ifndef JP_TAG_H_
#define JP_TAG_H_

#include <stdint.h>

/**
 * 定义属性值最大数
 */
#define JP_TAG_MAX_ATTRIBUTE_SIZE (64ULL)

enum jp_type;
struct jp_tag_attribute;

/**
 * 定义标签项
 */
typedef struct jp_tag
{
	char* name; //名称
	char* parent; //父节点名称
	char* comment; //注释信息
	char* text_value; //如果节点使用<p>display</p>这种形式，则记录display
	void* value;
	struct jp_tag_attribute*attribute[JP_TAG_MAX_ATTRIBUTE_SIZE + 1];
//#define JP_IS_HAVE_ATTRIBUTE        0x2 //指明此标答有attribute
#define JP_TAG_FLAG_IS_NEED_USE_TEXT_VALUE 	0X1 //指明需要使用text_value
#define JP_TAG_FLAG_IS_REQUIRE 0x2 //指明是否必须的
	uint32_t flag;
	//is_require
	//uint32_t attribute_count; //属性数目
	//uint32_t child_node_count;　//子节点数目
	enum jp_type type;

} jp_tag_t;

/**
 * 创建tag
 * @return NULL 创建失败
 * @return !NULL 创建成功
 */
jp_tag_t* jp_tag_create();

/**
 * 销毁tag
 * @param[in] tag 要销毁的tag
 */
void jp_tag_destroy(jp_tag_t*tag);

/**
 * 设置tag名称
 * @param[in] tag 要设置的tag
 * @param[in] name 要设置的名称
 */
void jp_tag_set_name(jp_tag_t*tag, char*name);

/**
 * 设置tag父节点名称
 * @param[in] tag 要设置的tag
 * @param[in] parent 指定父节点
 */
void jp_tag_set_parent(jp_tag_t*tag, char*parent);

/**
 * 设置tag节点注释
 * @param[in] tag 要设置的tag
 * @param[in] comment 要设置的注释
 */
void jp_tag_set_comment(jp_tag_t*tag, char*comment);

/**
 * 设置tag字面值
 * @param[in] tag 要设置的tag
 * @param[in] text_value 要设置的字面值
 */
void jp_tag_set_text_value(jp_tag_t*tag, char*text_value);

/**
 * 设置tag类型
 * @param[in] tag 要设置的类型
 * @param[in] type 类型
 */
void jp_tag_set_type(jp_tag_t*tag, enum jp_type type);

/**
 * 设置tag属性
 * @param[in] tag 要设置的类型
 * @param[in] attribute 要设置的类型
 */
void jp_tag_set_attribute(jp_tag_t*tag, struct jp_tag_attribute* attribute);

/**
 * 设置tag真实value
 * @param[in] tag 要设置的类型
 * @param[in] value 要设置的真实value
 */
void jp_tag_set_value(jp_tag_t* tag, void*value);

/**
 * 设置tag必须flag
 * @param[in] tag 要设置的类型
 */
void jp_tag_flag_set_require(jp_tag_t*tag);

/**
 * 设置tag非必须flag
 * @param[in] tag 要设置的类型
 */
void jp_tag_flag_set_eliminate(jp_tag_t*tag);
/**
 * 获取tag名称
 * @param[in] tag 要获取的tag
 * @return tag名称
 */
char* jp_tag_get_name(jp_tag_t*tag);

/**
 * 获取tag父节点
 * @param[in] tag 要获取的tag
 * @return tag父节点
 */
char* jp_tag_get_parent(jp_tag_t*tag);

/**
 * 获取tag注释
 * @param[in] tag 要获取的tag
 * @return 注释内容
 */
char* jp_tag_get_comment(jp_tag_t*tag);

/**
 * 获取tag字面值
 * @param[in] tag 要获取的tag
 * @return 字面值
 */
char* jp_tag_get_text_value(jp_tag_t*tag);

/**
 * 获取类型
 * @param[in] tag 获取的tag
 * @return 类型值
 */
enum jp_type jp_tag_get_type(jp_tag_t*tag);

/**
 * 获取tag真实value
 * @param[in] tag 获取的tag
 * @return 真实的value
 */
void* jp_tag_get_value(jp_tag_t*tag);

/**
 * 获取tag必须flag
 * @param[in] tag 要设置的类型
 * @return 0 非必须
 * @return !0 必须
 */
int32_t jp_tag_flag_get_require(jp_tag_t*tag);

/**
 * dump tag
 * @param[in] out 输出函数
 * @param[in] tag 标签
 * @param[in] arg 输出参数
 * @return NULL 格式化失败
 * @return !NULL 格式化成功
 */
void jp_tag_dump(dump_out_fun out, jp_tag_t* tag, void*arg);

/**
 * 获取tag属性
 * @param[in] tag 标签
 * @param[in] attribute_name 属性名称
 * @return NULL 获取属性失败
 * @reutrn !NULL 获取属性成功
 */
struct jp_tag_attribute* jp_tag_get_attribute(jp_tag_t*tag, char*attribute_name);

#endif /* JP_TAG_H_ */
