#! /bin/bash

#记录版本管理软件名称
VERSION_SOFT_NAME=

#记录代码版本
VERSION=

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

#测试代码
load_version_file
get_version_soft_name
get_version
echo "soft_name:${VERSION_SOFT_NAME}";
echo "version:${VERSION}"
