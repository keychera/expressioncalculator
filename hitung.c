#include "header_dir/hitung.h"
#include "header_dir/mystring.h"
#include "header_dir/customlistdp.h"
#include <stdio.h>
#include <stdlib.h>

boolean noBracket(char *inp){
	char *s = &inp[0];
	boolean bracketExist = false;
	while ((!bracketExist) && (*s != '\000')) {
		bracketExist = (*s == '(');
		s++;
	} 
	return !bracketExist;
}

char* debracketize(char *inp){
	char *out = (char*) malloc(mystrlen(inp));
	mystrcpy(out,"");
	if (noBracket(inp)) {
		if(mystrlen(inp) > 0)
			sprintf(out,"%f",HitungEkspresi(inp));
	} else {
		char *pt = &inp[0];
		char *pass = (char*) malloc(mystrlen(inp));
		char *passO = (char*) malloc(2);
		int i = 0;
		
		Stack bracket;
		CreateEmptyStack(&bracket);
		Push(&bracket,'z');
		infotypeSt dummy;
		
		boolean flagCalculate = false;
		boolean flagOperator = false;
		
		while (*pt != '\000') {
			switch (*pt) {
				case '(':
						if (InfoTop(bracket) == 'b') {
							pass[i] = *pt;
							i++;
						}
						Push(&bracket,'b');
					break;
				case ')':
						Pop(&bracket,&dummy);
						if (InfoTop(bracket) == 'z'){
							flagCalculate = true;
						} else {
							pass[i] = *pt;
							i++;
						}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
						if (InfoTop(bracket) == 'z') {
							if (*(pt+1) == '('){
								flagCalculate = true;
								flagOperator = true;
								passO[0] = *pt;
								passO[1] = '\000';
							} else if (*(pt-1) == ')') {
								flagOperator = true;
								passO[0] = *pt;
								passO[1] = '\000';
							} else {
								pass[i] = *pt;
								i++;
							}
						} else {
							pass[i] = *pt;
							i++;
						}
					break;
				default:
					pass[i] = *pt;
					i++;
					if (*(pt+1) == '\000')
						flagCalculate = true;
			}
			if ((flagCalculate) || (flagOperator)) {
				pass[i] = '\000';
				if (flagCalculate){
					char* in = (char*) malloc(mystrlen(inp));
					sprintf(in,"%f",HitungEkspresi(debracketize(pass)));
					mystrcat(out,in);
				}
				if (flagOperator)
					mystrcat(out,passO);
				i = 0;
				flagCalculate = false;
				flagOperator = false;
			}
			pt++;
		}
	}
	return out;
}

custList StringToList(char* S){
	int i,Limit;
	custList L;
	boolean Negative;
	custinfotype X;
	float Dec;
	
	custCreateEmpty(&L);
	
	Limit=mystrlen(S)-1;
	Negative=false;
	i=0;
	
	
	X.Operator=false;
	X.Val=0;
	if(S[i]=='-'){
		Negative=true;
		i++;
	}
	while(S[i]!='+' && S[i]!='-' && S[i]!='*' && S[i]!='/' && S[i]!='.' && i<=Limit){
		X.Val=(10*X.Val)+S[i]-'0';
		i++;
	}
	/*S[i]=='+' || S[i]=='-' || S[i]=='*' || S[i]=='/' || S[i]=='.' || i>Limit*/
	if(S[i]=='.'){
		i++;
		Dec=0.1;
		while(S[i]!='+' && S[i]!='-' && S[i]!='*' && S[i]!='/' && i<=Limit){
			X.Val=X.Val+((S[i]-'0')*Dec);
			Dec=Dec/10;
			i++;
		}
	}
	if(Negative){
		X.Val=(-1)*X.Val;
		Negative=false;
	}
	custInsVLast(&L,X);
	
	while(i<=Limit){
		X.Operator=true;
		X.Val=S[i];
		custInsVLast(&L,X);
		i++;
		
		X.Operator=false;
		X.Val=0;
		if(S[i]=='-'){
			Negative=true;
			i++;
		}
		while(S[i]!='+' && S[i]!='-' && S[i]!='*' && S[i]!='/' && S[i]!='.' && i<=Limit){
			X.Val=(10*X.Val)+S[i]-'0';
			i++;
		}
		/*S[i]=='+' || S[i]=='-' || S[i]=='*' || S[i]=='/' || i>Limit*/
		if(S[i]=='.'){
			i++;
			Dec=0.1;
			while(S[i]!='+' && S[i]!='-' && S[i]!='*' && S[i]!='/' && i<=Limit){
				X.Val=X.Val+((S[i]-'0')*Dec);
				Dec=Dec/10;
				i++;
			}
		}
		if(Negative){
			X.Val=(-1)*X.Val;
			Negative=false;
		}
		custInsVLast(&L,X);
	}
	
	return L;
}

float HitungEkspresi(char* S){
	custList L;
	custinfotype X;
	custaddress P;
	float Hasil;
	
	L=StringToList(S);
	
	/*Perkalian*/
	X.Operator=true;
	X.Val='*';
	P=custSearch(L,X);
	while(P!=Nil){
		Hasil=custVal(custPrev(P))*custVal(custNext(P));
		custVal(custNext(P))=Hasil;
		custPrev(custNext(P))=custPrev(custPrev(P));
		if(custPrev(custNext(P))!=Nil){
			custNext(custPrev(custNext(P)))=custNext(P);
		}
		else{
			custFirst(L)=custNext(P);
		}
		custDealokasi(custPrev(P));
		custDealokasi(P);
		
		X.Operator=true;
		X.Val='*';
		P=custSearch(L,X);
	}
	/*Pembagian*/
	X.Operator=true;
	X.Val='/';
	P=custSearch(L,X);
	while(P!=Nil){
		Hasil=custVal(custPrev(P))/custVal(custNext(P));
		custVal(custNext(P))=Hasil;
		custPrev(custNext(P))=custPrev(custPrev(P));
		if(custPrev(custNext(P))!=Nil){
			custNext(custPrev(custNext(P)))=custNext(P);
		}
		else{
			custFirst(L)=custNext(P);
		}
		custDealokasi(custPrev(P));
		custDealokasi(P);
		
		X.Operator=true;
		X.Val='/';
		P=custSearch(L,X);
	}
	/*Penjumlahan*/
	X.Operator=true;
	X.Val='+';
	P=custSearch(L,X);
	while(P!=Nil){
		Hasil=custVal(custPrev(P))+custVal(custNext(P));
		custVal(custNext(P))=Hasil;
		custPrev(custNext(P))=custPrev(custPrev(P));
		if(custPrev(custNext(P))!=Nil){
			custNext(custPrev(custNext(P)))=custNext(P);
		}
		else{
			custFirst(L)=custNext(P);
		}
		custDealokasi(custPrev(P));
		custDealokasi(P);
		
		X.Operator=true;
		X.Val='+';
		P=custSearch(L,X);
	}
	/*Pengurangan*/X.Operator=true;
	X.Val='-';
	P=custSearch(L,X);
	while(P!=Nil){
		Hasil=custVal(custPrev(P))-custVal(custNext(P));
		custVal(custNext(P))=Hasil;
		custPrev(custNext(P))=custPrev(custPrev(P));
		if(custPrev(custNext(P))!=Nil){
			custNext(custPrev(custNext(P)))=custNext(P);
		}
		else{
			custFirst(L)=custNext(P);
		}
		custDealokasi(custPrev(P));
		custDealokasi(P);
		
		X.Operator=true;
		X.Val='-';
		P=custSearch(L,X);
	}
	return custVal(custFirst(L));
}

