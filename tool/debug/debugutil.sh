#实现读取配置文件生成debug模块控制
function gen_hfile()
{
	echo "h"
}

function gen_cfile()
{
	echo "h"
}


#$1 config file name
function read_config_file()
{
	
	config_file_name="`basename $1|cut -d'.' -f 1`";
	
}


read_config_file *.debug
