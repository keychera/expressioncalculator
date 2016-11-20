#ifndef reader_H
#define reader_H

#define MARK "zzz"

#include "boolean.h"
#include "mystring.h"

#define strlength 99
#define idlength 5
//file var for reader.c
//static FILE * source;

boolean reader_openFile(char fileName[strlength]);

char reader_checkID(char* sentence);

void reader_searchID(char id,char *outp,int ignore);

void reader_removeID(char *outp);

void reader_close();


#endif
