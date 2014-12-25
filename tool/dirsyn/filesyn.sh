#! /bin/bash
#做什么?
#对两个文件集合做差运算
#怎么做?
#1.生成文件集合
#2.做差

function error_log()
{
	log_info="$1"
	printf "%s" $log_info
}

function find_all_file()
{
	dir="$1";
	outfile="$2";
	find "$dir" -type f -print | xargs cksum >>$outfile ;
}

function find_filter_file()
{
	dir="$1"
	outfile="$2"
	filter="$3"
	
	find "$dir" -type f -print | xargs grep -E "$filter$" | xargs cksum >>$outfile ;
}

function find_file()
{
	dir="$1";
	outfile="$2";
	filter="$3";

	if [ $# -eq 3 -o $# -eq 2 ];
	then
	   :
	else
	   error_log "find_file function argment fail,file_file <dir> <outfile> [<filter>]"
	fi;

	if [ "X$filter" == "X" ] ;
	then
		find_all_file "$dir" "$outfile";
	else
		find_filter_file "$dir" "$outfile" "$filter";
	fi;
}

find_file . an.txt
echo "-----------------------" >> an.txt
find_file "`pwd`" an.txt '.*syn'
