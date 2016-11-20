#ifndef mystring_H
#define mystring_H

#include <stdio.h>
#include "boolean.h"
#include "lilfx.h"

int mystrlen(const char *str);

char *mystrcpy(char *dest, const char *src);

int mystrcmp(const char *str1, const char *str2);

void myprintstr(const char *str);

#endif
