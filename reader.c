#include "header_dir/reader.h"
#include <stdio.h>
#include "header_dir/mystring.h"

//file var for reader.c
static FILE * source;


boolean reader_openFile(char fileName[strlength]){
//opening source file for narration
	source = fopen(fileName,"r");
	if (source != NULL) 
		return true;
	else
		return false;
}

void reader_checkID(char* sentence,char* outp)
{
	char* s;
	s=&sentence[0];
	*outp = *s;
}

void reader_searchID(char id,char *outp,int ignore){
//search the sentence of the following id 
//to be the parameter of build narration and pass it to output
	boolean found = false;
	char sentence[strlength];
	char idcheck;
	while ((!found) && (fgets(sentence,strlength,source) != NULL)){
		reader_checkID(sentence,&idcheck);
		found = (idcheck == id);
		if (ignore != 0) {
			ignore--;
			found = false;
		}
	}
	if (found)
		mystrcpy(outp,sentence);
	else
		outp = NULL;
	rewind(source);
}

void reader_removeID(char *outp){
	boolean firstspace = false;
	char sentence[strlength];
	char* s;
	int i = 0;
	mystrcpy(sentence,outp);
	for ( s=&sentence[0]; (*s != '\000'); s++ )
	{		
		if (firstspace) {
			outp[i] = *s;
			i++;
		} else
			firstspace = (*s == ' ');
	}
	outp[i] = '\000';
}

void reader_close()
{
	fclose(source);
}
