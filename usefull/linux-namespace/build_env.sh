#! /bin/bash

function execute()
{
	echo "$*"
	eval "$*"
}

function create_vrouter()
{
	name=$1
	execute ip netns add $name
}

function delete_vrouter()
{
	name=$1
	execute ip netns delete $name
}

function create_vrlink()
{
	vr_name=$1
	vrlink_name=$2
	execute ip link add $vrlink_name type veth peer name p_${vrlink_name}
	execute ip link set p_${vrlink_name} netns $vr_name
	execute ifconfig $vrlink_name 172.17.42.1/16 up
	execute ip netns exec $vr_name ifconfig p_${vrlink_name} 172.17.42.2/16 up
}

function delete_vrlink()
{
	vrlink_name=$1
	execute ip link delete ${vrlink_name}
}

function setup_server()
{
	vr_name=$1
	execute ip netns exec $vr_name python server.py
}

vr_name="hello"
vrlink_name="hi0"
delete_vrouter "$vr_name"
delete_vrlink  "$vrlink_name"

create_vrouter "$vr_name"
create_vrlink "$vr_name" "$vrlink_name" 
setup_server  "$vr_name"

