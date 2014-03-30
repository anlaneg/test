/*
 * json_parse.h
 *
 *  Created on: Sep 1, 2013
 *      Author: along
 */

#ifndef JSON_PARSE_H_
#define JSON_PARSE_H_

#include "cJSON.h"

typedef cJSON json_t;

/**
 * json类型
 */
typedef enum json_type
{
	JSON_TYPE_FALSE = cJSON_False,
	JSON_TYPE_TRUE = cJSON_True,
	JSON_TYPE_NULL = cJSON_NULL,
	JSON_TYPE_NUMBER = cJSON_Number,
	JSON_TYPE_STRING = cJSON_String,
	JSON_TYPE_ARRAY = cJSON_Array,
	JSON_TYPE_OBJECT = cJSON_Object
} json_type_t;

/**
 * 将字符串转换为json对象
 * @param[in] value 字符串
 * @param[out] error_loc 如果解析失败，返回失败原因
 * @return NULL 转换失败
 * @return !NULL 转换成功
 */
static inline json_t* json_text_parse(const char*value, const char**error_loc)
{
	json_t* json;
	json = cJSON_Parse(value);
	if (!json)
	{
		*error_loc = cJSON_GetErrorPtr();
	}
	return json;
}

/**
 * 销毁json对象
 * @param[in] json 要销毁的json对象
 */
static inline void json_object_destroy(json_t* json)
{
	cJSON_Delete(json);
}

/**
 * 将json对象转换为字符串
 * @param[in] json 要转换的json对象
 * @return NULL 转换失败
 * @return !NULL 转换成功
 */
static inline const char* json_object_print(json_t*json)
{
	return cJSON_Print(json);
}

#endif /* JSON_PARSE_H_ */
