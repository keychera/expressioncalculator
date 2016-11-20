/* TUGAS TBFO */

#include <stdio.h>
#include "header_dir/stacklist.h"
#include "header_dir/pda.h"

int main () {
	reader_openFile("pda.txt");
	char sentence[strlength];
	reader_searchID('(',sentence,0);
	printf("%s",sentence);
	reader_removeID(sentence);
	printf("%s",sentence);
	reader_removeID(sentence);
	printf("%s",sentence);
	reader_removeID(sentence);
	printf("%s",sentence);
	reader_close();
	return 0;
}
