
typedef struct gen_workspace
{
	lib_hash_t* cfg_hash;
	gen_buffer_t* in_buffer;
	gen_buffer_t* out_buffer;
}gen_workspace_t;

int32_t gen_workspace_init(gen_workspace_t* workdspace,gen_args_t*args);
int32_t gen_workspace_destory(gen_workspace_t*workspace);


static int32_t workspace_load_variable(gen_workspace_t*workspace,gen_args_t* args);

static int32_t workspace_parse_tmplate_file(gen_workspace_t*workspace,gen_args_t*args);


int main(int argc,char**argv)
{
	sf_int32_t ret =-1;
	gen_args_t args;	
	gen_workspace_t workspace;
	
	//0.do args init
	if(gen_args_init(&args))
	{
		//TODO
	}

	//1.parse argv
	if((ret=gen_args_parse(&args,argc,argv)))
	{
		gen_args_destroy(&args);
		exit(ret)
	}

	//2.do workdspace init
	if(gen_workspace_init(&workspace,&args))
	{
	}

	//3.build variable hashtable
	if(workspace_load_variable(&workspace,&args))
	{
	}

	//4.template file process
	if(workspace_parse_tmplate_file(&workspace,&args))
	{
	}

	return 0;
}
