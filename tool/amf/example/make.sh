#! /bin/bash
function execute()
{
	echo "$*"
	eval "$*"
}

function make_test()
{
	file=$1
	execute make -f $file 
	execute make -f $file clean
}

source environment_setting
make_test Makefile.normal
mkdir ../obj
make_test Makefile.tiny
rm -rf ../obj
make_test Makefile.lib
make_test Makefile.obj
make_test Makefile.dynlib
make_test Makefile.bin
rm -rf libtest.a  libtest.so  test
