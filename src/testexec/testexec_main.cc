/* testexec_main SUPPORT (testexec) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test |execve(2)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testexec

	Description:
	This program tests the |execve(2)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usysflag.h>		/* LIBU |usysflag(3u)| */
#include	<prognamevar.hh>	/* LIBU */
#include	<shellunder.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |MAXPATHLEN| */


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

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 0) {
	    ccharp execname = argv[1] ;
	    rs = u_execve(execname,(argv + 2),envv) ;
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


