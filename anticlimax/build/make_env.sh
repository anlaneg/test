#! /bin/bash
function get_os_name()
{
    if [ -e '/etc/os-release' ];
    then
        echo "ubuntu";
    elif [ -e '/etc/system-release' ];
    then
        echo "centos";
    else
        echo "unkown";
    fi;
}

function do_require()
{
    require_path="$1"
    os_name=`get_os_name`
    require_file="$require_path/${os_name}_require"
    if [ -e "$require_file" ];
    then
        cat $require_file | while read line; do
            echo "=====>execute:$line"
            $line
        done;
    fi;
}

do_require .
