#ifndef __big_brain_utils_h__
#define __big_brain_utils_h__

#include <ddcString.h>
#include <ddcDef.h>

typedef char byte;
typedef char bool;

#define MAX(a,b) ((a >= b) ? a : b)

struct big_brain
{
	char* code;
	char* code_start;
	byte* call_stack[10];
	int call_stack_ptr;
	byte memspace[1000];
	byte* ptr;
};

void compile_error(const char* cstr)
{
	ddPrintf("\x1b[38;2;255;255;255m[\x1b[38;2;255;0;0mERROR\x1b[38;2;255;255;255m] %s\n", cstr);
	exit(1);
}

#endif
