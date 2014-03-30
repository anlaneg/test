/**
 * @author: along
 * @date : 2013-08-31
 * @brief :
 * @logic:
 */

#ifndef JPASER_H_
#define JPASER_H_

#include <stdio.h>
#include <stdarg.h>

struct jp_symbol_table ;

typedef void (*dump_out_fun)(void*arg,char*fmt,...);

typedef struct jp_jparse_args
{
	int32_t is_need_show_help;
	int32_t is_need_show_version;
	int32_t is_need_verbose;
	char* complier_file;
	char* output_path;
}jp_jparse_args_t;

/**
 * 用于记录命令行参数
 */
extern jp_jparse_args_t g_jparse_args;

/**
 * jparser参数解析
 * @param[out] local_args 出参，记录转换后的命令行输入
 * @param[in] argc 参数数目
 * @param[in] argv 参数
 * @return 0 参数解析成功
 * @return !0 参数解析失败
 */
int32_t jparse_args_process(jp_jparse_args_t*local_args,int argc,char**argv);

/**
 * jparse参数销毁
 * @param[in] local_args 要销毁的参数
 */
void jparse_args_destroy(jp_jparse_args_t*local_args);

/**
 * 解析指定文件，返回json对象
 * @param[in] filename 要解析的文件名称
 * @return NULL 解析失败
 * @return !NULL 解析成功
 */
json_t* jparse_file_load(const char*filename);

/**
 * json解析
 * @param[in] json json对象
 * @param[in] symbol_table 符号表
 * @return 0 解析成功
 * @return !0 解析失败
 */
int32_t jparse_json_parse(json_t * json, struct jp_symbol_table* symbol_table);

/**
 * dump
 * @param[in] arg 参数
 * @param[in] fmt 字符串
 * @param[in] ... 参数
 */
static inline void jparse_dump(void*arg,char*fmt,...)
{
	va_list va;
	va_start(va,fmt);
	vfprintf(stderr,fmt,va);
	va_end(va);
}


#endif /* JPASER_H_ */
