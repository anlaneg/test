#! /bin/bash

function gen_mms_list_file()
{
	#directory="orgin  process";
	directory="orgin";

	for dir in $directory ;
	do
		for file in ./$dir/*.txt ;
		do
			./util.awk "$file";
		done;
	done > mms.list;
}

#gen_mms_list_file

function wait_mplayer_timeout()
{
	file=$1;
	timeout=$2;

	(sleep $timeout ; echo "q") | mplayer "$file" 2>&1 | grep "No stream found" >/dev/null;
	if [ $? -eq 0 ] ; 
	then
		#url no stream
		echo "wrong url:$file";
		echo "$i" >>wrong.txt;
	else
		echo "$i" >>right.txt;
	fi;
}

function mms_url_test()
{
	for i in `cat mms.list`;
	do
		echo "test url:$i";
		wait_mplayer_timeout "$i" 40
	done;
}

mms_url_test


