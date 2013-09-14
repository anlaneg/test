#! /bin/bash

#检查所给目录是否为git工作目录
#$1 目录
#return 1 是
#return 0 否
function is_git_workspace()
{
	path=$1;
	if `git log $path 2>/dev/null 1>/dev/null` ;
	then
		echo "1";
	else
		echo "0";
	fi;
}

#获取所给目录git版本库根
#$1 目录
#return 版本库根
function get_git_workspace_root()
{
	path=$1
	echo "unkown";
}

#获取所给目录git版本库版本号
#$1 目录
#return 版本库版本号
function get_git_workspace_version()
{
	path=$1
	echo "git:`git log $path 2>/dev/null | head -n 1 | cut -d ' ' -f 2`";
}

#怎么调试,依次调用
#is_git_workspace
#get_git_workspace_root
#get_git_workspace_version
#检查是否生成正确结果
