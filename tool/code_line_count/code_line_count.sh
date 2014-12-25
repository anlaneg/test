#! /bin/bash

function get_source_count()
{
	dir=$1;
	file_pattern="$2";
	
	total_line=0;
	for i in `find $dir -type f -name $file_pattern`;
	do
		line_count=`wc -l "$i" | cut -d' ' -f 1`;
		total_line=$((total_line+line_count));
	done;
	echo "$total_line"
}

get_source_count /home/along/workspace/bjdev/src '*.[ch]'
