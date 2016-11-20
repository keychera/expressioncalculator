#include "header_dir/mystring.h"

int mystrlen(const char *str){
	int i = 0;
	while (str[i] != '\000') {
		i++;
	}
	return i;
}

char *mystrcpy(char *dest, const char *src){
	int i = 0;
	while (src[i] != '\000') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\000';
	return dest;
}

int mystrcmp(const char *str1, const char *str2){
	int i = 0;
	int n = 0;
	boolean check = true;
	while (check) {
		n += (str1[i] - str2[i]);
		check = ((str1[i] != '\000') && (str2[i] != '\000') && (n == 0));
		i++;
	}
	return n;
}

void myprintstr(const char *str){
	int i = 0;
	while(str[i] != '\000') {
		printf("%c",str[i]);
		i++;
	}
}
