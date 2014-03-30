/*
 * args_private.h
 *
 *  Created on: Sep 19, 2013
 *      Author: along
 */

#ifndef GEN_ARGS_PRIVATE_H_
#define GEN_ARGS_PRIVATE_H_

#include <stdint.h>

typedef struct args_variable
{
	char*var_name;
	char*var_value;
} args_variable_t;

/**
 * arg hash初始化
 * @param[in] hash_args hash参数
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t args_hash_args_init(gen_hash_args_t*hash_args);

/**
 * 变量解析
 * @param[in] variable 要解析的变量
 * @param[in] result 解析结果
 * @param[in] escape_char 转义符
 */
int32_t args_variable_parse(char*variable, args_variable_t*result,
		char escape_char);



#endif /* ARGS_PRIVATE_H_ */
