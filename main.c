/* TUGAS TBFO */

#include <stdio.h>
#include "header_dir/stacklist.h"
#include "header_dir/pda.h"
#include "header_dir/hitung.h"

int main () {
	boolean notFinal = false;
	pda_initiate("pda.txt");
	char sentence[strlength];
	scanf("%s",sentence);
	char *s;
	for ( s=&sentence[0]; (*s != '\000'); s++ ){
		if (pda_transition(*s)) {
			//pda_showCondition();
		} else {
			notFinal = true;
			break;
		}
	}
	if(!notFinal){
		if (pda_finalState()){
			printf("the sentence : %s\n",debracketize(sentence));
			if (pda_floatExist()) {
				printf("%.2f\n",HitungEkspresi(debracketize(sentence)));
			} else
				printf("%d\n",(int)HitungEkspresi(debracketize(sentence)));
		} else {
			printf("SINTAK ERROR\n");
		}
	} else {
		printf("SINTAK ERROR\n");
	}
	reader_close();
	return 0;
}
