#ifndef __big_brain_file_h__
#define __big_brain_file_h__

#include <stdio.h>

#include "./utils.h"

char* read_file(const char* path)
{
	FILE* fp = fopen(path, "r");
	if (fp == null) return "ERROR";
	fseek(fp, 0L, SEEK_END);
	long nb = ftell(fp) - 1;
	fseek(fp, 0L, SEEK_SET);
	char* buffer = (char*)calloc(nb+4, sizeof(char));
	fread(buffer, sizeof(char), nb, fp);
	fclose(fp);
	buffer[nb] = 0;
	return buffer;
}

#endif
