/*
 * xp_syntax.h
 *
 *  Created on: Nov 25, 2013
 *      Author: along
 */

#ifndef XP_SYNTAX_H_
#define XP_SYNTAX_H_

#if 0
/**
 * tree 节点 id最大长度
 */
#define XP_PARSE_TREE_NODE_ID_MAX_SIZE (31ULL)
#endif


#define XP_SYNTAX_ITEM_MAX_PARENT_COUNT (32ULL)

#define XP_SYNTAX_TAG_ITEM_PARENT_LIST(...)\
{\
__VA_ARGS__ \
}
/**
 * syntax tag 初始化
 */
#define XP_SYNTAX_TAG_ITEM_INIT(tag_id,tag_parent_id_list,tag_name,tag_is_require,tag_entry_fun,tag_exit_fun)\
		{\
			.type=XP_TAG,\
			.id=tag_id,\
			.parent_id = tag_parent_id_list,\
			.name=tag_name,\
			.is_require=tag_is_require,\
			.tag={\
					.entry=tag_entry_fun,\
					.exit=tag_exit_fun,\
			}\
		}

/**
 * syntax attrbute 初始化
 */
#define XP_SYNTAX_ATTRIBUTE_ITEM_INIT(attr_id,attr_parent_id_list,attr_name,attr_is_require,attr_covert,attr_default_value)\
		{\
			.type=XP_ATTRIBUTE,\
			.id=attr_id,\
			.parent_id = attr_parent_id_list,\
			.name=attr_name,\
			.is_require=attr_is_require,\
			.attribute={\
					.default_attr_value=attr_default_value,\
					.convert=attr_covert,\
			},\
		}

/**
 * 用于施放用户自定义数据
 * ＠param[in] user_data 需要用户释放的数据
 * @return 0 成功
 * @return !0 失败
 */
typedef int32_t (*syntax_tree_node_user_data_free_fun)(void*user_data);

struct xp_syntax_item;
/**
 * 语法树节点
 */
typedef struct xp_syntax_tree_node
{
	struct xp_syntax_tree_node* parent;
	syntax_tree_node_user_data_free_fun free_user_data;
	void*user_data;
	xp_vector_t child;
	const struct xp_syntax_item* self_syntax;
	//char node_id[XP_PARSE_TREE_NODE_ID_MAX_SIZE + 1];
} xp_syntax_tree_node_t;

/**
 * 节点进入函数
 */
typedef int32_t (*xp_tag_entry_fun)(libxml_node_t*node,
		struct xp_syntax_tree_node*me);

/**
 * 节点离开函数
 */
typedef int32_t (*xp_tag_exit_fun)(libxml_node_t*node,
		struct xp_syntax_tree_node*me);

/**
 * 属性转换函数
 */
typedef int32_t (*xp_attr_convert_fun)(const char*attr_name,
		const char*attr_value, struct xp_syntax_tree_node*me);

/**
 * 语法项
 */
typedef struct xp_syntax_item
{
	enum
	{
		XP_TAG, XP_ATTRIBUTE,
	} type;
	uint32_t id;
	uint32_t parent_id[XP_SYNTAX_ITEM_MAX_PARENT_COUNT];//容许有多个父节点
	char* name;
	uint32_t is_require;
	union
	{
		struct
		{
			char* default_attr_value;
			xp_attr_convert_fun convert;
		} attribute;

		struct
		{
			xp_tag_entry_fun entry;
			xp_tag_exit_fun exit;
		} tag;
	};
} xp_syntax_item_t;

/**
 * 子项遍历函数回调
 * @param[in] item 语法项
 * @param[in] args 参数
 * @return 0 成功
 * @return !0 遍历失败
 */
typedef int32_t (*xp_syntax_child_item_travel_fun)(const xp_syntax_item_t*item,void*args);
/**
 * 添加语法项
 * @param[in] item 要添加的语法项
 * @return 0 添加成功
 * @return !0 添加失败
 */
int32_t xp_syntax_item_add(xp_syntax_item_t*item);

/**
 * 查找指定id的语法项
 * @param[in] id 要查找的id
 * @return NULL 查找失败
 * @return !NULL 查找成功
 */
xp_syntax_item_t* xp_syntax_item_lookfor(uint32_t id);

/**
 * 属性项查找
 * @param[in] parent 父语法项编号
 * @param[in] name 语法项名称
 * @return NULL 查找失败
 * @return !NULL 查找成功
 */
xp_syntax_item_t* xp_syntax_attribte_item_lookfor(uint32_t parent,
		const char*name);

/**
 * 标签语法项查找
 * @param[in] parent 父语法项编号
 * @param[in] name 语法项名称
 * @return NULL 查找失败
 * @return !NULL 查找成功
 */
xp_syntax_item_t* xp_syntax_tag_item_lookfor(uint32_t parent, const char*name);

/**
 * 语法项子属性遍历
 * @param[in] item 父语法项
 * @param[in] access 访问函数
 * @param[inout] args 访问参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t xp_syntax_child_attribute_item_travel(xp_syntax_item_t*item,
		xp_syntax_child_item_travel_fun access, void*args);

/**
 * 语法项子属性遍历
 * @param[in] item 父语法项
 * @param[in] access 访问函数
 * @param[inout] args 访问参数
 * @return 0 遍历成功
 * @return !0 遍历失败
 */
int32_t xp_syntax_child_attribute_item_travel(xp_syntax_item_t*item,
		xp_syntax_child_item_travel_fun access, void*args);

/**
 * 语法检查
 * @param[in] node 要检查的节点
 * @param[in] parent_id 父节点id
 * @return 0 检查通过
 * @return !0 检查失败
 * @注意：此函数要求parent_id 一定存在于语法项中
 */
int32_t xp_syntax_check(libxml_node_t*node, uint32_t parent_id);

/**
 * 获取syntax item根
 * @return NULL 返回失败
 * @return !NULL 返回成功
 */
xp_syntax_item_t* xp_syntax_item_get_root_item();
/**
 * 获取syntax tree根节点
 * @return NULL 返回失败
 * @return !NULL 返回成功
 */
xp_syntax_tree_node_t* xp_syntax_tree_get_root_node();

/**
 * 获取syntax tree 父节点
 * @param[in] node 节点
 * @return NULL 无父节点
 * @return !NULL 有父节点
 */
static inline xp_syntax_tree_node_t* xp_syntax_tree_get_parent_node(
		xp_syntax_tree_node_t* node)
{
	assert(node);
	return node->parent;
}

/**
 * 检查所给节点是否为父节点
 * @param[in] node 节点
 * @return 0 不是
 * @return !0 是
 */
static inline int32_t xp_syntax_tree_is_root_node(xp_syntax_tree_node_t*node)
{
	assert(node);
	if (node->parent || node != xp_syntax_tree_get_root_node())
	{
		return 0;
	}
	return 1;
}

/**
 * 获取父节点最后一个子节点
 * @param[in] parent 父节点
 * @return !NULL 最后一个子节点
 * @return NULL 无子节点
 */
static inline xp_syntax_tree_node_t* xp_syntax_tree_get_last_child(
		xp_syntax_tree_node_t*parent)
{
	return (xp_syntax_tree_node_t*) xp_vector_top(&parent->child);
}

/**
 * 构造语法树
 * @param[in] root xml根节点
 * @param[in] parent_id 父节点
 * @return 解释的数据
 */
void* xp_syntax_build_tree(libxml_node_t*root, uint32_t parent_id);

/**
 * 语法项初始化
 * @param[in] size 大小
 * @param[in] array 语法项数组
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t xp_syntax_init(int32_t size, xp_syntax_item_t*array);

/**
 * 用户数据默认释放函数
 */
int32_t xp_syntax_tree_node_user_data_default_free(void*user_data);
#endif /* XP_SYNTAX_H_ */
