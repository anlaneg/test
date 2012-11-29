#实现读取配置文件生成debug模块控制
function gen_hfile()
{
	echo "h"
}

function gen_cfile()
{
	echo "h"
}

function output_upper()
{
	echo $1 | tr '[a-z]' '[A-Z]' 
}

#$1 config file name
function read_config_file()
{
	file_path=$1
	config_file_name="`basename $1 | cut -d'.' -f 1`";
	awk_command="awk -F ':' 'BEGIN{
		count=0;
	}

	{
		debug_info[count,\"macro\"]=\$1;
		debug_info[count,\"command\"]=\$2;
		debug_info[count,\"help\"]=\$3;
		count ++;
	}
	
	END{
		
		printf(\"/*文件头注释*/\n\");
		printf(\"#ifndef %s_DEBUG_H\n#define %s_DEBUG_H\n\n\",
			 \"`output_upper $config_file_name`\",
			 \"`output_upper $config_file_name`\");

		printf(\"/*下列宏用于定义$config_file_name 文件中指明的子模块*/\n\");
		for(i=0;i<count;++i)
		{
			printf(\"#define %s (1ULL<<%d) /*%s*/\n\",debug_info[i,\"macro\"],i,debug_info[i,\"help\"]);
		}

		printf(\"/*实现flag控制函数*/\n\");
		printf(\" static inline void module_debug_enable(const char*module_name)\n
			{\n
				/*加入实现*/\n
			}\n
			static inline void module_debug_disable(const char*module_name)\n
			{\n
				/*加入实现*/\n
			}\n

			static inline void module_debug_enable_all()\n
			{\n
				/*加入实现*/\n
			}\n
			
			static inline void module_debug_disable_all()\n
			{\n
				/*加入实现*/\n
			}\n

			static inline uint64_t module_debug_state()\n
			{\n
				/*加入实现*/\n
			}\n
		\");
		printf(\"#endif\n\");
	}'"

	#显示调试代码
	echo "$awk_command $file_path"
	#执行awk代码
	eval $awk_command $file_path
}


read_config_file *.debug
