/*
 * xp_parse_init.c
 *
 *  Created on: Oct 16, 2013
 *      Author: along
 */
#include <stdint.h>
#include <stddef.h>

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "libmem.h"
#include "libxml.h"
#include "xp_debug.h"
#include "xp_vector.h"
#include "xp_syntax.h"
#include "xp_plugin.h"
#include "xp.h"

int32_t xp_parse_init()
{
	xp_syntax_item_t* syntax_item_root = xp_syntax_item_get_root_item();
	assert(syntax_item_root);
	if (xp_syntax_init(1, syntax_item_root))
	{
		LIB_ERROR(PARSE, "add root syntax item %s:'%s' fail!\n",
				syntax_item_root->type == XP_TAG ? "tag" : "attribute",
				syntax_item_root->name);
		return -1;
	}
	return xp_syntax_init(xp_plugin_easyweb_syntax_size_get(),
			xp_plugin_easyweb_syntax_array_get());
}
