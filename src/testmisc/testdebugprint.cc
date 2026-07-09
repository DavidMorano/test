/* testdebugprint SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |debugptinf(3debug)| subroutine and some friends */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#define	VARDEBUGFNAME	"TESTDEBUGPRINT_DEBUGFILE"


int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	cchar		*msg = "here\nis\033" ;

#if	CF_DEBUG
	if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	rs = debugprintf("main: msg=>%s<\n",msg) ;

	if (rs < 0) {
	    debugprintf("main: rs=%d\n",rs) ;
	}

#if	CF_DEBUG
	debugclose() ;
#endif

	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


