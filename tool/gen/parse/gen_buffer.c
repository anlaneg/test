
#include "gen.h"
#include "gen_buffer.h"

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
		gen_output_fun output, void*arg)
{
	return -1;
}

/**
 * 销毁buffer
 * @param[in] buffer
 */
void gen_buffer_destroy(gen_buffer_t* buffer)
{

}

/**
 * flush buffer
 * @param[in] buffer
 * @param[in] output 输出
 * @param[in] arg 参数
 * @return 生成的长度
 */
int32_t gen_buffer_flush(gen_buffer_t*buffer, gen_output_fun output, void*arg)
{
	return -1;
}

/**
 * append str
 * @param[in] buffer
 * @param[in] str 字符串
 * @param[in] length 长度
 * @return 输出的长度
 */
int32_t gen_buffer_append(gen_buffer_t*buffer, char*str, uint32_t length)
{
	return -1;
}
