/* File : stacklist.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H

#include "boolean.h"
#include <stdlib.h>

/* Konstanta */
#define NilS NULL

/* Deklarasi infotype */
typedef char infotypeSt;

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmt * addressSt;
typedef struct tElmt {
	infotypeSt Info;
	addressSt Next;
} Elmt; 

#define NextLstr(P) (P)->Next
#define InfoLstr(P) (P)->Info


/* Type stack dengan ciri TOP : */
typedef struct {
	addressSt TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).TOP->Info 


/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
/* Prototype manajemen memori */
void Alokasi (addressSt *P, infotypeSt X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */

void Dealokasi (addressSt  P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

boolean IsSEmpty (Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void CreateEmptyStack (Stack * S);
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Push (Stack * S, infotypeSt X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (Stack * S, infotypeSt *X); //key fix for issue #4
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif
