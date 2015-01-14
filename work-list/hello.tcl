#! /usr/bin/wish 

#首先我们需要构造一个列表框
wm title . "work-list"

listbox .list 
.list insert 0 "New"
.list insert 1 "help"
.list config -selectmode single
bind .list <Double-1> list_double_select_event
pack .list -side top -fill x

#添加过程响应create
#添加过程响应双击
proc list_double_select_event {} {
	set idx [ .list curselection ] 
	if { $idx == 0 } {
		list_create_new_windows
	} else {
	puts stdout "select idx is $idx" ;
	}
}


#创建新的窗体
proc list_create_new_windows {} {
	puts stdout "hello world";
	toplevel .nw
	wm title .nw "create-list"
	label .nw.title_txt -text "任务标题"
	entry .nw.title
	label .nw.time_txt -text "创建时间"
	entry .nw.time
	label .nw.process_txt -text "处理进度"
	text  .nw.process 
	button .nw.save -command exit -text "
}
