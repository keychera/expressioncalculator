#ifndef _PDA_H
#define _PDA_H

//a pda machine

#include <stdio.h>
#include "boolean.h"
#include "stacklist.h"
#include "reader.h"


extern char state;
extern Stack stack;

void pda_read(char fileName[strlength]);

boolean pda_transition(char alphabet);
//read alphabet and global state and top of stack and change the state and the stack
//return true if it succesfully transition





#endif
