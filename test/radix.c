#define <stdint.h>
#define <sys/queue.h>

#define RADIX_NODE_MAX_MASK_LENGTH (1UL)
#define RADIX_NODE_MASK_SIZE (sizeof(int32_t)*8UL)
#if RADIX_NODE_MAX_MASK_LENGTH > 63
#error "no support RADIX_NODE_MAX_MASK_LENGTH bigger than 63"
#endif

#define RADIX_NODE_MAX_CHILDREN_COUNT (1UL << (RADIX_NODE_MAX_MASK_LENGTH))

typedef struct radix_node
{
	struct radix_node*parent;
	struct radix_node* child[RADIX_NODE_MAX_CHILDREN_COUNT];
	int32_t offset;

	int32_t ip; 
	int32_t mask;
}radix_node_t;

static inline radix_node_t * radix_node_alloc()
{
	
}

static inline void radix_node_free(radix_node_t*node)
{
}

static inline int32_t radix_node_insert(radix_node_t*root,void*addr)
{
}

static inline int32_t radix_node_delete(radix_node_t*root,void*addr)
{
}

static inline uint32_t radix_node_child_idx(int32_t offset)
{
	uint32_t mask = ((~0UL) >> offset) & ((~0UL) << RADIX_NODE_MASK_SIZE - offset - RADIX_NODE_MAX_MASK_LENGTH );
	return mask;
}
static inline radix_node_t* radix_node_find(radix_node*root,int32_t ip)
{
	assert(root);
	if(root->offset)
	{
		uint32_t idx = radix_node_child_idx(root->offset,ip);
		assert(idx >= 0 && idx < RADIX_NODE_MAX_CHILDREN_COUNT);
		if(root->children[idx])
		{
		    return radix_node_child_idx(root->children[idx],ip);		
		}
	}	
	//leaf
	if((root->ip & mask) == (ip & mask))
	{
		return root;
	}
	//向父节点退
		
	return NULL;
}
