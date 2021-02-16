#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcKeyboard.h>
#include <string.h>

#include "./utils.h"
#include "./exec.h"
#include "./file.h"
#include "./args.h"

int main(int argc, char** argv)
{
	read_args(argc, argv);
	if (!args_if_def(make_constant_ddString("__INPUT_FILE"))) compile_error("NO INPUT DATA");
	struct big_brain bb;
	if (args_if_def(make_constant_ddString("-f")))
		bb.code = read_file(args_get_value(make_constant_ddString("__INPUT_FILE")).cstr);
	else
		bb.code = args_get_value(make_constant_ddString("__INPUT_FILE")).cstr;
	bb.code_start = bb.code;
	bb.call_stack[10];
	bb.call_stack_ptr = 0;
	for (int i = 0; i < 1000; i++) bb.memspace[i] = 0;
	bb.ptr = &((bb.memspace[0]));
	if (args_if_def(make_constant_ddString("-r"))) full_run(&bb);
	else if (args_if_def(make_constant_ddString("-w"))) watch_run(&bb);
	else full_run(&bb);
	ddPrint_nl();
	return 0;
}
