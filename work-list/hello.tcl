#! /usr/bin/wish 

#首先我们需要构造一个列表框
wm title . "work-list"

listbox .list 
.list insert 0 "New"
.list insert 1 "help"
.list config -selectmode single
bind .list <Double-1> proc_list_double_select_event
pack .list -side top -fill x

#添加过程响应create
#添加过程响应双击
proc proc_list_double_select_event {} {
	set idx [ .list curselection ] ;
	if { $idx == 0 } {
		proc_create_config_window
	} else {
		proc_load_config_window
	}
}

#create config window
proc proc_create_config_window {} {
	toplevel .config_window
	label .config_window.title_label -text "标题"
	entry .config_window.title 
	label .config_window.process_label -text "进度"
	text  .config_window.process
	button .config_window.save -text "save" -command proc_save_new_config
	#button .config_window.finish -text "finish"
	pack .config_window.title_label -side left
	pack .config_window.title -side left
	pack .config_window.process_label -side bottom
	pack .config_window.process -side bottom
	pack .config_window.save  -side left
	#pack .config_window.finish -side left
}

proc proc_save_new_config {} {
	set title [ .config_window.title get ];
	set fd [ open /home/along/db.log a+ ];
	set time [ clock seconds ] ;
	set time [ clock format $time -format "%Y-%m-%d %H:%M:%S" ]
	set process [ .config_window.process get 1.0 end  ];
	puts $fd "##$title##$time##$process";
	close $fd
}


proc proc_load_config_window {} {
}
