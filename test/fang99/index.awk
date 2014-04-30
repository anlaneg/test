#!/bin/awk -f

function skip_line()
{
	
}

function parse_line(i)
{
	if(i==1)
	{
		split($3,b,"=");
		printf("%s>",substr(b[3],1,length(b[3])-1));/* " */
	}
	else if(i==2)
	{
		printf("%s>",substr($4,1,length($4)-3));/*<\a*/
	}
	else if(i==3)
	{
		printf("%s>",substr($3,1,length($3)-7));/* <\font>*/
	}
	else if(i==4)
	{
		if(index($2,"href"))
		{
			split($2,b,"\"")
		}
		printf("%s%s>",substr($2,1,5),b[6]);
	}
	else if(i==5)
	{
		printf("%s>",substr($2,1,index($2,"&nbsp")-1));
	}
	else if(i==6)
	{
		printf("%s>",$2);
	}
	else if(i==7)
	{
		printf("%s>",substr($2,1,index($2,"<a href='/individialcenter")-1));
	}
	else if(i==8)
	{
		printf("%s>",substr($3,1,length($3)-3));/*<\a*/
	}
	else if(i==9)
	{
	}
	else if(i==10)
	{
	}
}

BEGIN{

   result[1,1]="";	
}

{
	for(i = 1; i < 10; ++i)
	{
		parse_line(i);
		getline
	}	
	parse_line(10);
	printf("\n");
}

END{
}
