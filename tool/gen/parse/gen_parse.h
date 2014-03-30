#ifndef GEN_PARSE_H_
#define GEN_PARSE_H_

/**
 * hot key 最大大小
 */
#define GEN_HOT_KEY_MAX_SIZE (64ULL)


/**
 * 模块文件解析
 * @param[in] args 参数
 * @return 0 成功
 * @return !0 失败
 */
int32_t gen_parse_tmplate_file_process(gen_args_t*args);


#endif /* GEN_PARSE_H_ */
