/* File : stacklist.h */
#include <stdio.h>
#include "header_dir/stacklist.h"


//PREFIX Lstr

/* Prototype manajemen memori */
void Alokasi (addressSt *P, infotypeSt X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
	*P = malloc(sizeof(*P));
	if (*P != NilS) {
		InfoLstr(*P) = X;
		NextLstr(*P) = NilS;
	}
}
void Dealokasi (addressSt  P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
	free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsSEmpty (Stack S)
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
{
	return (Top(S) == NilS);
}
void CreateEmptyStack (Stack * S)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
{
	Top(*S) = NilS;
}
void Push (Stack * S, infotypeSt X)
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
	addressSt P;
	Alokasi(&P,X);
	if (P != NilS) {
		if (IsSEmpty(*S)) {
			Top(*S) = P;
		} else {
			NextLstr(P) = Top(*S);
			Top(*S) = P;
		}
	}
}
void Pop (Stack * S, infotypeSt *X) //key fix for issue #4
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
	*X = InfoTop(*S); //key fix for issue #4
	if (NextLstr(Top(*S)) == NilS) {
		Dealokasi(Top(*S));
		CreateEmptyStack(&*S);
	} else {
		addressSt Pdel = Top(*S);
		Top(*S) = NextLstr(Top(*S));
		Dealokasi(Pdel);
	}

}
