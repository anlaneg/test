#! /bin/bash

WORKSPACE_ROOT=
GIT_TEST_ROOT="`pwd`/.."

function do_directory()
{
	dir_path="$1";
	help_info="$2";
	mkdir -p "$dir_path"
}

#$0 指需要创建目录的父目录
function do_make_workspace()
{
	WORKSPACE_ROOT="$1"
	do_directory $WORKSPACE_ROOT/bin #用于存放生成的可执行程序
	do_directory $WORKSPACE_ROOT/document  #用于存放文档
	do_directory $WORKSPACE_ROOT/src/include  #用来存放公共头文件
	do_directory $WORKSPACE_ROOT/lib #用于存放生成的lib库
	do_directory $WORKSPACE_ROOT/tool #用于存放源码或构建工具
	do_directory $WORKSPACE_ROOT/test #用于存放可执行代码

	ln -s "$GIT_TEST_ROOT/amf" $WORKSPACE_ROOT/mk #用来存放amf
	cp $WORKSPACE_ROOT/mk/environment_setting $WORKSPACE_ROOT/environment_setting
	chmod u+x $WORKSPACE_ROOT/environment_setting

	do_directory $WORKSPACE_ROOT/src/lib #用来存放lib库及其头文件
	ln -s "$GIT_TEST_ROOT/libdebug" "$WORKSPACE_ROOT/src/lib/libdebug"
}


#在当前目录下创建工作区
rm -rf ./example
do_make_workspace  ./example

