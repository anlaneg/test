#include <stdio.h>
#include <unistd.h>

extern char* __progname;

char* get_file_name(int argc,char**argv)
{
	if(argc != 2)
	{
		printf("%s <filepath>\n",__progname);
		return NULL;
	}
	
	if(access(argv[1],R_OK))
	{
		printf("filepath %s can not read!\n",argv[1]);
		return NULL;
	}	

	return argv[1];
}

int statistical_frequency(char*file_name,long* char_count)
{
	int c;
	FILE* file = fopen(file_name,"r");
	while((c=fgetc(file))!=EOF)
	{
		char_count[c] ++;
	}
	
	fclose(file);
}

void display_frequency(long*char_count,int length)
{
	int i;
	printf("int array[]={\n");
	for(i = 0 ; i < length;++i)
	{
		printf("	[%d]=%ld,\n",i,char_count[i]);
	}
	printf("};\n");
}

int main(int argc,char**argv)
{
	//1.检查文件是否存在
	long char_count[256]={0,};
	char* file_name;
	if(!(file_name = get_file_name(argc,argv)))
	{
		return 1;
	}
	
	if(statistical_frequency(file_name,char_count))
	{
		return 1;
	}

	display_frequency(char_count,256);
	return 0;
}	
