
typedef struct gen_cfg_item
{
	char*name;
	char*value;
}gen_cfg_item_t;

int32_t gen_cfg_parse(FILE*file,gen_cfg_item_t* item_tbl,uint32_t max_size);
