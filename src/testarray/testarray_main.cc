/* testarray_main SUPPORT (testarray) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test division */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This is test code for seeing how the compiler handles a
	combined division and module sequence.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

using libu::cfdec ;			/* subroutine */

cint		rlen = 3 ;

constexpr int 	arrvals[rlen][2] = {
    { 0, 1 },
    { 2, 3 },
    { 4, 5 }
} ; /* end array */

int main(int,con mainv,con mainv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
	if (rs >= 0) {
	    int x[4] = { 0, 1, 2, 3 } ;
	    {
		const caddr_t xp = caddr_t(&x) ;
		const size_t  xsz = sizeof(x) ;
		const caddr_t xpp = caddr_t(x + 1) ;
		const caddr_t xp_one = caddr_t(&x + 1) ;
		const caddr_t x0p = caddr_t(&x[0]) ;
		const caddr_t x1p = caddr_t(&x[1]) ;
		const caddr_t x2p = caddr_t(&x[2]) ;
		const caddr_t x3p = caddr_t(&3[x]) ;
		printf("xp= %16p\n",xp) ;
		printf("xsz=%lu\n",xsz) ;
		printf("xpp=%16p\n",xpp) ;
		printf("xpo=%16p\n",xp_one) ;
		printf("x0p=%16p\n",x0p) ;
		printf("x1p=%16p\n",x1p) ;
		printf("x2p=%16p\n",x2p) ;
		printf("x3p=%16p\n",x3p) ;
	    }
	} /* end if (ok) */
    	if (rs >= 0) {
		for (int i = 0 ; i < rlen ; i += 1) {
		    for (int j = 0 ; j < 2 ; j += 1) {
	                printf(" %2d",arrvals[i][j]) ;
		    } /* end for */
	            printf("\n") ;
	        } /* end for */
	} /* end if (ok) */
	if (rs >= 0) {
	        cint n = (rlen * 2) ;
	        int *ip = intp(arrvals) ;
	        for (int i = 0 ; i < n ; i += 1) {
	            printf(" %2d",ip[i]) ;
	        } /* end for */
	        printf("\n") ;
	} /* end if (OK) */
	if (rs >= 0) {
	    cpcchar a[] = { "one", "two", "three" } ;
	    for (cauto &e : a) {
		printf(" %s",e) ;
	    } /* end for */
	   printf("\n") ;
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


