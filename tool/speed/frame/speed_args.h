/**
 * @author:along
 * @date: 2013-04-06
 * @brief 用于实现框架对外命令行提供
 */

/**
 * speed frame 参数解析结果结构体
 * 随着软件的成长，对外的参数解析结果
 * 均需保存在此结构体里，这个结构体也一并需要变换。
 */
typedef struct speed_frame_args
{
	uint32_t msg_size;
	uint32_t msg_count;
	char* module_name;
}speed_frame_args_t;

