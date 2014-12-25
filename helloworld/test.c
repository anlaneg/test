#include <stdio.h>
#include <string.h>
#include <ctype.h>

//一个字节的最大值
#define MAX_COUNT 0X100

//需要的统计数组
long char_count[MAX_COUNT];

//将统计数组清零
int init_char_count()
{
	memset(char_count,0,sizeof(char_count));
	return 0;
}

int print_char_count()
{
	int i ;
	for(i = 0 ; i < MAX_COUNT;++i)
	{
		if(i%10==9)
		{
			printf("\n");
		}

		if(isprint(i))
		{	
			printf("char[%c]=%ld ",i,char_count[i]);
		}
		else
		{
			printf("char[%d]=%ld ",i,char_count[i]);
		}
	}

	return 0;

}

int main(int argc,char**argv)
{
	//统计出某一个字符大本文档中的数目
	const char* filename="/home/along/mountpoint/d_root/www.csdn.net.sql";
	unsigned char char_value=0;
	int row = 0;
	int error_number = 0;
	int have_error=0;

	FILE*file = fopen(filename,"r");
	if(file == NULL)
	{
		printf("error,file not fount\n");	
		return 1;
	}

	init_char_count();
	while(fread(&char_value,sizeof(char),1,file)==1)
	{
		//printf("%c",char_value);
		if(char_value == '\n')
		{
			row ++;
			if(have_error)
			{
				error_number++;
				printf("row=%d have error,error number=%d\n",row,error_number);
				have_error=0;
			}
		}
		if(!isprint(char_value) && char_value !='\r' && char_value !='\n')
		{
			//printf("row=%d col=%d value=%c\n",row,col,char_value);
			have_error=1;
		}
	
		char_count[char_value]++;		
	}

	fclose(file);	

	print_char_count();

	return 0;	
}
