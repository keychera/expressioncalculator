/* TUGAS TBFO */

#include <stdio.h>
#include "header_dir/stacklist.h"
#include "header_dir/pda.h"

int main () {
	boolean notFinal = false;
	pda_initiate("pda.txt");
	pda_showCondition();
	char sentence[strlength];
	/*char inp;int ign;
	scanf("%c %d",&inp,&ign);
	reader_searchID(inp,sentence,ign);*/
	scanf("%s",sentence);
	char *s;
	for ( s=&sentence[0]; (*s != '\000'); s++ ){
		//printf("input %c\n",*s);
		if (pda_transition(*s)) {
			//pda_showCondition();
		} else {
			printf("input tidak diterima PDA\n");
			boolean notFinal = true;
			break;
		}
	}
	if(!notFinal){
		if (pda_finalState()){
			printf("input diterima PDA\n");
		} else {
			printf("input tidak diterima PDA\n");
		}
	}
	
	reader_close();
	return 0;
}
