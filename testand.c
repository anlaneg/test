#include <stdio.h>

struct test_type
{
	int array[3];
	char string[18];
};

int main(int argc,char**argv)
{
	//c解析器总是认为这个&号写与不写是相等的
	//另外运行本例多次可以发现加载器在加载本程序时,会
	//悄悄的从不同地址进行偏移,具体结果见下例
	struct test_type test;
	printf("%p ,%p\n",test.array,&(test.array));
	printf("%p ,%p\n",test.string,&(test.string));
	return 0;
}


#if 0

//测试结果
请按 ENTER 或其它命令继续
0xbfc28fcc ,0xbfc28fcc
0xbfc28fd8 ,0xbfc28fd8

请按 ENTER 或其它命令继续

请按 ENTER 或其它命令继续
0xbfc375fc ,0xbfc375fc
0xbfc37608 ,0xbfc37608

请按 ENTER 或其它命令继续
0xbf96829c ,0xbf96829c
0xbf9682a8 ,0xbf9682a8

请按 ENTER 或其它命令继续
0xbfe6652c ,0xbfe6652c
0xbfe66538 ,0xbfe66538

请按 ENTER 或其它命令继续
0xbfb64dec ,0xbfb64dec
0xbfb64df8 ,0xbfb64df8

请按 ENTER 或其它命令继续
0xbfc745ec ,0xbfc745ec
0xbfc745f8 ,0xbfc745f8

请按 ENTER 或其它命令继续
0xbf9261ac ,0xbf9261ac
0xbf9261b8 ,0xbf9261b8

请按 ENTER 或其它命令继续
0xbfc5115c ,0xbfc5115c
0xbfc51168 ,0xbfc51168

#endif
