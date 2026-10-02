/* testchar */

#include	<iostream>
#include	<cstdio>

static cchar	a[] = "hello world!" ;

int main() {
	cint	sz = sizeof(a) ;
	printf("a=%s sz=%u\n",a,sz) ;
}


