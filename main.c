/* TUGAS TBFO */

#include <stdio.h>
#include "header_dir/stacklist.h"
#include "header_dir/pda.h"

int main () {
	pda_initiate("pda.txt");
	pda_showCondition();
	char sentence[strlength];
	reader_searchID('a',sentence,0);
	scanf("%s",sentence);
	char *s;
	for ( s=&sentence[0]; (*s != '\000'); s++ ){
		if (pda_transition(*s))
			pda_showCondition();
		else {
			printf("input tidak diterima PDA\n");
			break;
		}
	}
	reader_close();
	return 0;
}
