

#ifndef GEN_ARGS_H_
#define GEN_ARGS_H_

/**
 * 参数
 */
typedef struct gen_args
{
	gen_hash_args_t hash_args;
	gen_hash_t var_hash;
	char* my_name;
	char* cfg_file_path;
	char* template_file_path;
	char* output_file_path;
	char split_char;
	char escape_char;
	int32_t debug_level;
	int32_t is_need_show_help;
	int32_t is_need_show_version;
	int32_t global_buffer_size;
	gen_output_fun output_fun;
	gen_buffer_t* out_buffer;
}gen_args_t;

/**
 * 参数初始化
 * @param[in] args 参数
 * @param[in] prg_name 程序名称
 * @return 0 初始化成功
 * @return !0 初始化失败
 */
int32_t gen_args_init(gen_args_t* args,char*prg_name);

/**
 * 参数销毁
 * @param[in] args 参数
 */
void gen_args_destroy(gen_args_t* args);

/**
 * 解析参数
 * @param[in] args 参数
 * @param[in] argc 参数数目
 * @param[in] argv 参数集
 * @return 0 解析成功
 * @return !0 解析失败
 */
int32_t gen_args_parse(gen_args_t*args,int argc,char**argv);

/**
 * 为variable hash中添加一个变量
 * @param[in] args 参数
 * @param[in] variable 变量参数
 * @return 0 添加成功
 * @return !0 添加失败
 */
int32_t gen_args_hash_add_variable(gen_args_t* args, char*variable);
#endif /* GEN_ARGS_H_ */
