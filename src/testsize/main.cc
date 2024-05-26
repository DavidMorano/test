/* main SUPPORT (testsize) */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>



struct testsize {
	uint	a ;
	uint	b : 4 ;
	uint	c : 1 ;
} ;

struct structshort {
	short	a ;
} ;

struct structbits {
	short	ch ;
	uint	a:1 ;
	uint	b:1 ;
} ;


int main() {
	int	sz ;
	sz = sizeof(struct testsize) ;
	printf("sizeof testsize=%d\n",sz) ;
	sz = sizeof(structshort) ;
	printf("sz=%d\n",sz) ;
	sz = sizeof(structbits) ;
	printf("sz=%d\n",sz) ;
}


