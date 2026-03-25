/* testarith_main SUPPORT (Test-Arith) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test arithmetic */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<syncstream>		/* |osyncstream(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


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

int main(int,mainv,mainv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	{
	    uint	r, co ;
	    cchar	*fmt = 
	    	        "%02x %02x = %02x + %02x %02x\n" ;
	    printf("co  r    j    i ci\n") ;
	    for (uint ci = 0 ; ci < 2 ; ci += 1) {
	        for (uint i = 0 ; i < 4 ; i += 1) {
	            for (uint j = 0 ; j < 4 ; j += 1) {
		        r = j + i + ci ;
		        co = (r >> 2) ;
	    	        printf(fmt,co,(r & 3),j,i,ci) ;
		    }
	        }
	    }
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


