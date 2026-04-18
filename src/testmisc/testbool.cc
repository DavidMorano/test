/* testbool SUPPORT (testbool) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test boolean operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This tests some boolean operations.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


int main(int,mainv,mainv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
	{
	    cbool f1 = true ;
	    cbool f2 = true ;
	    bool f ;
	    f = f1 ^ f2 ;
	    printf("res=%u\n",uint(f)) ;
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


