#ifndef __big_brain_exec_h__
#define __big_brain_exec_h__

#include "./utils.h"

int exec(struct big_brain* bb);
void full_run(struct big_brain* bb);
void jump_to_label(char** _code, char label_name);
void jump_from_closer(char** _code);
void jump_to_closer(char** _code);

void jump_to_closer(char** _code)
{
	char* code = *_code;
	int scope = 0;
	while (!(*code == ']' && scope == 1))
	{
		if (*code == '[') scope++;
		else if (*code == ']') scope--;
		code++;
	}
	*_code = code;
}
void jump_from_closer(char** _code)
{
	char* code = *_code;
	int scope = 0;
	while (!(*(--code) == '[' && scope == 0))
	{
		if (*code == ']') scope++;
		else if (*code == '[') scope--;
	}
	*_code = code;
}
void jump_to_label(char** _code, char label_name)
{
	char* code = *_code;
	while (!(*code == '#' && *(code+1) == label_name)) code++;
	code++;
	*_code = code;
}

void print_info(struct big_brain* bb, int cptr, int mem_len)
{
	int i;
	cursor_move_to(0, 3);
	ddPrints("memoryspace = [");
	for (i = 0; i < mem_len; i++)
	{
		if (i == cptr) cursor_style_underline();
		ddPrintf("%d", bb->memspace[i]);
		cursor_style_reset();
		ddPrints(", ");
	}
	if (i == cptr) cursor_style_underline();
	ddPrintf("%d", bb->memspace[i]);
	cursor_style_reset();
	ddPrints("]");
	
}

void watch_run(struct big_brain* bb)
{
	int max_ptr = 0;
	cursor_clear();
	cursor_home();
	ddPrintf("%s", bb->code_start);
	cursor_move_to(0, 2);
	ddPrintf("output:");
	cursor_save();
	while (*(bb->code))
	{
		int cptr = ((long)bb->ptr)-((long)(&(bb->memspace[0])));
		max_ptr = MAX(max_ptr, cptr);
		int pos = ((long)bb->code)-((long)bb->code_start);
		cursor_move_to(0, 0);
		cursor_move(pos, 0);
		ddPrint_char('^');
		print_info(bb, cptr, max_ptr);
		cursor_restore();
		ddKey_getch();
		if (exec(bb) == 1) break;
		cursor_save();
		cursor_move_to(0, 0);
		cursor_move(pos, 0);
		ddPrint_char(' ');
	}
	cursor_move_to(0, 8);
}
void full_run(struct big_brain* bb)
{
	while (*(bb->code))
	{
		exec(bb);
	}
}

int exec(struct big_brain* bb)
{
	switch (*(bb->code))
	{
		case '@':
		{
			char label_name = *(++(bb->code));
			bb->code = bb->code_start;
			jump_to_label(&(bb->code), label_name);
		} break;
		case '#':
		{
			(bb->code)++;
		} break;
		case '[':
		{
			if (!(*bb->ptr)) jump_to_closer(&(bb->code));
		} break;
		case ']':
		{
			if (*(bb->ptr)) jump_from_closer(&(bb->code));
		} break;
		case '~':
		{
			return 1;
		} break;
		case '!':
		{
			bb->code = bb->call_stack[--(bb->call_stack_ptr)];
		} break;
		case '?':
		{
			bb->call_stack[(bb->call_stack_ptr)++] = bb->code;
		} break;
		case '>':
		{
			(bb->ptr)++;
		} break;
		case '<':
		{
			(bb->ptr)--;
		} break;
		case '+':
		{
			(*(bb->ptr))++;
		} break;
		case '-':
		{
			(*(bb->ptr))--;
		} break;
		case '$':
		{
			ddPrint_int(*(bb->ptr));
		} break;
		case '%':
		{
			ddPrint_char(*(bb->ptr));
		} break;
		case ',':
		{
			*(bb->ptr) = ddKey_getch();
		} break;
	}
	(bb->code)++;
	return 0;
}

#endif
