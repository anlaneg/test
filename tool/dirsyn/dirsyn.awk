#! /usr/bin/awk -f
{ 
	dirsyn_parser_config_line($0);
} 

END{
	dirsyn_end();
}



/*完成配置行解析*/
function dirsyn_parser_config_line(config_line)
{
	#忽略掉注释行
	if(match($0,/^\s?#.*$/))
	{ 
		next;
	}
	
	#忽略掉空行
	if(match($0,/^\s?$/))
	{
		next;
	}

	#解析配置行	
	if((equal_loc=index(config_line,"="))>0)
	{
		config_array[substr(config_line,0,equal_loc-1)]=substr(config_line,equal_loc+1);
	}
	else
	{
		printf("error config line:%s\n",config_line);
	}
}


function dirsyn_end()
{
	#参数校验
	if(dirsyn_config_valid(config_array))
	{
		printf("config valid fail!\n");
	}
	#生成脚本代码
	if(dirsyn_generate_shell_script(config_array))
	{
		printf("generate shell script fail!\n");
	}
}

function dirsyn_config_valid(config_array)
{
	/*TODO add config line valid*/
	return 0;	
}

function dirsyn_generate_shell_script(config_array)
{
	for( i in config_array) {
		printf("array[%s]=%s\n", i,config_array[i]);
	}
	return 0;
}


