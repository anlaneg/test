
typedef int32_t (*gen_output_fun)(char*,void*arg);

typedef struct gen_buffer
{
	gen_output_fun output;
	void*arg;
	int32_t size;
	int32_t empty_loc;
	char buffer[0];
}gen_buffer_t;

gen_buffer_t* gen_buffer_t* gen_buffer_init(int32_t size,gen_output_fun output,void*arg);
gen_buffer_t* gen_buffer_destroy(gen_buffer_t*);

int32_t gen_buffer_flush(gen_buffer_t*buffer,get_output_fun output,void*arg);

//auto invoker buffer flush(one interface?)
//int32_t gen_buffer_push(gen_buffer_t*buffer,char*str,int32_t length);
//0== strlen(str)
int32_t gen_buffer_append(gen_buffer_t*buffer,char*str,uint32_t length);

