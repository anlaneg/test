/**
 * @author: along
 * @date : 2013-08-31
 * @brief :本文件用于实现easywebparse的前期生成
 * @logic:
 */
#include <assert.h>
#include <stdlib.h>

#include "jp_debug.h"
#include "json_parse.h"
#include "jp.h"
#include "jp_symbol_table.h"
#include "jp_tag_attribute.h"
#include "jp_tag.h"
#include "jp_parse_frame.h"

int main(int argc, char**argv)
{
	json_t * json;
	memset(&g_jparse_args, 0, sizeof(jp_jparse_args_t));
	if (jparse_args_process(&g_jparse_args, argc, argv))
	{
		exit(0);
	}

	//load summary.txt.json
	assert(g_jparse_args.complier_file);
	LIB_LOG(CORE, "load complier file:'%s'...\n", g_jparse_args.complier_file);

	if (!(json = jparse_file_load(g_jparse_args.complier_file)))
	{
		LIB_ERROR(CORE, "load file:'%s' fail!\n", g_jparse_args.complier_file);
		return -1;
	}

	LIB_LOG(CORE, "read json string:'%s'\n", json_object_print(json));
	if(jp_parse_handle_init())
	{
		LIB_ERROR(CORE,"init parse handle fail!\n");
		return -1;
	}

	if (jp_parse_handle_parse(json,&g_symbol_table))
	{
		LIB_ERROR(CORE, "parse json fail!\n");
		jp_tag_symbol_table_uninit(&g_symbol_table);
		return -1;
	}


#if 0
	//check
	//gen
#endif

	json_object_destroy(json);
	jparse_args_destroy(&g_jparse_args);
	return 0;
}
