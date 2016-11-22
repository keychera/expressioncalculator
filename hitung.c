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

char* debracketize(char *inp,char opPass){
	char *out = (char*) malloc(mystrlen(inp));
	if (noBracket(inp)) {
		if(mystrlen(inp) > 0)
			sprintf(out,"%f",HitungEkspresi(inp,opPass));
	} else {
		int i = 0;infotypeSt dummy;
		out = (char*) malloc(mystrlen(inp));
		
		char *pass = (char*) malloc(mystrlen(inp));
		char *pt = &inp[0];
		
		Stack bracket;
		CreateEmptyStack(&bracket);
		Push(&bracket,'z');
		
		boolean flagForCalculate = false;
		char operatorPass = '+';
		char operatorPrec = '+';
		while (*pt != '\000') {
			switch(*pt) {
				case '(' :
						if (InfoTop(bracket) != 'z') {
							pass[i] = *pt;
							i++;						
						}
						Push(&bracket,'b');
					break;
				case ')' :
						Pop(&bracket,&dummy);
						if (InfoTop(bracket) == 'z') {
							flagForCalculate = true;						
						} else {
							pass[i] = *pt;
							i++;
						}
					break;
				case '+' :
				case '*' :
				case '/' :
				case '-' :
						pass[i] = *pt;
						i++;
					if (*(pt+1) == '(') {
						operatorPrec =  operatorPass ;
						operatorPass = *pt;
						flagForCalculate = true;
					}
						break;
				default:
					pass[i] = *pt;
					i++;
						
			}
			pt++;
			if (flagForCalculate) {
				pass[i] = '\000';
				mystrcat(out,debracketize(pass,operatorPrec));
				i = 0;
				flagForCalculate = false;
			}
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

float HitungEkspresi(char* S,char operator){
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
	//key edit
	float out;
	switch(operator){
		case '+':
		case '*':
		case '/': out = custVal(custFirst(L)); break;
		case '-': out = (-1*custVal(custFirst(L))); break;
	}
	return out;
}

