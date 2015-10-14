
typedef struct node_cfg
{
	uint32_t size;
	uint32_t count;
}node_cfg_t;

typedef struct node_pool
{
	node_cfg_t cfg;
	struct node_pool* next;
	void*base;
	uint32_t*node_mg;
	uint32_t free_count;
}node_pool_t;



node_pool_t* node_pool_init(node_cfg_t*cfg);

void node_pool_destrory(node_pool_t*pool);

void* node_pool_alloc_node(node_pool_t*pool);

void node_pool_free_node(node_pool_t*pool,void*);


