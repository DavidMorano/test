/* testarray SUPPORT (testarray) */
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
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usupport.h>
#include	<localmisc.h>

using libu::cfdec ;			/* subroutine */

cint		rlen = 3 ;

constexpr int 	arrvals[rlen][2] = {
    { 0, 1 },
    { 2, 3 },
    { 4, 5 }
} ; /* end array */

int main(int argc,mainv,mainv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
    	if (rs >= 0) {
	    {
		for (int i = 0 ; i < rlen ; i += 1) {
		    for (int j = 0 ; j < 2 ; j += 1) {
	                printf(" %2d",arrvals[i][j]) ;
		    }
	            printf("\n") ;
	        } /* end for */
	    }
	    {
	        cint n = (rlen * 2) ;
	        int *ip = intp(arrvals) ;
	        for (int i = 0 ; i < n ; i += 1) {
	            printf(" %2d",ip[i]) ;
	        } /* end for */
	        printf("\n") ;
	    }
	} /* end if (OK) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


