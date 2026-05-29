/* testdiv SUPPORT (testdiv) */
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
#include	<cstddef>		/* CSTD |nullptr_t| */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cmath>			/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

using libu::cfdec ;			/* subroutine */

int main(int argc,con mainv argv,con mainv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
    	if (argc > 1) {
	    for (int ai = 1 ; ai < argc ; ++ai) {
		cchar *ap = argv[ai] ;
		if (*ap) {
	            if (ulong num ; (rs = cfdec(ap,-1,&num)) >= 0) {
	                ulong	den = argc ;
    	                ulong quo ;
	                int rem ;
	                quo = num / den ;
	                rem = int(num % den) ;
			printf("-\n") ;
	                printf("dividend=%lu\n",num) ;
	                printf("divisor=%lu\n",den) ;
	                printf("quo=%lu\n",quo) ;
	                printf("rem=%u\n",rem) ;
		    } /* end if (cfdec) */
		} /* end if (valid) */
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


