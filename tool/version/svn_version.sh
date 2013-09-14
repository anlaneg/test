#! /bin/bash

#检查所给目录是否为svn工作目录
#$1 目录
#return 1 是
#return 0 否
function is_svn_workspace()
{
	path=$1;
	if `svn info $path 1>/dev/null 2>/dev/null` ;
	then
		echo "1";
	else
		echo "0";
	fi;
}

#获取所给目录svn版本库根
#$1 目录
#return 版本库根
function get_svn_workspace_root()
{
	path=$1
	echo "`svn info $path 2>/dev/null | head -n 3 | tail -n 1 | cut -d' ' -f 2`";
}

#获取所给目录svn版本库版本号
#$1 目录
#return 版本库版本号
function get_svn_workspace_version()
{
	path=$1
	echo "svn:`svn info $path 2>/dev/null | head -n 5 | tail -n 1 | cut -d ' ' -f 2`";
}

#测试代码
#is_svn_workspace /home/along/workspace/bjdev/src/
#get_svn_workspace_root /home/along/workspace/bjdev/src/
#get_svn_workspace_version /home/along/workspace/bjdev/src/
