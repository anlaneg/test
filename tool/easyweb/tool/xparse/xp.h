/*
 * xp.h
 *
 *  Created on: Oct 13, 2013
 *      Author: along
 */

#ifndef XP_H_
#define XP_H_

/**
 * 解析阶段
 */
typedef enum xp_parse_phase
{
	XPARSE_PHASE_SYNTAX=1,
	XPARSE_PHASE_SEMANTICS,
	XPARSE_PHASE_GENERATE,

	XPARSE_PHASE_MAX,
}xp_parse_phase_t;

/**
 * 框架初始化
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t xp_parse_init();

/**
 * 文件加载
 * @param[in] xml 文件
 * @return NULL 解析文件失败
 * @return !NULL 解析文件成功
 */
libxml_node_t* xp_parse_load_file(const char* xml);

/**
 * 框架执行指定阶段
 * @param[in] phase 阶段
 * @param[in] args 参数
 * @return 0 阶段执行成功
 * @return !0 阶段执行失败
 */
int32_t xp_parse_execute_phase(xp_parse_phase_t phase, libxml_node_t* root);

/**
 * 框架销毁
 * @return 0 销毁成功
 * @return !0 销毁失败
 */
int32_t xp_parse_destroy();

#endif /* XP_H_ */
