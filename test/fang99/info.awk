#! /bin/awk -f

function parse_table()
{
	tabel=""
	if(index($0,"<table")) 
	{ 
		table=sprintf("%s%s",table,$0) ; 
		getline ;
		while(1)
		{
			while(index($0,"</table>")) 
			{ 
				printf("%s%s\n",gsub("","\r",table),$0);
				return ;
			}
			table=sprintf("%s%s",table,$0); 
			getline;
		}
	} 
}

BEGIN{
	line_number = 0;
}

{ 
	parse_table()
}

END{
	printf("parse table %d\n",line_number);
}
