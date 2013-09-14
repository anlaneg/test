#ifndef GEN_PARSE_H_
#define GEN_PARSE_H_

/**
 * hot key 最大大小
 */
#define GEN_HOT_KEY_MAX_SIZE (64ULL)

/**
 * 热点信息
 */
typedef struct hot_point_info
{
	int32_t start;
	int32_t end;
	char hot_key[GEN_HOT_KEY_MAX_SIZE + 1];
} hot_point_info_t;

/**
 * 解析行信息
 * @param[in] line 行
 * @param[in] split_char 分隔符
 * @param[in] info 信息数组
 * @param[in] max_info_size 信息最大数目
 * @return 0 成功
 * @return !0 失败
 */
int32_t gen_parse_line(char*line, char*split_char, hot_point_info_t info[],
		int32_t max_info_size);

#endif /* GEN_PARSE_H_ */
