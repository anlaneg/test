
typedef uint32_t (*lib_hashcode_fun)(void*key);
//>0 , == 0 , < 0
typedef int32_t (*lib_hashcompare_fun)(void*find,void*hash_store);
typedef int32_t (*lib_hashelem_destroy_fun)(void*key,void*value);
typedef void* (*lib_hash_alloc_fun)(uint32_t size);
typedef void (lib_hash_free_fun)(void*);

typedef struct lib_hash_elem
{
	void*key;
	void*value;
	struct lib_hash_elem*next;
}lib_hash_elem_t;

typedef struct lib_hash_args
{
	lib_hashcode_fun hashcode;
	lib_hashcompare_fun compare;
	lib_hashelem_destroy_fun elem_destroy;
	lib_hash_alloc_fun alloc;
	lib_hash_free_fun free;
	uint32_t size;
}lib_hash_args_t;

typedef struct lib_hash
{
	lib_hash_elem_t* bucket;
	lib_hash_args_t args;
}lib_hash_t

int32_t lib_hash_init(lib_hash_t*hash,lib_hash_args_t* hash);
int32_t lib_hash_insert(lib_hash_t*hash,void*key,void*value);
void* lib_hash_lookfor(lib_hash_t*hash,void*key);
void* lib_hash_delete(lib_hash_t*hash,void*key);
void* lib_hash_destroy(lib_hash_t*hash);
