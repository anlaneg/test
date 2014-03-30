#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "gen.h"

int main(int argc, char**argv)
{
	int32_t ret = -1;
	gen_args_t args;

	//0.do args init
	if (gen_args_init(&args, argv[0]))
	{
		LIB_ERROR(PARSER, "init args fail!\n");
		return -1;
	}

	//1.parse argv
	if ((ret = gen_args_parse(&args, argc, argv)))
	{
		LIB_ERROR(PARSER, "parse argments fail!\n");
		gen_args_destroy(&args);
		exit(ret);
	}

	//2.do workdspace init
	gen_hash_dump(&args.var_hash, args.output_fun);

	//3.template file process
	gen_hash_dump(&args.var_hash, args.output_fun);
	if (gen_parse_tmplate_file_process(&args))
	{
		LIB_ERROR(PARSER, "parse tmplate fail!\n");
		gen_args_destroy(&args);
		return -1;
	}

	return 0;
}
