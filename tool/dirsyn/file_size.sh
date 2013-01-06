#! /bin/bash

function get_all_file_size()
{
	file_path=$1
	output_path=$2

	if [ "X$output_path" == "X-" -o "X$output_path" == "X" ];
	then
		output_path=""
	fi;
	find "$file_path" -type f -printf "%s %h%f\n" | tee -a $output_path;

#下面的方法也可以,但处理超过1020时会报打开文件太多bug
#	find "$file_path" -type f | awk '{ 
#			cmd=sprintf("ls -al \"%s\" | cut -d\047 \047 -f 5 ",$0); 
#			cmd | getline file_size1; 
#			printf("%s %s\n",file_size1,$0); 
#		}' | tee -a $output_path
}


get_all_file_size /home/along/desktop/desktop_doc/goodbook  /home/along/files_name
