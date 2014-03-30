#include <assert.h>

#include "gen.h"
#include "gen_buffer.h"
#include "libmem.h"

/**
 * 创建buffer
 * @param[in] size 大小
 * @param[in] output 输出函数
 * @param[in] arg 参数
 * @return !NULL 成功
 * @return NULL 失败
 */
gen_buffer_t* gen_buffer_create(int32_t size, gen_output_fun output, void*arg)
{
	gen_buffer_t* buffer;

	buffer = LIB_MEM_ALLOC(size + sizeof(gen_buffer_t) + 1); //add '\0'
	if (!buffer)
	{
		LIB_ERROR(PARSER,"create buffer size :%d fail!\n", size);
		return NULL ;
	}

	buffer->arg = arg;
	buffer->empty_loc = 0;
	buffer->output = output;
	buffer->size = size;
	return buffer;
}

/**
 * 销毁buffer
 * @param[in] buffer
 */
void gen_buffer_destroy(gen_buffer_t* buffer)
{
	assert(buffer);
	LIB_MEM_FREE(buffer);
}

/**
 * flush buffer
 * @param[in] buffer
 * @return 生成的长度
 */
int32_t gen_buffer_flush(gen_buffer_t*buffer)
{
	if (buffer->empty_loc > 0)
	{
		assert(buffer->buffer[buffer->empty_loc] == '\0');
		buffer->output(buffer->arg, buffer->buffer);
		buffer->empty_loc = 0;
	}
	return 0;
}

static void buffer_copy_str(gen_buffer_t*buffer, char*str, uint32_t length)
{
	uint32_t i = 0;

	assert(buffer);
	assert(str);

	for (/**/; i < length && str[i] != '\0'; ++i)
	{
		buffer->buffer[buffer->empty_loc + i] = str[i];
	}

	buffer->empty_loc += i;
	assert(buffer->empty_loc <= buffer->size);
	buffer->buffer[buffer->empty_loc] = '\0';
}

static void buffer_append_largest(gen_buffer_t*buffer, char*str,
		uint32_t total_length)
{
	uint32_t write;
	uint32_t offset = 0;
	uint32_t length = total_length;
	while (length)
	{
		write = (buffer->size <= length) ? buffer->size : length;
		offset += write;
		gen_buffer_append(buffer, str + offset, write);
		length -= write;
	}
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
	assert(buffer);
	assert(str);

	if (buffer->empty_loc + length < buffer->size)
	{
		buffer_copy_str(buffer, str, length);
		return 0;
	}

	gen_buffer_flush(buffer);
	if (length <= buffer->size)
	{
		buffer_copy_str(buffer, str, length);
		return 0;
	}

	buffer_append_largest(buffer, str, length);
	return 0;
}
