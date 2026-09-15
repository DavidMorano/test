/* testgetexec_main SUPPORT (testgetexec) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
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

int main(int argc,con mainv argv,con mainv envv) {
    	cnullptr	np{} ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 0) {
	cchar		*cp = argv[0] ;
	(void) envv ;
	printf("arg0=%s\n",
		(cp != np) ? cp : "*NA*") ;

	cp = getenv("_") ;

	printf("_=%s\n",
		(cp != np) ? cp : "*NA*") ;

	cp = (char *) getexecname() ;

	printf("execname=%s\n",
		(cp != np) ? cp : "*NA*") ;
	} /* end if (arguments) */
	return ex ;
} /* end subroutine (main) */


