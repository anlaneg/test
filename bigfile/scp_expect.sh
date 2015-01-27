#!/usr/bin/expect
set username root
set password root
set host_ip 150.0.4.3
set host_path /home/along/ghost_split/split
set download_file [lindex $argv 0]
set save_path [lindex $argv 1]

puts " spawn scp $username@$host_ip:$host_path/$download_file $save_path "
spawn scp $username@$host_ip:$host_path/$download_file $save_path
set timeout 300
expect "password:"
set timeout 300
send "$password\r"
#set timeout 300
#send "exit\r"
expect eof
