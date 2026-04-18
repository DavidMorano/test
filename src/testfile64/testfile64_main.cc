/* testfile64_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |uc_truncate(3uc)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testfile64

	Description:
	Test the |uc_truncate(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<ucfileop.h>
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
	    rs = uc_truncate("here",0z) ;
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


