
#define GEN_HOT_KEY_MAX_SIZE (64ULL)
typedef struct hot_point_info
{
	int32_t start;
	int32_t end;
	char hot_key[GEN_HOT_KEY_MAX_SIZE + 1];
}hot_point_info_t;

int32_t gen_parse_line(char*line,char*split_char,hot_point_info_t info[],int32_t max_info_size);

