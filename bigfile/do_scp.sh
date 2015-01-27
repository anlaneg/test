#! /bin/bash
file_count=598
file_length=2
save_path=/home/along/mountpoint/x_root/anlang


./scp_expect.sh xbj $save_path
./scp_expect.sh xdb $save_path
./scp_expect.sh xmu $save_path
#for((i=0;i<$file_count;++i));
#do
#  name=`./splitname 2 $i`
#  name="x$name"
#  ./scp_expect.sh $name $save_path
#  echo "同步$name 完成 `date`"
#done;



#function find_not_exist()
#{
#   i=$1;
#   #echo "[$i]"
#   for j in `cat an.txt`;
#   do
#	if [ "$j" == "$i" ];
#	then
#	    echo "1";
#	    return;
#	fi;
#   done;
#   echo "0";
#   return ;
#}

#for i in `cat bn.txt`; 
#do
#  	ret="`find_not_exist $i`";
#	#echo "$i $ret"
#	if [ "$ret" == "0" ] ;
#	then
#		echo $i;
#  		./scp_expect.sh $i $save_path
#		echo "同步$i 完成 `date`"
#	fi;
#done;
