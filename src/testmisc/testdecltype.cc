/* testdecltype SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test getting the size of various types (using |sizeof()|) */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdarg>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;
	if (rs >= 0) {
	    const int i = 1 ;
	    const int *p{} ;
	    decltype (*p) j = 2 ;
	    printf("i=%d j=%d\n",i,j) ;
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


