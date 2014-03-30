/**
 *
 */

#ifndef LIBSTR_H
#define LIBSTR_H

#include <stdint.h>

/**
 * 实现字符串备份
 * @param[in] src 要备份的字符串
 * @return NULL 备份字符串失败
 * @return !NULL
 */
char* libstr_strdup(const char*src);

/**
 * 实现字符串长度获取
 * @param[in] src 要获取长度的字符串
 * @return 字符串长度
 */
int32_t libstr_strlen(const char*src);

/**
 * 自字符串开头查找指定字符
 * @param[in] str 要查找的字符串
 * @param[in] c 要查找的字符
 * @return NULL 未查找到
 * @return !NULL 查找到
 */
const char* libstr_find_char(const char*str, char c);

/**
 * 自字符串开头查找第一个非空字符
 * @param[in] str 要查找的字符串
 * 注意:空格被认为是非图形字符
 */
const char* libstr_find_graph_char(const char*str);

#endif //LIBSTR_H

