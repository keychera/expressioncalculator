/*
NIM				:13515136
Nama			:Lazuardi Firdaus
Tanggal			:25 Oktober 2016
Topik praktikum	:List
Deskripsi		:Berisi fungsi dan prosedur untuk List dengan pointer 
				 ganda
*/

#include "header_dir/customlistdp.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean custIsEmpty (custList L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	return ((custFirst(L)==Nil)&&(custLast(L)==Nil));
}

/****************** PEMBUATAN LIST KOSONG ******************/
void custCreateEmpty (custList *L)
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
	custFirst(*L)=Nil;
	custLast(*L)=Nil;
}

/****************** Manajemen Memori ******************/
custaddress custAlokasi (custinfotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
	custaddress P;
	
	(P)=(custElmtList*) malloc (sizeof (custElmtList));
	if(P != NULL){
		custInfo(P)=X;
		custNext(P)=Nil;
		custPrev(P)=Nil;
	}
	else{
		P=Nil;
	}
	return P;
}
void custDealokasi (custaddress P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free (P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
custaddress custSearch (custList L, custinfotype X)
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	custaddress P;
	boolean found;
	float Val;
	boolean Operator;
	
	Val=X.Val;
	Operator=X.Operator;
	
	if(custIsEmpty(L)){
		return Nil;
	}
	else{
		found=false;
		P=custFirst(L);
		while((P != Nil) && (!found)){
			if(custVal(P)==Val && custOperator(P)==Operator){
				found=true;
			}
			else{
				P = custNext(P);
			}
		}
		if(found){
			return P;
		}
		else{
			return Nil;
		}
	}
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void custInsVFirst (custList *L, custinfotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	custaddress P;
	
	P=custAlokasi(X);
	if(P!=Nil){
		if(custIsEmpty(*L)){
			custFirst(*L)=P;
			custLast(*L)=P;
		}
		else{
			custNext(P)=custFirst(*L);
			custPrev(custFirst(*L))=P;
			custFirst(*L)=P;
		}
	}
}
void custInsVLast (custList *L, custinfotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	custaddress P;
	
	P=custAlokasi(X);
	if(P != Nil){
		if(custIsEmpty(*L)){
			custFirst(*L)=P;
			custLast(*L)=P;
		}
		else{
			custPrev(P)=custLast(*L);
			custNext(custLast(*L))=P;
			custLast(*L)=P;
		}
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void custDelVFirst (custList *L, custinfotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	*X=custInfo(custFirst(*L));
	if(custNext(custFirst(*L)) == Nil){
		custFirst(*L)=Nil;
		custLast(*L)=Nil;
	}
	else{
		custPrev(custNext(custFirst(*L))) = Nil;
		custFirst(*L)=custNext(custFirst(*L));
	}
}
void custDelVLast (custList *L, custinfotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	*X=custInfo(custLast(*L));
	if(custNext(custFirst(*L)) == Nil){
		custFirst(*L)=Nil;
		custLast(*L)=Nil;
	}
	else{
		custNext(custPrev(custLast(*L)))=Nil;
		custLast(*L)=custPrev(custLast(*L));
	}
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void custInsertFirst (custList *L, custaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	if(custIsEmpty(*L)){
		custFirst(*L)=P;
		custLast(*L)=P;
	}
	else{
		custNext(P)=custFirst(*L);
		custPrev(custFirst(*L))=P;
		custFirst(*L)=P;
	}
}
void custInsertLast (custList *L, custaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	if(custIsEmpty(*L)){
		custFirst(*L)=P;
		custLast(*L)=P;
	}
	else{
		custPrev(P)=custLast(*L);
		custNext(custLast(*L))=P;
		custLast(*L)=P;
	}
}
void custInsertAfter (custList *L, custaddress P, custaddress Prec)
/* I.S. Prec pastilah elemen list; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	custaddress PTemp;
	
	if(Prec==custFirst(*L)){
		custNext(P)=custNext(Prec);
		custPrev(P)=Prec;
		if(custNext(Prec)!=Nil){
			custPrev(custNext(Prec))=P;
		}
		custNext(Prec)=P;
	}
	else if(Prec==custLast(*L)){
		custInsertLast(L,P);
	}
	else{
		PTemp=custFirst(*L);
		while(PTemp != Prec){
			PTemp=custNext(PTemp);
		}
		/*PTemp==Prec*/
		custNext(P)=custNext(PTemp);
		custPrev(P)=PTemp;
		custPrev(custNext(PTemp))=P;
		custNext(PTemp)=P;
	}
}
void custInsertBefore (custList *L, custaddress P, custaddress Succ)
/* I.S. Succ pastilah elemen list; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */
{
	custaddress PTemp;
	
	if(Succ==custFirst(*L)){
		custInsertFirst(L,P);
	}
	else if(Succ==custLast(*L)){
		custNext(P)=Succ;
		custPrev(P)=custPrev(Succ);
		if(custPrev(Succ) != Nil){
			custNext(custPrev(Succ)) = P;
		}
		custPrev(Succ)=P;
	}
	else{
		PTemp=custFirst(*L);
		while(PTemp != Succ){
			PTemp=custNext(PTemp);
		}
		/*PTemp == Succ*/
		custNext(P)=PTemp;
		custPrev(P)=custPrev(PTemp);
		custNext(custPrev(PTemp))=P;
		custPrev(PTemp)=P;
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void custDelFirst (custList *L, custaddress *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = custFirst(*L);
	if(custNext(custFirst(*L)) == Nil){
		custFirst(*L)=Nil;
		custLast(*L)=Nil;
	}
	else{
		custPrev(custNext(custFirst(*L)))=Nil;
		custFirst(*L)=custNext(custFirst(*L));
	}
}
void custDelLast (custList *L, custaddress *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
{
	*P=custLast(*L);
	if(custPrev(custLast(*L))==Nil){
		custFirst(*L)=Nil;
		custLast(*L)=Nil;
	}
	else{
		custNext(custPrev(custLast(*L)))=Nil;
		custLast(*L)=custPrev(custLast(*L));
	}
}
void custDelP (custList *L, custinfotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan custVal(P)=X  */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	custaddress P;
	boolean found;
	float Val;
	boolean Operator;
	
	Val=X.Val;
	Operator=X.Operator;
	
	if(!custIsEmpty(*L)){
		found=false;
		P=custFirst(*L);
		while((P != Nil)&&(!found)){
			if(custVal(P)==Val && custOperator(P)==Operator){
				found=true;
			}
			else{
				P=custNext(P);
			}
		}
		/*P==Nil or found*/
		if(found){
			if((custFirst(*L)==P)&&(custLast(*L)==P)){
				custFirst(*L)=Nil;
				custLast(*L)=Nil;
				custDealokasi(P);
			}
			else if(custFirst(*L)==P){
				custFirst(*L)=custNext(P);
				custPrev(custNext(P))=Nil;
				custDealokasi(P);
			}
			else if(custLast(*L)==P){
				custLast(*L)=custPrev(P);
				custNext(custPrev(P))=Nil;
				custDealokasi(P);
			}
			else{
				custNext(custPrev(P))=custNext(P);
				custPrev(custNext(P))=custPrev(P);
				custDealokasi(P);
			}
		}
	}
}
void custDelAfter (custList *L, custaddress *Pdel, custaddress Prec)
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel=custNext(Prec);
	if(custNext(Prec) != Nil){
		if(custNext(custNext(Prec)) != Nil){
			custPrev(custNext(custNext(Prec))) = Prec;
		}
		else{
			custLast(*L) = Prec;
		}
		custNext(Prec)=custNext(custNext(Prec));
	}
}
void custDelBefore (custList *L, custaddress *Pdel, custaddress Succ)
/* I.S. List tidak kosong. Succ adalah anggota list. */
/* F.S. Menghapus Prev(Succ): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel=custPrev(Succ);
	if(custPrev(Succ) != Nil){
		if(custPrev(custPrev(Succ)) != Nil){
			custNext(custPrev(custPrev(Succ))) = Succ;
		}
		else{
			custFirst(*L) = Succ;
		}
		custPrev(Succ) = custPrev(custPrev(Succ));
	}
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void custPrintForward (custList L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	custaddress P;
	boolean first;
	printf("[");
	first = true;
	P = custFirst(L);
	while(P != Nil){
		if(first){
			first=false;
			printf("%f",custVal(P));
		}
		else{
			printf(",%f",custVal(P));
		}
		P=custNext(P);
	}
	printf("]");
}
void custPrintBackward (custList L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizontal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	custaddress P;
	boolean first;
	printf("[");
	first = true;
	P = custLast(L);
	while(P != Nil){
		if(first){
			first=false;
			printf("%f", custVal(P));
		}
		else{
			printf(",%f",custVal(P));
		}
		P= custPrev(P);
	}
	printf("]");
}


