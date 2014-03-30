#ifndef GEN_BUFFER_H_
#define GEN_BUFFER_H_

#include <stdint.h>

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
 * 创建buffer
 * @param[in] size 大小
 * @param[in] output 输出函数
 * @param[in] arg 参数
 * @return !NULL 成功
 * @return NULL 失败
 */
gen_buffer_t* gen_buffer_create(int32_t size, gen_output_fun output, void*arg);

/**
 * 销毁buffer
 * @param[in] buffer
 */
void gen_buffer_destroy(gen_buffer_t*);

/**
 * flush buffer
 * @param[in] buffer
 * @return 生成的长度
 */
int32_t gen_buffer_flush(gen_buffer_t*buffer);

/**
 * append str
 * @param[in] buffer
 * @param[in] str 字符串
 * @param[in] length 长度
 * @return 输出的长度
 */
int32_t gen_buffer_append(gen_buffer_t*buffer, char*str, uint32_t length);

#endif /* GEN_BUFFER_H_ */
