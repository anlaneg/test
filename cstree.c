
/**
 * 实现时注意:由于此数可能会存在太多节点,
 * 因此不能通过递归的方式进行遍历,而应采用
 * 非递归的方式进行增删改
 */
#define CSTREE_MAX_TREE_LENGTH (31ULL)

#define CSTREE_GET_KEY_POINTER(cstree_node,type)

typedef int32_t(*cstree_key_compare_fun)(void*tree_key,void*key);
typedef int32_t(*cstree_key_access_fun)(void*tree_key,void*args);

//如果需要支持节点遍历删除,则可使用此函数(不好支持)
typedef int32_t(*cstree_travel_fun)(cstree_node_t*node,void*args);

typedef struct cstree_node
{
	struct cstree_node* child;
	struct cstree_node* next_brother;
	struct cstree_node* prev_brother;
	struct cstree_node* parent; 
	char key[0];
}cstree_node_t;


typedef struct cstree
{
	cstree_node_t root;//根节点
	cstree_key_compare_fun key_compare;//key比对函数
	
	void* travel_stack;//遍历栈(其大小为node_count + sizeof(cstree_node))
	char name[CSTREE_MAX_TREE_LENGTH+1];//cstree名称
	uint32_t key_length;//key的大小
	uint32_t node_count; //树上的节点数目
}cstree_t;


int32_t cstree_build(cstree_t*tree,char name,cstree_key_compare_fun fun,uint32_t expect_max_count);

int32_t cstree_insert(cstree_t*tree,void*key);

int32_t cstree_lookup(cstree_t*tree,void*key);

int32_t cstree_delete(cstree_t*tree,void*key);

int32_t cstree_key_travel(cstree_t*tree,cstree_key_access_fun access,void*args);

