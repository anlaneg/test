#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#define MAX_STEP (1024ULL)
#define INIT_CACHE_COUNT (2000000ULL)
char* init_cache_size(int32_t step)
{
	static char*array =NULL;
	if(!array)
	{
		int ret =posix_memalign((void**)&array,64,MAX_STEP*INIT_CACHE_COUNT*sizeof(char));
		assert(!ret);
	}
	
	return array;
}

void test_cache_size(char*array,int step)
{
	int32_t i;
	for(i = 0 ; i < INIT_CACHE_COUNT; ++i)
	{
		array[i*step]=i;
	}	
}

//此程序用于测试具体机器的cachesize
//用于获取不同cachesize的大小
int main(int argc,char**argv)
{

	//1.绑定cpu
	
	//2.做一些无聊的事情

	//3.测试不同步长需要多少时间？
	int i ;
	for(i = 1;i < MAX_STEP ;++i)
	{
		int64_t micro;
		struct timeval begin;
		struct timeval end;
				
		char* array = init_cache_size(i);
		assert(array);	

		gettimeofday(&begin,NULL); //time
		test_cache_size(array,i);
		gettimeofday(&end,NULL); //end time

		micro = (end.tv_usec-begin.tv_usec + 1000000ULL)+((end.tv_sec - begin.tv_sec -1)*1000000ULL);
		printf("%d %ld\n",i,micro);
		//free(array);
	}

	return 0;	
}
