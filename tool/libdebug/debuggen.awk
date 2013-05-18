#注意调用方必须传送参数
#file_name进来，用来表示文件名称


BEGIN {
	count = 0;
}

{
		debug_info[count,"macro"]=$1;
		debug_info[count,"command"]=$2;
		debug_info[count,"help"]=$3;
		count ++;
}

END {
	#当前不支持count >=31的情况
	if(count >= 31)
	{
	    printf("echo \"当前不支持module数目大于31的情况\\n\"");
	    exit;
	}

	file_name_toupper=toupper(file_name);
	#printf("file_name_toupper:%s\n",file_name_toupper);
	file_module_count = gen_module_count();
	#printf("file_module_count:%s\n",file_module_count);
	file_module_macro = gen_module_macro();	
	#printf("file_module_macro:%s\n",file_module_macro);
	file_module_names = gen_module_names();
	#printf("file_module_names:%s\n",file_module_names);
	file_module_example_name=gen_module_example_name();
	#printf("file_module_example_name:%s\n",file_module_example_name);

	#生成hfile
	gen_hfile(file_name_toupper,file_module_macro);

	#生成cfile
	gen_cfile();
}

function gen_module_count()
{
	module_count = "#define " toupper(file_name) "_MODULE_COUNT  ("  count "ULL)\\n";
	return module_count;
}

function gen_module_macro()
{
	file_module_macro="";
	for(i = 0 ; i < count ; ++i)
	{
		file_module_macro = file_module_macro  "#define "  debug_info[i,"macro"]  " (1ULL << " i  ") /*" debug_info[i,"help"]  "*/\\n";
	}

	return file_module_macro;
}

function gen_module_names()
{
	file_module_names="";
	for(i = 0 ; i < count; ++i)
	{
		file_module_names= file_module_names  "\\\"" debug_info[i,"command"] "\\\",\\n";
	}
	
	return file_module_names  "NULL\\n";
}

function gen_module_example_name()
{
	module_example_name="";
	for(i = 0 ; i < count; ++i)
	{
		if(i >= 1)
		{
			break;
		}
		module_example_name=debug_info[i,"macro"];
	}
	
	return module_example_name;
}

function gen_hfile(file_name_toupper,file_module_macro)
{
	printf("cat template_debug.h | awk '{sub(\"##FILE_NAME_UPPER##\",\"%s\"); sub(\"##DEBUG_MODULE_COUNT##\",\"%d\");sub(\"##DEBUG_MODULE_MACRO_FLAG##\",\"%s\");sub(\"##DEBUG_MODULE_EXAMPLE##\",\"%s\"); print $0 }' > %s/%s_debug.h;",file_name_toupper,count,file_module_macro,file_module_example_name,out_path,file_name);
}	
			
	
function gen_cfile()
{
	printf("cat template_debug.c | awk '{sub(\"##FILE_NAME##\",\"%s\"); sub(\"##FILE_NAME_UPPER##\",\"%s\");sub(\"##DEBUG_MODULE_NAME##\",\"%s\"); print $0; }' > %s/%s_debug.c;",file_name,file_name_toupper,file_module_names,out_path,file_name);
}
