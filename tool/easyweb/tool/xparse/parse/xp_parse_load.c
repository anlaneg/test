/*
 * xp_parse_load.c
 *
 *  Created on: Oct 16, 2013
 *      Author: along
 */
#include <stdint.h>
#include <stddef.h>

#include "libxml.h"

libxml_node_t* xp_parse_load_file(const char* xml)
{
	return libxml_file_load(xml);
}
