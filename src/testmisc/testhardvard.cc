/* main SUPPORT (test-harvard) */

#include	<stdio.h>

typedef unsigned int	uint ;

int main() {
    uint	a = (16 << 20) - (16 << 16) ;
    printf("%08x %d\n",a,a) ;
}


