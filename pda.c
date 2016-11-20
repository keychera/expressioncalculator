//a pda machine

#include "header_dir/pda.h"

char state;
Stack stack;
static FILE *source;

void pda_read(char fileName[strlength]);

boolean pda_transition(char alphabet);
//read alphabet and global state and top of stack and change the state and the stack
//return true if it succesfully transition



