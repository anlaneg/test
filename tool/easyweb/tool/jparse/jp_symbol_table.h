/**
 * @author: along
 * @date : 2013-09-04
 * @brief :定义jparse符号表
 * @logic:
 */

#ifndef JPARSE_SYMBOL_TABLE_H_
#define JPARSE_SYMBOL_TABLE_H_

#include <stdint.h>

/**
 * 符号表最大项
 */
#define JP_TAG_MAX_SYMBOL_TABLE_SIZE (128ULL)


struct jp_tag;
struct jp_tag_attribute;

/**
 * 符号表
 */
typedef struct jp_symbol_table
{
	uint32_t tag_table_length;
	struct jp_tag*tag_table[JP_TAG_MAX_SYMBOL_TABLE_SIZE +1];
} jp_symbol_table_t;


/**
 *  符号表
 */
extern jp_symbol_table_t g_symbol_table;
/**
 * 符号初始化
 * @param[in] symbol_table 符号表
 * @return 0 符号表初始化成功
 * @return !0 符号表初始化失败
 */
int32_t jp_tag_symbol_table_init(jp_symbol_table_t* symbol_table);

/**
 * 符号表反初始化
 * @paramp[in] symbol_table 符号表
 */
void jp_tag_symbol_table_uninit(jp_symbol_table_t* symbol_table);

/**
 * 属性值插入
 * @param[in] symbol_table 符号表
 * @param[in] tag_name 标签名
 * @param[in] tag_parent 标签父节点名称
 * @param[in] attribute 属性
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t jp_tag_attribute_insert(jp_symbol_table_t*symbol_table, const char*tag_name,
		const char*tag_parent, struct jp_tag_attribute * attribute);

/**
 * 标签插入
 * @param[in] symbol_table 符号表
 * @param[in] tag 要插入的标签
 * @return 0 插入成功
 * @return !0 插入失败
 */
int32_t jp_tag_insert(jp_symbol_table_t*symbol_table, struct jp_tag*tag);

/**
 * 标签查询
 * @param[in] symbol_table 符号表
 * @param[in] name 标签名
 * @param[in] parent 父节点名称
 * @return NULL 查询失败
 * @return !NULL 查询成功
 */
struct jp_tag*jp_tag_lookup(jp_symbol_table_t*symbol_table, const char*name,
		const char*parent);

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
		const char*tag_name, const char*tag_parent, const char*attribute_name);

#endif /* JPARSE_SYMBOL_TABLE_H_ */
