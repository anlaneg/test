#! /bin/bash
function execute()
{
	echo "$*"
	eval "$*"
}

function make_test()
{
	file="$*"
	execute make -r -R --no-print-directory -f "$file"
	execute make -r -R --no-print-directory -f "$file" clean
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
make_test Makefile -C ./project
rm -rf libtest.a  libtest.so  test
