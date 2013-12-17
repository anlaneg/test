#! /bin/bash

CORE_LIST=`cat /proc/cpuinfo  | grep "processor" | cut -d':' -f 2`
CPU_INFO_DIR="/sys/devices/system/cpu"
#printf "core-list:%s\n" $CORE_LIST
for core in $CORE_LIST ;
do
    CORE_MHZ=`cat "/proc/cpuinfo" | grep "cpu MHz" | head -n $(($core+1)) | tail -n 1 | cut -d':' -f 2`
    printf "%s\n" "core-num:$core";
    printf "%s\n" "core-freq:$CORE_MHZ";

    index_count=`ls -1d $CPU_INFO_DIR/cpu$core/cache/index* | wc -l`;
    for((i=0;i<$index_count;++i));
    do
        dir="$CPU_INFO_DIR/cpu$core/cache/index$i";
        printf "\t%s," "level:`cat $dir/level`";
        printf "%s,"   "size:`cat $dir/size`";
        printf "%s,"   "cache-line:`cat $dir/coherency_line_size`";
        printf "%s,"   "way:`cat $dir/ways_of_associativity`";
        printf "%s,"   "share:`cat $dir/shared_cpu_list`";
        printf "%s\n"   "type:`cat $dir/type`";
        
    
    done;
done;
