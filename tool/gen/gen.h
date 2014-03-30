
#ifndef GEN_H_
#define GEN_H_

#include <stdint.h>

/**
 * 输出函数
 * @param[in] arg 参数
 * @param[in] str 要输出的字符串
 * @param[in] ... 其它参数
 */
typedef void (*gen_output_fun)(void*arg,char* fmt,...);

#include "debug/gen_debug.h"
#include "hash/gen_hash.h"
#include "cfg/gen_cfg_parse.h"
#include "parse/gen_buffer.h"
#include "args/gen_args.h"
#include "parse/gen_parse.h"
#endif
