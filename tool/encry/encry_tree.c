
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

static inline encry_tree_brother_lookfor(encry_node_t*root,int8_t data)
{
}


int encry_tree_insert(encry_node_t * root,int8_t* data,uint32_t len)
{
	assert(root);
	assert(data);
	
	uint32_t i ;
	encry_node_t*self = NULL;
	for(i = 0 ; i < len; ++i)
	{
		self = encry_tree_brother_lookfor(root->child,data[i]);
		if(self)
		{
			continue;
		}

		break;
	}
	
	if(i < len)
	{
		self = encry_tree_build_child_list(self,data,i,len)
		if(!self)
		{
			return -1;//alloc node fail
		}
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

