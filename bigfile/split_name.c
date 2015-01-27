#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char**argv)
{
    if(argc != 3)
    { 
	printf("usage split <length> <number>\n");
	return 1;
    }

    int length = atoi(argv[1]);
    int number = atoi(argv[2]);
	
    char* file_name=(char*)malloc(sizeof(char)*(length + 1));
    memset(file_name,'a',sizeof(char)*(length+1));
    file_name[length]='\0';
    
    int i ;
    for(i = length-1;i >=0; i--)
    {
	file_name[i]=((number % 26)+ 'a' );
	number = number /26;
	if(number == 0)
	{
		i--;
		break;
	}
    } 
    #if 0
    for(/*i--;*/; i >=0 ; i--)
    {
	file_name[i] = 'x';
    }
    #endif 
    printf("%s\n",file_name);
    return 0; 
}
