//a pda machine

#include <stdio.h>
#include "header_dir/pda.h"

char state;
Stack stack;

void pda_initiate(char fileName[strlength]){
	reader_openFile(fileName);
	state = 'q';
	CreateEmptyStack(&stack);
	Push(&stack,'Z');
}

boolean pda_transition(char alphabet){
//read alphabet and global state and top of stack and change the state and the stack
//return true if it succesfully transition
	boolean found = false;
	int ignore = 0;
	char sentence[strlength];
	do {
		reader_searchID(alphabet,sentence,ignore);
		if (mystrcmp(sentence,MARK) != 0) {
			reader_removeID(sentence);
			found = (reader_checkID(sentence) == state);
			if (!found) {
				ignore++;
			} else {
				reader_removeID(sentence);
				found = (reader_checkID(sentence) == InfoTop(stack));
				if (!found) {
					ignore++;
				} else {
					reader_removeID(sentence);
				}
			}
		}
	} while ((!found) && (mystrcmp(sentence,MARK) != 0));
	if (found) {
		state = reader_checkID(sentence);
		reader_removeID(sentence);
		infotypeSt dummy;
		switch (reader_checkID(sentence)) {
			case '+' ://push stack
					reader_removeID(sentence);
					Push(&stack,reader_checkID(sentence));
					break;
			case 'e' ://pop stack
					Pop(&stack,&dummy);
					break;
			default  ://change top of stack
					if (reader_checkID(sentence) != InfoTop(stack)){
						Pop(&stack,&dummy);
						Push(&stack,reader_checkID(sentence));
					}
		}
	}
	if (IsSEmpty(stack)) found = false;
	return found;
}

void pda_showCondition(){
	printf("current state : %c\n",state);
	printf("current stack's top : %c\n",InfoTop(stack));
}

boolean pda_finalState(){
	return (((state == 'q') || (state == 'n') || (state == 'c')) && (InfoTop(stack) == 'Z'));
}


