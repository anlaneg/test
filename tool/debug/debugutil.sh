#! /bin/bash

#complier all debug file
for i in *.debug;
do
   self_name="`echo $i | awk '{ print substr($0,0,length($0) - length(\"debug\")) }'`"
   #echo $self_name
   command="`awk -F':' -f ./debuggen.awk -v file_name=$self_name *.debug`"
   #echo $command
   eval $command
done;
