/**
 * @file xp_vector.h
 * @brief 动态数组
 * @author along
 * @date 2012-4-10
 */

#ifndef XP_VECTOR_H_
#define XP_VECTOR_H_

#include <string.h>
#include <stdint.h>

/**
 * 动态数组
 */
typedef struct xp_vector
{
	uint32_t length; //当前已使用长度(如果此长度为0，则当前数组为空）
	uint32_t capacity; //当前向量容量
	void** elements; //元素数组
} xp_vector_t;

/**
 * vector初始化值
 */
#define XP_VECTOR_INITIALIZER \
{\
    .length = 0,\
    .capacity = 0,\
    .elements = NULL\
}

/**
 * vector初始化函数
 * @param[in] xp_vector vector指针
 * @return 无
 */
#define XP_VECTOR_INIT_FUN(xp_vector) \
do\
{\
    (xp_vector)->length = 0;\
    (xp_vector)->capacity = 0;\
    (xp_vector)->elements = NULL;\
}while(0)

/**
 * 初始化xp_vector
 * @param[in] vector 要初始化的vector
 * @param[in] init_size vector的初始化大小
 * @return 0　初始化成功
 * @return !0 初始化失败
 */
static inline int32_t xp_vector_init(xp_vector_t*vector, uint32_t init_size)
{
	vector->length = 0;
	if (init_size != 0&& (vector->elements
			= (void**) LIB_MEM_ALLOC(sizeof(void*)*init_size)) != NULL){
	vector->capacity = init_size;
	return 0;
}

	LIB_ERROR(PLUGIN, "init vector error!");
	return -1;
}

static inline int32_t xp_vector_increase(xp_vector_t*vector, uint32_t capacity)
{
	void*element = NULL;
#if 0
	if (!(element = XP_REALLOC((void*)(vector->elements),capacity*sizeof(void*))))
	{
		//重分配失败
		LIB_ERROR(PLUGIN,"increase vector error!");
		return -1;
	}
#endif
	if (!(element = LIB_MEM_ALLOC(capacity * sizeof(void*))))
	{
		LIB_ERROR(PLUGIN, "increase vector error!");
		return -1;
	}

	if (vector->elements)
	{
		memcpy(element, (void*) (vector->elements),
				vector->capacity * sizeof(void*));
		LIB_MEM_FREE(vector->elements);
	}

	vector->elements = (void**) element;
	vector->capacity = capacity;
	return 0;
}
/**
 * 将elem指向的数据挂接在vector的未尾位置
 * @param[in] vector 要检查的vector
 * @param[in] elem   要比对的elem
 * @return 0　插入成功
 * @return !0 插入失败
 */
static inline int32_t xp_vector_append(xp_vector_t*vector, void*elem)
{
	if (!elem)
	{
		LIB_ERROR(PLUGIN, "vector can't append null element!\n");
		return -1;
	}

	if (vector->length + 1 >= vector->capacity)
	{
		uint32_t new_capacity = (vector->capacity) ? (2 * vector->capacity) : 2;
		while (new_capacity <= vector->length + 1)
		{
			new_capacity = 2 * new_capacity;
		}
		//如果将这个元素,加入,则将使得vector越界,因此扩容,
		if (xp_vector_increase(vector, new_capacity))
		{
			LIB_ERROR(PLUGIN, "increase vector error!");
			return -1;
		}
	}

	vector->elements[vector->length] = elem;
	vector->length++;
	//XP_LOG("append length = %d\n",vector->length);
	return 0;
}

/**
 * 弹出elem最后一个数据
 * @param[in] vector 要操作的vector
 * @param[out] elem  *elem不可为NULL,弹出的数据
 * @return 0 弹出成功
 * @return !0 弹出失败
 */
static inline int32_t xp_vector_pop(xp_vector_t*vector, void**elem)
{
	//XP_LOG("pop length = %d,*elem=%p\n",vector->length,*elem);
	if (!vector->length || !elem)
	{
		LIB_ERROR(PLUGIN, "elem is null or vector is empty!\n");
		return -1;
	}

	*elem = vector->elements[--vector->length];

	return 0;
}

/**
 * 返回elem最后一个数据
 * @param[in] vector 要操作的vector
 * @return NULL 返回失败
 * @return !NULL 返回成功
 */
static inline void* xp_vector_top(xp_vector_t*vector)
{
	if (!vector->length)
	{
		LIB_ERROR(PLUGIN, "vector is empty!\n");
		return NULL ;
	}

	return vector->elements[vector->length - 1];
}

/**
 * 压一个数据进栈
 * @param[in] vector 要操作的vector
 * @param[out] elem  压栈的数据
 * @return 0 压栈成功
 * @return !0 弹栈失败
 */
static inline int32_t xp_vector_push(xp_vector_t*vector, void*elem)
{
	return xp_vector_append(vector, elem);
}

/**
 * 检查vector中是否与elem相等的数据项
 * @param[in] vector 要检查的vector
 * @param[in] elem   要比对的elem
 * @param[in] cmp    比对函数 elem_in_vector 指vector中的元素,elem 指查找的元素
 * @return <０　没有找到相应数据项
 * @return >=0 找到数据项,且返回值为其对应下标
 */
static inline int32_t xp_vector_lookup(xp_vector_t*vector, const void*elem,
		int32_t (*cmp)(void*elem_in_vector, const void*elem))
{
	uint32_t i = 0;
	for (; i < vector->length; ++i)
	{
		if (cmp(vector->elements[i], elem) == 0)
		{
			return i;
		}
	}

	return -1;
}

/**
 * 检查vector中是否存在与elem相等的数据项,如果存在,则不插入,否则插入
 * @param[in] vector 要检查的vector
 * @param[in] elem   要比对的elem
 * @param[in] cmp    比对函数 [如果比对相等,返回０,否则比对不相等,返回!0]
 * @return 1 数据已存在
 * @return 0 数据插入成功
 * @return <0 数据插入失败
 */
static inline int32_t xp_vector_unique_insert(xp_vector_t*vector, void*elem,
		int32_t (*cmp)(void*a, const void*b))
{
	if (xp_vector_lookup(vector, elem, cmp) < 0)
	{
		return xp_vector_append(vector, elem);
	}

	return 1;
}

/**
 * 获得vector当前长度
 * @param[in] vector 要检查的vector
 * @return vector长度
 */
static inline uint32_t xp_vector_get_length(xp_vector_t*vector)
{
	return vector->length;
}

/**
 * 检查当前vector是否为空
 * @param[in] vector 要检查的vector
 * @return 0 不为空
 * @return !0 为空
 */
static inline int32_t xp_vector_is_empty(xp_vector_t*vector)
{
	return (xp_vector_get_length(vector) > 0) ? 0 : 1;
}

/**
 * 获取vector中第idx个元素
 * @param[in] vector 要获取的vector
 * @param[in] idx    元素索引
 * @return NULL 没有这个元素
 * @return !NULL 返回elements中存放的元素
 * 注意:此函数的实现意味着vector中不能存放NULL元素.
 */
static inline void* xp_vector_index_of(xp_vector_t*vector, uint32_t idx)
{
	if (idx < vector->length)
	{
		return vector->elements[idx];
	}

	return NULL ;
}

/**
 * vector遍历
 * @param[in] vector 要遍历的vector
 * @param[in] element_deal 处理函数,如果返回０表示处理成功,将继续处理,否则返回!0,则中止处理,返回返回值
 * @param[in] args  处理函数参数
 * @return 0 遍历成功
 * @return !0 处理时中止了处理,中止时的返回值
 */
static inline int32_t xp_vector_travel(xp_vector_t*vector,
		int32_t (*element_deal)(const void*elem, void*args), void*args)
{
	uint32_t i = 0;
	int32_t ret;
	for (; i < vector->length; ++i)
	{
		if ((ret = element_deal(vector->elements[i], args)))
		{
			return ret;
		}
	}

	return 0;
}

static inline void xp_vector_destroy(xp_vector_t*vector,
		void (*element_destroy)(void*elem, void*args), void*args)
{
	if (element_destroy)
	{
		uint32_t i = 0;
		for (; i < vector->length; ++i)
		{
			element_destroy(vector->elements[i], args);
		}
	}

	LIB_MEM_FREE((void*) (vector->elements));
}

static inline void xp_vector_clearall(xp_vector_t*vector,
		void (*element_destroy)(void*elem, void*args), void*args)
{
	xp_vector_destroy(vector, element_destroy, args);
	XP_VECTOR_INIT_FUN(vector);
}

static inline void xp_vector_sort(xp_vector_t*vector,
		int32_t (*element_sort)(void*elem_a, void*elem_b))
{
	uint32_t i;
	uint32_t j;
	for (i = 0; i < vector->length; ++i)
	{
		for (j = i + 1; j < vector->length; ++j)
		{
			int32_t ret = element_sort(vector->elements[i],
					vector->elements[j]);
			if (ret > 0)
			{
				void* tmp = vector->elements[i];
				vector->elements[i] = vector->elements[j];
				vector->elements[j] = tmp;
			}
		}
	}
}

#endif /* VECTOR_H_ */
