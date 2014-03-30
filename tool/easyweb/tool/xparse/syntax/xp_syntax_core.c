/*
 * xp_syntax_core.c
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

#include "libmem.h"
#include "libxml.h"
#include "xp_debug.h"
#include "xp_vector.h"
#include "xp_syntax.h"

static xp_vector_t s_syntax_item_array = XP_VECTOR_INITIALIZER;

static int32_t syntax_item_find_by_id(xp_syntax_item_t*elem,
		const void*args_elem)
{
	uint32_t*id = (uint32_t*) args_elem;
	assert(id);

	if (elem->id == *id)
	{
		return 0;
	}
	return 1;
}

struct typeparam_find
{
	const char* name;
	int32_t type;
	uint32_t parent_id;
};

struct child_travel_param
{
	uint32_t type;
	uint32_t parent_id;
	xp_syntax_child_item_travel_fun travel_fun;
	void*args;
};

static int32_t syntax_item_find_by_typeparam(xp_syntax_item_t*elem,
		const void*args_elem)
{
	struct typeparam_find* finder = (struct typeparam_find*) args_elem;
	assert(finder);

	if (elem->type == finder->type && !strcmp(elem->name, finder->name))
	{
		uint32_t idx;
		for (idx = 0; idx < XP_SYNTAX_ITEM_MAX_PARENT_COUNT //
		&& elem->parent_id[idx]; ++idx)
		{
			if (finder->parent_id == elem->parent_id[idx])
			{
				return 0;
			}
		}
	}

	return 1;
}

static int32_t syntax_item_repeat_check(const xp_syntax_item_t*elem,
		xp_syntax_item_t*args)
{
	//不能含用重复的id
	if (elem->id == args->id)
	{
		return -1;
	}

	//同一父节点不能有相同名称的同一类型子节点
	if (elem->type == args->type && !strcmp(elem->name, args->name))
	{
		uint32_t idx;
		for (idx = 0; idx < XP_SYNTAX_ITEM_MAX_PARENT_COUNT //
		&& elem->parent_id[idx]; ++idx)
		{
			uint32_t j;
			for (j = 0; j < XP_SYNTAX_ITEM_MAX_PARENT_COUNT //
			&& args->parent_id[j]; ++j)
			{
				if (args->parent_id[j] == elem->parent_id[idx])
				{
					return -1;
				}
			}
		}
	}

	return 0;
}

static int32_t syntax_item_validation(xp_syntax_item_t*item)
{
	if (!item)
	{
		LIB_ERROR(SYNTAX, "synatx item must no-null!\n");
		return -1;
	}

	if (!item->id)
	{
		LIB_ERROR(SYNTAX, "syntax item must bigger than zero!\n");
		return -1;
	}

	if (!item->name || !strlen(item->name))
	{
		LIB_ERROR(SYNTAX,
				"syntax item must have name and must strlen bigger than zero!\n");
		return -1;
	}

	if (item->type == XP_ATTRIBUTE && !item->attribute.convert)
	{
		LIB_ERROR(SYNTAX,
				"syntax attribute item convert function must no-null!\n");
		return -1;
	}

	if (!item->is_require && item->type == XP_ATTRIBUTE
			&& !item->attribute.default_attr_value)
	{
		LIB_ERROR(SYNTAX,
				"syntax attribute item '%s' is no-require,but we not find default value!\n",
				item->name);
		return -1;
	}

	if (item->type == XP_TAG && (!item->tag.entry || !item->tag.exit))
	{
		LIB_ERROR(SYNTAX,
				"syntax tag item '%s' must have entry and exit function!\n",
				item->name);
		return -1;
	}

	return 0;
}

/**
 * 添加语法项
 * @param[in] item 要添加的语法项
 * @return 0 添加成功
 * @return !0 添加失败
 */
int32_t xp_syntax_item_add(xp_syntax_item_t*item)
{
	if (syntax_item_validation(item))
	{
		LIB_ERROR(SYNTAX, "syntax item validataion fail!!\n");
		return -1;
	}

	if (xp_vector_travel(&s_syntax_item_array,
			(int32_t (*)(const void*, void*)) syntax_item_repeat_check, item))
	{
		LIB_ERROR(SYNTAX, "syntax item '%s' is repeat!\n", item->name);
		return -1;
	}

	return xp_vector_append(&s_syntax_item_array, item);
}

/**
 * 查找指定id的语法项
 * @param[in] id 要查找的id
 * @return NULL 查找失败
 * @return !NULL 查找成功
 */
xp_syntax_item_t* xp_syntax_item_lookfor(uint32_t id)
{
	int32_t idx;
	if ((idx = xp_vector_lookup(&s_syntax_item_array, &id,
			(int32_t (*)(void*, const void*)) syntax_item_find_by_id)) < 0)
	{
		return NULL ;
	}

	return xp_vector_index_of(&s_syntax_item_array, idx);
}

/**
 * 属性项查找
 * @param[in] parent 父语法项编号
 * @param[in] name 语法项名称
 * @return NULL 查找失败
 * @return !NULL 查找成功
 */
xp_syntax_item_t* xp_syntax_attribte_item_lookfor(uint32_t parent,
		const char*name)
{
	const struct typeparam_find finder =
		{ .name = name, .type = XP_ATTRIBUTE, .parent_id = parent, };

	int32_t idx;
	if ((idx = xp_vector_lookup(&s_syntax_item_array, &finder,
			(int32_t (*)(void*, const void*)) syntax_item_find_by_typeparam))
			< 0)
	{
		return NULL ;
	}

	return xp_vector_index_of(&s_syntax_item_array, idx);
}

/**
 * 标签语法项查找
 * @param[in] parent 父语法项编号
 * @param[in] name 语法项名称
 * @return NULL 查找失败
 * @return !NULL 查找成功
 */
xp_syntax_item_t* xp_syntax_tag_item_lookfor(uint32_t parent, const char*name)
{
	const struct typeparam_find finder =
		{ .name = name, .type = XP_TAG, .parent_id = parent, };

	int32_t idx;
	if ((idx = xp_vector_lookup(&s_syntax_item_array, &finder,
			(int32_t (*)(void*, const void*)) syntax_item_find_by_typeparam))
			< 0)
	{
		return NULL ;
	}

	return xp_vector_index_of(&s_syntax_item_array, idx);
}

static int32_t syntax_item_child_attribute_travel(const xp_syntax_item_t*item,
		void*args)
{
	struct child_travel_param *finder = (struct child_travel_param*) args;
	if (item->type == finder->type)
	{
		uint32_t idx;
		for (idx = 0; idx < XP_SYNTAX_ITEM_MAX_PARENT_COUNT //
		&& item->parent_id[idx]; ++idx)
		{
			if (finder->parent_id == item->parent_id[idx])
			{
				return finder->travel_fun(item, finder->args);
			}
		}
	}
	return 0;
}

/**
 * 语法项子属性遍历
 * @param[in] item 父语法项
 * @param[in] access 访问函数
 * @param[inout] args 访问参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t xp_syntax_child_attribute_item_travel(xp_syntax_item_t*item,
		xp_syntax_child_item_travel_fun access, void*args)
{
	struct child_travel_param param =
		{ .type = XP_ATTRIBUTE, .travel_fun = access, .args = args, .parent_id =
				item->id, };
	return xp_vector_travel(&s_syntax_item_array,
			(int32_t (*)(const void*, void*)) syntax_item_child_attribute_travel,
			&param);
}

/**
 * 语法项子标签遍历
 * @param[in] item 父语法项
 * @param[in] access 访问函数
 * @param[inout] args 访问参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t xp_syntax_child_tag_item_travel(xp_syntax_item_t*item,
		xp_syntax_child_item_travel_fun access, void*args)
{
	struct child_travel_param param =
		{ .type = XP_TAG, .travel_fun = access, .args = args, .parent_id =
				item->id, };
	return xp_vector_travel(&s_syntax_item_array,
			(int32_t (*)(const void*, void*)) syntax_item_child_attribute_travel,
			&param);
}

int32_t xp_syntax_item_delete(xp_syntax_item_t* item)
{
	return -1;
}
