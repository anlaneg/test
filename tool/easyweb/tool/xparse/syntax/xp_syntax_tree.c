/*
 * xp_syntax_tree.c
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

static xp_syntax_item_t s_syntax_item_root = XP_SYNTAX_TAG_ITEM_INIT(1,XP_SYNTAX_TAG_ITEM_PARENT_LIST(1),"root",0,(xp_tag_entry_fun)1,(xp_tag_exit_fun)1);
/**
 * 语法树根节点
 */
static xp_syntax_tree_node_t s_syntax_tree_root =
	{ .self_syntax=&s_syntax_item_root, .parent = NULL, .child = XP_VECTOR_INITIALIZER,
			.user_data = NULL ,

	};

struct syntax_attr_convert_param
{
	xp_syntax_item_t*parent_syntax;
	struct xp_syntax_tree_node*self;
};

static int32_t syntax_build_subtree_inner(libxml_node_t*child_xml_node,
		xp_syntax_tree_node_t*parent_syntax_tree_node,
		xp_syntax_item_t*parent_syntax_item);

/**
 * 获取syntax item根
 * @return NULL 返回失败
 * @return !NULL 返回成功
 */
xp_syntax_item_t* xp_syntax_item_get_root_item()
{
	return &s_syntax_item_root;
}
/**
 * 获取syntax tree根节点
 * @return NULL 返回失败
 * @return !NULL 返回成功
 */
xp_syntax_tree_node_t* xp_syntax_tree_get_root_node()
{
	return &s_syntax_tree_root;
}

/**
 * 创建新的子节点
 * @param[in] parent 父节点
 * @param[in] node_id 节点id
 * @param[in] user_data
 * @return 0 插入成功
 * @return !0 插入失败
 */
static inline xp_syntax_tree_node_t* syntax_tree_node_create(
		xp_syntax_tree_node_t*parent, const xp_syntax_item_t*syntax_item,
		void*user_data)
{
	assert(parent);
	assert(syntax_item);

	xp_syntax_tree_node_t*node =
			(xp_syntax_tree_node_t*) LIB_MEM_ALLOC(sizeof(xp_syntax_tree_node_t));
	if (!node)
	{
		LIB_ERROR(SYNTAX_TREE, "alloc syntax tree node fail!\n");
		return NULL ;
	}

	//strncpy(node->node_id, node_id, XP_PARSE_TREE_NODE_ID_MAX_SIZE);
	//node->node_id[XP_PARSE_TREE_NODE_ID_MAX_SIZE] = '\0';
	node->self_syntax = syntax_item;
	XP_VECTOR_INIT_FUN(&(node->child));
	node->parent = parent;
	node->user_data = user_data;

	return node;
}

static void syntax_tree_node_destroy_inner(xp_syntax_tree_node_t*node,
		void*un_use)
{
	if (xp_vector_get_length(&node->child))
	{
		xp_vector_destroy(&node->child,
				(void (*)(void*, void*)) syntax_tree_node_destroy_inner, NULL );
	}
	if (node->user_data)
	{
		if (node->free_user_data && node->free_user_data(node->user_data))
		{
			LIB_ERROR(SYNTAX_TREE, "node '%s' free user data fail!\n",
					node->self_syntax->name);
		}
		else
		{
			LIB_ERROR(SYNTAX_TREE,
					"node '%s' have user data,but no register free function !\n",
					node->self_syntax->name);
		}
	}
	LIB_MEM_FREE(node);
}
/**
 * 销毁syntax tree node
 * @param[in] node 节点
 * @return 0 销毁成功
 * @return !0 销毁失败
 */
static inline void syntax_tree_node_destroy(xp_syntax_tree_node_t*node)
{
	syntax_tree_node_destroy_inner(node, NULL );
}
/**
 * 创建并插入新的子节点
 * @param[in] parent 父节点
 * @param[in] node_id 节点id
 * @param[in] user_data
 * @return 0 插入成功
 * @return !0 插入失败
 */
static inline int32_t xp_syntax_tree_insert_child_node(
		xp_syntax_tree_node_t*parent, const xp_syntax_item_t*syntax_item,
		void*user_data)
{
	xp_syntax_tree_node_t*node = syntax_tree_node_create(parent, syntax_item,
			user_data);

	if (xp_vector_push(&parent->child, node))
	{
		LIB_ERROR(SYNTAX_TREE,
				"push child node '%s' to parent node '%s' fail!\n",
				node->self_syntax->name, parent->self_syntax->name);
		LIB_MEM_FREE(node);
		return -1;
	}

	return 0;
}

static inline int32_t syntax_tree_delete_last_child(
		xp_syntax_tree_node_t*parent)
{
	xp_syntax_tree_node_t* last_child = NULL;
	xp_vector_pop(&parent->child, (void**) &last_child);
	if (!last_child)
	{
		LIB_ERROR(SYNTAX_TREE, "syntax delete last child fail!\n");
		return -1;
	}

	syntax_tree_node_destroy(last_child);
	return 0;
}

/**
 * node 属性检查函数
 * @param[in] attr_name 属性名
 * @param[in] attr_value 属性值
 * @param[in] args 参数
 * @return 0 访问成功
 * @return !0 访问失败
 */
static int32_t syntax_attribute_covert(const char*attr_name,
		const char*attr_value, void*args)
{
	assert(attr_name);
	assert(attr_value);
	assert(args);

	struct syntax_attr_convert_param*param =
			(struct syntax_attr_convert_param*) args;
	assert(param->parent_syntax);
	assert(param->self);

	xp_syntax_item_t* parent_syntax = param->parent_syntax;
	struct xp_syntax_tree_node*self = param->self;
	xp_syntax_item_t* attr_syntax;
	if (!(attr_syntax = xp_syntax_attribte_item_lookfor(parent_syntax->id,
			attr_name)))
	{
		LIB_ERROR(SYNTAX_TREE, "attribute node:'%s' unkown,parent is '%s'!\n",
				attr_name, parent_syntax->name);
		return -1;
	}

	if (attr_syntax->attribute.convert(attr_name, attr_value, self))
	{
		LIB_ERROR(SYNTAX_TREE, "attribute node:'%s' value:'%s' convert fail!\n",
				attr_name, attr_value);
		return -1;
	}
	return 0;
}

static int32_t syntax_build_tree_inner(libxml_node_t*parent_xml_node,
		xp_syntax_tree_node_t*parent_syntax_tree_node,
		xp_syntax_item_t*parent_syntax_item)
{
	libxml_node_t*child_xml_node;
#if 0
	xp_syntax_item_t*child_syntax_item;
	const char*node_name = libxml_node_name_get(parent_xml_node);

	if (!(child_syntax_item = xp_syntax_tag_item_lookfor(parent_syntax_item->id, node_name)))
	{

		LIB_ERROR(SYNTAX_CHECK,
				"syntax-error:tag node:'%s' unkown,parent is '%s'!\n",
				node_name, parent_syntax_item->name);
		return -1;
	}
#endif
	struct syntax_attr_convert_param param;
	param.parent_syntax = parent_syntax_item;
	param.self = parent_syntax_tree_node;
	if (libxml_node_attribute_travel(parent_xml_node, syntax_attribute_covert,
			&param))
	{
		return -1;
	}

	if ((child_xml_node = libxml_node_child_get(parent_xml_node)))
	{
		//有子节点，需要先访问子节点，回头上来再上来访问兄弟节点
		if (syntax_build_subtree_inner(child_xml_node, parent_syntax_tree_node,
				parent_syntax_item))
		{
			return -1;
		}
	}

	//首个兄弟的子节点已访问，现在访问兄弟节点
	if (child_xml_node)
	{
		libxml_node_t*brother_xml_node;
		for (brother_xml_node = libxml_node_brother_get(child_xml_node);
				brother_xml_node;
				brother_xml_node = libxml_node_brother_get(brother_xml_node))
		{
			//有子节点，需要先访问子节点，回头上来再上来访问兄弟节点
			if (syntax_build_subtree_inner(brother_xml_node,
					parent_syntax_tree_node, parent_syntax_item))
			{
				return -1;
			}
		}
	}

	return 0;
}

static int32_t syntax_build_subtree_inner(libxml_node_t*child_xml_node,
		xp_syntax_tree_node_t*parent_syntax_tree_node,
		xp_syntax_item_t*parent_syntax_item)
{
	//1.create new tree node
	xp_syntax_tree_node_t* child_syntax_tree_node;
	xp_syntax_item_t* child_syntax_item;
	assert(child_xml_node);
	const char* child_xml_node_name = libxml_node_name_get(child_xml_node);
	//1.1 get child syntax_item
	if (!(child_syntax_item = xp_syntax_tag_item_lookfor(parent_syntax_item->id,
			child_xml_node_name)))
	{

		LIB_ERROR(SYNTAX_TREE, "tag node:'%s' unkown,parent is '%s'!\n",
				child_xml_node_name, parent_syntax_item->name);
		//syntax_tree_node_destroy(child_syntax_tree_node);
		return -1;
	}
	//1.2 create syntax tree node
	if (xp_syntax_tree_insert_child_node(parent_syntax_tree_node,
			(const xp_syntax_item_t*) child_syntax_item, NULL ))
	{
		LIB_ERROR(SYNTAX_TREE, "syntax tree create new node fail!\n");
		return -1;
	}
	child_syntax_tree_node = xp_syntax_tree_get_last_child(
			parent_syntax_tree_node);
	assert(child_syntax_tree_node);

	//2.trigger entry

	if (child_syntax_item->tag.entry(child_xml_node, child_syntax_tree_node))
	{
		LIB_ERROR(SYNTAX_TREE, "trigger tag node :'%s' entry function fail!\n",
				child_xml_node_name);
		syntax_tree_node_destroy(child_syntax_tree_node);
		return -1;
	}

	//3.process child node
	if (syntax_build_tree_inner(child_xml_node, child_syntax_tree_node,
			child_syntax_item))
	{
		syntax_tree_node_destroy(child_syntax_tree_node);
		return -1;
	}

	//4.trigger exit
	if (child_syntax_item->tag.exit(child_xml_node, child_syntax_tree_node))
	{
		LIB_ERROR(SYNTAX_TREE, "trigger tag node :'%s' exit function fail!\n",
				child_xml_node_name);
		syntax_tree_node_destroy(child_syntax_tree_node);
		return -1;
	}

	return 0;
}

/**
 * 构造语法树
 * @param[in] root xml根节点
 * @param[in] parent_id 父节点
 * @return 解释的数据
 */
void* xp_syntax_build_tree(libxml_node_t*root, uint32_t parent_id)
{
	xp_syntax_item_t* parent = xp_syntax_item_lookfor(parent_id);
	if (!parent)
	{
		LIB_ERROR(SYNTAX_TREE, "we can not find syntax item by id '%d'!\n",
				parent_id);
		return NULL ;
	}
	if (syntax_build_subtree_inner(root, xp_syntax_tree_get_root_node(),
			parent))
	{
		LIB_ERROR(SYNTAX_TREE, "build tree fail!\n");
		return NULL ;
	}

	return xp_syntax_tree_get_root_node()->user_data;
}

/**
 * 用户数据默认释放函数
 */
int32_t xp_syntax_tree_node_user_data_default_free(void*user_data)
{
	LIB_MEM_FREE(user_data);
	return 0;
}
