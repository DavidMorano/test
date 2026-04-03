/* testmodule SUPPORT (testmodule) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |hostequiv(3dam)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 2026-03-30, David A-D- Morano
	I just saw that there are tests for the GNU GLIB version
	of their various |strto{x}(3c)| subroutines.  I thought
	that it was high time (after all of these years) to see
	if my own versions of these subroutines (specifically
	my look-alikes for |strtol(3c)| and |strtoul(3c)|) can
	pass those tests.

*/

/* Copyright © 2026 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testmodule

	Description:

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdint>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usysflag.h>		/* |usysflag(3u)| */
#include	<stdintx.h>
#include	<prognamevar.hh>
#include	<localmisc.h>		/* |MAXPATHLEN| */
#include	<dprintf.hh>		/* debugging */

import testmod ;

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cbool		f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
    	prognamevar	progname(argc,argv,envv) ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		c = 0 ;
	DPRINTF("ent\n") ;
	printf("%s: ent\n",ccp(progname)) ;
	{
	    	printname() ;
	}
	DPRINTF("ret rs=%d c=%d\n",rs,c) ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


