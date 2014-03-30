/*
 * xparse_main.c
 *
 *  Created on: Oct 1, 2013
 *      Author: along
 */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "libxml.h"
#include "xp_debug.h"
#include "xp.h"
#include "libmem.h"
#include "xp_vector.h"
#include "xp_syntax.h"

int main(int argc, char**argv)
{
	libxml_node_t* root;
	char* in_xml =
			//"/home/along/project/cworkspace/easyweb/tool/xparse/test/login.xml";
	"/home/along/project/cworkspace/easyweb/tool/xparse/test/version_1.0.xml";

	//1.init
	if (xp_parse_init())
	{
		LIB_ERROR(FRAME, "parse init fail!\n");
		return -1;
	}

	//2.load file
	if (!(root = xp_parse_load_file(in_xml)))
	{
		LIB_ERROR(FRAME, "load xml file '%s' fail!\n", in_xml);
		return -1;
	}

	//3.syntax check
	if (xp_syntax_check(root, 1))
	{
		LIB_ERROR(FRAME, "syntax check fail!\n");
		return -1;
	}

	//4.
	void*result;
	if (!(result = xp_syntax_build_tree(root, 1)))
	{
		LIB_ERROR(FRAME, "syntax build tree fail!\n");
		return -1;
	}

	//do destroy
	if (xp_parse_destroy())
	{
		LIB_ERROR(FRAME, "parse frame init fail!\n");
		return -1;
	}

	return 0;
}
