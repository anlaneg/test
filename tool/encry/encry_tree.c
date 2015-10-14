
#include <stdint.h>
#include "encry_node.h"
#include "node_mg.h"

#if 0
typedef struct encry_node
{
	struct encry_node *parent;
	struct encry_node *child;
	struct encry_node *brother;
	uint32_t priority;
	int8_t  character;
}encry_node_t;


enum traversal_mode
{
	PRIORITY_FIRST=1,
	
};
#endif



node_pool_t* g_encry_node_pool = NULL;

encry_node_t* encry_node_alloc()
{
	if(g_encry_node_pool == NULL)
	{
		node_cfg_t cfg={
			.size=sizeof(encry_node_t);
			.count=(4096/sizeof(encry_node_t));
		};
		g_encry_node_pool=node_pool_init(&cfg);
	}
	
	return node_pool_alloc_node(g_encry_node_pool);
}

void encry_node_free(encry_node_t*node)
{
	if(node != NULL)
	{
		assert(g_encry_node_pool);
		node_pool_free_node(g_encry_node_pool,node);
	}
}

static inline encry_node_t* encry_tree_brother_lookfor(encry_node_t*head,int8_t data)
{
	encry_node_t* node = head;	
	while(node)
	{
		if(node->character == data)
		{	
			return node;
		}

		node = node->brother;
	}
	return NULL;
}

static inline void encry_node_init_child(encry_node_t* self, int8_t data, encry_node_t* child_list)
{
	self->parent = NULL;
	self->child = child_list;
	child_list->parent = self;
	self->brother = NULL;
	node->priority = 0;
	node->character = data;
}

static inline void encry_node_set_parent(encry_node_t* self, encry_node_t* parent)
{
	self->parent = parent;
	self->brother = parent->child;
	parent->child = self;
}

static inline encry_node_t* encry_tree_build_child_list(encry_node_t*parent,int8_t*data,uint32_t offset,uint32_t len)
{
	assert(offset < len)

	
	uint32_t i ;
	encry_node_t* child_list = NULL;

	for(i = len - 1; i >= offset; i--)
	{
		encry_node_t* temp = encry_node_alloc();
		if(!temp)
		{
			goto FREE;
		}
		encry_node_init_child(temp,data[i],child_list);
		child_list = temp;
	}

	encry_node_set_parent(child_list,parent);
	return child_list;
	
	FREE:
	{
		while(child_list)
		{
			encry_node_t* temp = child_list;
			child_list->child = temp->child;
			encry_node_free(temp);
		}
		return NULL;
	}
}

static inline int encry_tree_increase_priority_goback(encry_node_t* leaf)
{
	assert(leaf);

	do
	{
		leaf->priority +=1;
		leaf=leaf->parent;
	}while(leaf);
}

int encry_tree_insert(encry_node_t* root,int8_t* data,uint32_t len)
{
	assert(root);
	assert(data);
	
	uint32_t i ;
	encry_node_t* self  = NULL;
	encry_node_t*parent = root;
	for(i = 0 ; i < len; ++i)
	{
		self = encry_tree_brother_lookfor(parent->child, data[i]);
		if(self)
		{
			parent = self;
			continue;
		}

		self = encry_tree_build_child_list(parent,data,i,len);
		if(!self)
		{
			return -1;//alloc node fail
		}
		break;
	}
	
	//if len == 0 ,self is NULL
	if(self)
	{
		encry_tree_increase_priority_goback(self);
	}

	return 0;
}

int encry_tree_delete(encry_node_t* root,int8_t* data,uint32_t len);

int encry_tree_traversal(encry_node_t* root,enum traversal_mode mode,int (*traversal_function)(encry_node_t*node,void*argv),void*argv);

