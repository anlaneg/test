#! /bin/bash

#complier all debug file
#$1 complier file
#$2 output folder
function complier_debug_file()
{
	debug_file="`basename $1`";
	out_folder="$2";
	self_name="`echo $debug_file | awk '{ print substr($0,0,length($0) - length(\"debug\")) }'`";
	#echo $self_name
	command="`awk -F':' -f ./debuggen.awk -v file_name=$self_name out_path=$out_folder $1`"
	#echo $command
	eval $command
}

complier_debug_file ./example/process.debug  ./example/
