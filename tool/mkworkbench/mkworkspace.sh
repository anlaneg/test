#! /bin/bash

#$0 指需要创建目录的父目录
function do_make_workspace()
{
	parent_path=$1;
	mkdir -p $parent_path/bin
	mkdir -p $parent_path/document
	mkdir -p $parent_path/mk
	mkdir -p $parent_path/src/include
	mkdir -p $parent_path/lib
	mkdir -p $parent_path/tool
	mkdir -p $parent_path/test
}


#在当前目录下创建工作区
do_make_workspace ../atf

