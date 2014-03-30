/*
 * gen_cfg_parse.h
 *
 *  Created on: Sep 14, 2013
 *      Author: along
 */

#ifndef GEN_CFG_PARSE_H_
#define GEN_CFG_PARSE_H_

struct gen_args;
/**
 * 通过配置装载变量
 * @param[in] args 配置参数
 * @return 0 配置解析装载成功
 * @return !0 配置解析装载失败
 */
int32_t gen_cfg_load_variable(struct gen_args* args);


#endif /* GEN_CFG_PARSE_H_ */
