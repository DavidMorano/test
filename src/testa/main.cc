/* main (TESTA) */
/* lang=C++20 */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstring>
#include	<cstdio>
#include	<iostream>
#include	<usystem.h>
#include	<mallocstuff.h>
#include	<localmisc.h>

/* local defines */

#define	NI	20
#define	NJ	2

/* forward references */

static int sub(int (*)[NJ],int,int) ;

/* local variables */

constexpr cchar		str[] = "hello" ;

/* exported subroutines */

int main() {
	int		a[NI][NJ] ;
	int		typesize ;
	int		sz ;
	int		n, i, j ;
	int		*p ;

	sz = sizeof(str) ;
	printf("sizeof=%u\v",sz) ;

	n = NI * NJ ;
	typesize = sizeof(uint (*)[NJ]) ;

	printf("1 typesize=%u\n",typesize) ;

	typesize = sizeof(char *) ;

	printf("2 typesize=%u\n",typesize) ;

#ifdef	COMMENT
	{
	    cchar	*(*keys)[NJ] ;
	    sz = n * typesize ;
	    (void) uc_malloc(sz,&keys) ;
	    memset(keys,0,sz) ;
	    printf("typesize=%u n=%u size=%u\n",typesize,n,sz) ;
	    keys[0][0] = "hello" ;
	    keys[0][1] = "there" ;
	    keys[1][0] = "good" ;
	    keys[1][1] = "bye" ;
	    for (i = 0 ; i < NJ ; i += 1) {
	        if (keys[i][0] != nullptr) {
	            printf("k=%s v=%s\n", keys[i][0],keys[i][1]) ;
	        }
	    } /* end for */
	} /* end block */
#endif /* COMMENT */

	sz = n * sizeof(int) ;
	memset(a,0,sz) ;

	p = (int *) a ;
	for (i = 0 ; i < n ; i += 1) {
		p[i] = i ;
	}

	for (i = 0 ; i < NI ; i += 1) {
	    for (j = 0 ; j < NJ ; j += 1) {
		printf("[%2d,%2d]=%d\n",i,j,a[i][j]) ;
	    }
	}

	sub(a,NI,NJ) ;

	return 0 ;
}
/* end subroutine (main) */

static int sub(int (*a)[2],int ni,int nj) {
	for (int i = 0 ; i < ni ; i += 1) {
	    for (int j = 0 ; j < nj ; j += 1) {
		printf("sub [%2d,%2d]=%d\n",i,j,a[i][j]) ;
	    }
	}
	return 0 ;
}
/* end subroutine (sub) */


