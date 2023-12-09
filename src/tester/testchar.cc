/* testchar */

#include	<iostream>
#include	<cstdio>

static const char	a[] = "hello world!" ;

int main() {
	const int	sz = sizeof(a) ;
	printf("a=%s sz=%u\n",a,sz) ;
}


