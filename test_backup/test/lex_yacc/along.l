%{
#include <stdio.h>
%}
CHAR [A-Za-z_]
DIGIT [0-9]
ID  {CHAR}[{DIGIT}|{CHAR}]*

line \n

whitespace [\r\n ]
%%

{ID} {
	printf("hello %s\n",yytext);
     }

{line} {
	static int line = 0;
	printf("line = %d\n",line++);
     }

{whitespace} {
	printf("blank\n");
	}
.	{
		printf("unkown\n");
	}
%%
int main()
{
	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}
