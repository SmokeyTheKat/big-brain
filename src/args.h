#ifndef __big_brain_args_h__
#define __big_brain_args_h__

#include "utils.h"

struct compilerArgs
{
	ddString name;
	ddString value;
};

struct compilerArgs* cargs;
sizet cargsCount = 0;

void read_args(int argc, char** argv)
{
	cargs = make(struct compilerArgs, 1000);
	for (int i = 1; i < argc; i++)
	{
		ddString dsarg = make_ddString(argv[i]);
		if (ddString_compare_cstring(dsarg, "--help") || ddString_compare_cstring(dsarg, "-help"))
		{
			ddPrint_cstring("big-brain\n");
			ddPrint_cstring("usage: bb [OPTIONS...] file\n");
			ddPrint_cstring("options:\n");
			ddPrint_cstring("	-f			runs file\n");
			ddPrint_cstring("	-s			runs as string\n");
			ddPrint_cstring("	-r	(default)	just executes file\n");
			ddPrint_cstring("	-w			runs in live viewer/debuger\n");
			ddPrint_cstring("docs: https://ddmo.rf.gd/big-brain/\n");
			exit(0);
		}
		else if (dsarg.cstr[0] == '-')
		{
			cargs[cargsCount++].name = dsarg;
		}
		else if (dsarg.cstr[0] != '-')
		{
			cargs[cargsCount].name = make_constant_ddString("__INPUT_FILE");
			cargs[cargsCount++].value = dsarg;
		}
	}
}
ddString args_get_value(ddString name)
{
	for (sizet i = 0; i < cargsCount; i++)
	{
		if (ddString_compare(name, cargs[i].name)) return cargs[i].value;
	}
	return make_constant_ddString("ERROR");
}
bool args_if_def(ddString name)
{
	for (sizet i = 0; i < cargsCount; i++)
	{
		if (ddString_compare(name, cargs[i].name)) return true;
	}
	return false;
}

#endif
