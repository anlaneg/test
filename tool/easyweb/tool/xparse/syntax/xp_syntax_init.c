/*
 * xp_syntax_init.c
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "libmem.h"
#include "libxml.h"
#include "xp_debug.h"
#include "xp_vector.h"
#include "xp_syntax.h"

/**
 * 语法项初始化
 * @param[in] size 大小
 * @param[in] array 语法项数组
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t xp_syntax_init(int32_t size, xp_syntax_item_t*array)
{
	assert(array);
	int32_t i;
	for (i = 0; i < size; ++i)
	{
		if (xp_syntax_item_add(&array[i]))
		{
			LIB_ERROR(SYNTAX, "add syntax item %s:'%s' fail!\n",
					array[i].type == XP_TAG ? "tag" : "attribute",
					array[i].name);
			return -1;
		}
	}

	//XXX 是否有必要在此处添加校验，用于检查子节点存在，但父节点不存在情况？
	return 0;
}
