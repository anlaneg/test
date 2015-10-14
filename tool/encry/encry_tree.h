#ifndef ENCRY_NODE_H
#define  ENCRY_NODE_H

#include <stdint.h>

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

int encry_tree_insert(encry_node_t * root,int8_t* data,uint32_t len);

int encry_tree_delete(encry_node_t* root,int8_t* data,uint32_t len);

typedef int (*encry_tree_traversal_fun)(encry_node_t*,void*argv);

int encry_tree_traversal(encry_node_t* root,enum traversal_mode mode,encry_tree_traversal_fun fun,void*argv);

#endif
