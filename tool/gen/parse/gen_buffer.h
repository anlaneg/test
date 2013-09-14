#ifndef GEN_BUFFER_H_
#define GEN_BUFFER_H_

#include <stdint.h>

/**
 * 输出函数
 * @param[in] str 要输出的字符串
 * @param[in] arg 参数
 * @return 生成的长度
 */
typedef int32_t (*gen_output_fun)(char* str, void*arg);

/**
 * buffer
 */
typedef struct gen_buffer
{
	gen_output_fun output;
	void*arg;
	int32_t size;
	int32_t empty_loc;
	char buffer[0];
} gen_buffer_t;

/**
 * 初始化buffer
 * @param[in] buffer
 * @param[in] size 大小
 * @param[in] output 输出函数
 * @param[in] arg 参数
 * @return 0 成功
 * @return !0 失败
 */
int32_t gen_buffer_t* gen_buffer_init(gen_buffer_t* buffer, int32_t size,
		gen_output_fun output, void*arg);

/**
 * 销毁buffer
 * @param[in] buffer
 */
void gen_buffer_destroy(gen_buffer_t*);

/**
 * flush buffer
 * @param[in] buffer
 * @param[in] output 输出
 * @param[in] arg 参数
 * @return 生成的长度
 */
int32_t gen_buffer_flush(gen_buffer_t*buffer, gen_output_fun output, void*arg);

/**
 * append str
 * @param[in] buffer
 * @param[in] str 字符串
 * @param[in] length 长度
 * @return 输出的长度
 */
int32_t gen_buffer_append(gen_buffer_t*buffer, char*str, uint32_t length);

#endif /* GEN_BUFFER_H_ */
