#! /usr/bin/wish 

#首先我们需要构造一个列表框
wm title . "work-list"

listbox .list 
.list insert 0 "New"
.list config -selectmode single
bind .list <Double-1> list_double_select_event
pack .list -side top -fill x

#添加过程响应create
#添加过程响应双击
proc list_double_select_event {list} {
	puts stdout "hello world"
}
