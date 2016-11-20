#include "header_dir/lilfx.h"

int digit(int n){
//number of digit
	int ret;
	if ((n % 10) == n) {
		ret = 1;
	} else {
		ret = 1 + digit(n / 10);
	}
	return ret;
}

int abs(int n){
	if (n >= 0)
		return n;
	else
		return -n;
}

