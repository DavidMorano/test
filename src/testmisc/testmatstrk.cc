/* testmatstrk SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test the |matstrk(3c)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Decription:
	Test the |matstrk(3u)| subroutine.

	Usage:
	$ testmatstrk.x <environment-variable>

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<umatx.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif


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
	if (argc > 1) {
	    for (int ai = 1 ; ai < argc ; ai += 1) {
		ccharp sstr = argv[ai] ;
		printf("sstr=%s\n",sstr) ;
		if (int idx = matstrk(envv,sstr) ; idx >= 0) {
		    printf("mat %s\n",envv[idx]) ;
		} else {
		    printf("mat-no\n") ;
		} /* end if (matstrk) */
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


