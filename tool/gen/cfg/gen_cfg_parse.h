/*
 * gen_cfg_parse.h
 *
 *  Created on: Sep 14, 2013
 *      Author: along
 */

#ifndef GEN_CFG_PARSE_H_
#define GEN_CFG_PARSE_H_

#include <stdio.h>

/**
 * 配置项
 */
typedef struct gen_cfg_item
{
	char*name;
	char*value;
}gen_cfg_item_t;

/**
 * 配置解析
 * @param[in] file 配置文件
 * @param[in] item_tbl 配置项表
 * @param[in] max_size 最大配置项表
 * @return 0 配置解析成功
 * @return !0 配置解析失败
 */
int32_t gen_cfg_parse(FILE*file,gen_cfg_item_t* item_tbl,uint32_t max_size);


#endif /* GEN_CFG_PARSE_H_ */
