
typedef struct ac_node
{
	struct ac_node_input
	{
		struct ac_node* next_node;
		struct ac_node_input*next;
		char input;
		#define TERMINAL 0x1
		#define CONTINUE 0x2
		char flag;
		char unuse[3];
	}table;
	struct ac_node* fail_node;
}ac_node_t;

typedef struct ac_tree
{
	ac_node_t root;
	int use;
	int alloc;
}ac_tree_t;

ac_node_t* ac_tree_node_create();
void ac_tree_node_destroy(ac_node_t*);
ac_node_t* ac_tree_node_find(ac_node_t*parent,char input);
int ac_tree_node_append(find,&word[i])
{
	//add node 
	//set fail;
}

int ac_tree_insert_word(ac_tree_t* tree,char*word)
{
	ac_node_t* find = &(tree->root)
	for(int i = 0 ; i < strlen(word);++i)
	{
		ac_node_t* temp = ac_tree_node_find(find,word[i]);
		if(temp == NULL)
		{
		   return ac_tree_node_append(find,&word[i]);
		}
		else
		{
		   find = temp->next_node; 
		}
	}
	
	if(find->flag != TERMINAL)
	{
		find->flag = TERMINAL;
	}
	return 0;
}
int ac_tree_delete_word(ac_tree_t* tree,char*word)
{
	//0.一般不建意提供
	//3.如果别人与删除项有相交,则相交部分不能删除(3种情况,子串,是其它的子串,和其它有前缀相交)
	//4.删除后,全树中fail值相关者均要修改(1,指向删除结点的)
}

//
int ac_tree_create(ac_tree_t*tree,int limit_count);
int ac_tree_destroy(ac_tree_t*tree);
char* ac_tree_match(ac_tree_t*tree,char*word);
