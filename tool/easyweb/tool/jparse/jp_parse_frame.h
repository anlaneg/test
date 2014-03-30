/**
 * @author: along
 * @date : 2013-09-02
 * @brief :本文件用于实现解析json对象框架
 * @logic:
 *   1.要解析的对象有两种，一种是tag,一种是attribute
 */

#ifndef JP_PARSE_FRAME_H_
#define JP_PARSE_FRAME_H_

#include <stdint.h>

/**
 * 最大解析parse handle数
 */
#define JP_MAX_TAG_PARSE_HANDLE (31ULL)
/**
 * tag解析
 */
typedef struct jp_tag_parse_handle
{
	int32_t (*init)(jp_tag_t*); //初始化
	int32_t (*parse)(json_t*, jp_tag_t*); //解释
	void (*dump)(dump_out_fun out, jp_tag_t*,void*arg); //dump
	void (*uninit)(jp_tag_t*); //销毁
} jp_tag_parse_handle_t;

/**
 * attribute解析
 */
typedef struct jp_attribute_parse_handle
{
	int32_t (*init)(jp_tag_attribute_t*); //初始化
	int32_t (*parse)(json_t*, jp_tag_attribute_t*); //解析
	void (*dump)(dump_out_fun out, jp_tag_attribute_t*,void*arg); //dump
	void (*uninit)(jp_tag_attribute_t*); //销毁
} jp_attribute_parse_handle_t;

typedef enum handle_type
{
	VALID_HANDLE = 0, TAG_HANDLE, ATTRIBUTE_HANDLE
} handle_type_t;
/**
 * parse主控
 */
typedef struct jp_parse_handle
{
	handle_type_t type;
	char* name;
	//TODO xpath没有使用
	/**
	 * 用于指出父节点，例如:
	 * 根节点xpath 为"/"
	 * input节点的xpath 为"/state/"
	 * packet属性的xpath为"/state" {注意，不能有'/‘符}
	 */
	//char* xpath;
	union
	{
		jp_tag_parse_handle_t tag_handle;
		jp_attribute_parse_handle_t attribute_handle;
	} type_ops;
} jp_parse_handle_t;

int32_t jp_parse_handle_register(jp_parse_handle_t*handle);
int32_t jp_parse_handle_parse(json_t*json, jp_symbol_table_t* symbol_table);
void jp_parse_handle_unregister(jp_parse_handle_t*handle);
jp_parse_handle_t* jp_parse_handle_lookup(jp_parse_handle_t*handle);
/**
 * 解析句柄初始化
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t jp_parse_handle_init();

#endif /* JP_PARSE_FRAME_H_ */
