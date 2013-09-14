#! /bin/bash

#记录版本管理软件名称
VERSION_SOFT_NAME=

#记录代码版本
VERSION=

#记录当前执行脚本的用户名
USERNAME="`whoami`"

#记录执行脚本时的时间
DATE="`date +'%Y/%m/%d %T'`"

#错误处理函数
#$1错误信息
#此函数将退出执行
function error_msg()
{
	message="$1"
	echo "$message";
	exit 1;
}

#装载除本文件以外的所有其它*_version.sh文件
function load_version_file()
{
	for i in `ls *_version.sh`;
	do
		source $i || error_msg "装载库$i失败";
	done;
}

#获取当前目录采用的版本管理软件名称	
function get_version_soft_name()
{
	for i in `ls *_version.sh`;
	do
		soft_name="`echo $i | sed 's/_version.sh//g'`";
		#echo "检查返回值:`is_${soft_name}_workspace .`";
		if [ "`is_${soft_name}_workspace .`"  == "1" ] ;
		then
			VERSION_SOFT_NAME=${soft_name};
			return;
		fi;
	done;
	error_msg "无法识别当前目录采用的版本管理软件";
}

#获取当前软件版本
function get_version()
{
	VERSION="`get_${VERSION_SOFT_NAME}_workspace_version `" 
}	

#解析version脚本
#$1 脚本代码
#输出生成的文件
function parser_version_script()
{
	script_path=$1;
	cat $script_path | awk -v date_inner="$DATE" -v user_inner="$USERNAME" -v src_ver_inner="$VERSION" -v split_char="-version=" '
		BEGIN {
			along_match=0;
			pro_name="";
		} 

		/^\s?[^#]+.+version/{
			#获取pro_name			
			pro_name=substr($0,0,index($0,split_char));

			#获取格式串
			line=substr($0,length(pro_name) + length(split_char) + 1 )
			
			#printf("length(pro_name:\"%s\")= %d length(split_char:\"%s\")=%d ,%s\n",pro_name,length(pro_name),split_char,length(split_char),line);
			#替换内部变量
			gsub(/\$\(DATE\)/,date_inner,line) ; 
			gsub(/\$\(SRC_VER\)/,src_ver_inner,line) ; 
			gsub(/\$\(USER\)/,user_inner,line);
			along_match=along_match + 1 ;
		} 
	
		END{ 
			if(along_match > 1)
			{
				printf("file error,exsit more than one format line\n");
				exit 1
			}
			#printf("line:%s match %d\n",line,match(line,/^".*"$/));
			if(match(line,/^".*"$/) ==0 )
			{
				printf("format line miss \"");
				exit 1;
			}

			printf("const char* %s_get_version_info()\n{\nstatic const char* pro_name=%s;\nreturn pro_name;\n}\n",pro_name,line);
		}'

}

#测试代码
load_version_file
get_version_soft_name
get_version
#echo "soft_name:${VERSION_SOFT_NAME}";
#echo "version:${VERSION}"
parser_version_script VERSION 
