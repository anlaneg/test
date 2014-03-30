#include <stdint.h>

typedef struct full_tree_node
{
	int data;
	struct full_tree_node* left;
	struct full_tree_node* right;
	struct full_tree_node* parent;
}full_tree_node_t;

int32_t full_tree_node_insert(full_tree_node_t* tree,full_tree_node_t*node)
{
	assert(tree);
	struct full_tree_node* root = tree->left;
	while(root)
	{
		if(root->data > node->data)
		{
			if(!root->left)
			{
				//root->left == null && root->right=node
				//do node->left = root && root->parent->??=node;

			}
			if(!root->right)
			{
				root->right = node;
				node->parent = root;
				return ;
			}

			assert(root->right);
			root= root->right;
			continue;
		}
		else if(root->data < node->data)
		{
			if(	
		}
		else
		{
			//已存在
			return 1;
		}

	}
}
