
typedef gen_args
{
	lib_hash_args_t hash_args;
	lib_hash_t var_hash;
	char* my_name;
	char* cfg_file_path;
	char* tmplate_file_path;
	char* output_file_path;
	char* split_char;
	char* escape_char;
	int32_t debug_level;
	int32_t is_need_show_help;
	int32_t is_need_show_version;
	int32_t global_buffer_size;
	gen_output_fun ouput_fun;
}gen_args_t;

static void show_version();
static void show_help();
static int32_t args_validate();
static int32_t args_process();

int32_t gen_args_init(gen_args_t* args);
int32_t gen_args_destroy(gen_args_t* args);
int32_t gen_args_parse(gen_args_t*args,int argc,char**argv);

