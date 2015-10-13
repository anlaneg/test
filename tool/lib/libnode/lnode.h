#ifndef LNODE_H
#define LNODE_H

typedef struct lnode_pool
{
	uint32_t item_size;
	uint32_t item_count;
	void*base;
	
}lnode_pool_t;

#endif
