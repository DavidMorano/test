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
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<cmath>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usupport.h>
#include	<localmisc.h>

using libu::cfdec ;			/* subroutine */

int main(int argc,mainv argv,mainv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
    	if (argc > 1) {
	    for (int i = 1 ; i < argc ; ++i) {
		cchar *ap = argv[i] ;
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
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


