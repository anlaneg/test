#! /bin/bash
#此脚本用来生成实体类

#
function gen_entity_class_member()
{
	output_path="$1"
	$GEN_PRO -d -c $CFG_FILE_PATH -t ./script/entity_member.template -o $output_path
}

export GEN_PRO=/home/along/github_test/tool/easyweb/bin/gen
export CFG_FILE_PATH=/home/along/project/cworkspace/easyweb/tool/xparse/gen/script/entity_member.cfg

gen_entity_class_member /home/along/project/cworkspace/easyweb/tool/xparse/gen/test.java
