/* testprogpath_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |prgetprgpath(3pr)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"testprgetprogpath_config.h"


#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* exported variables */


/* exported subrutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	cchar		*pr = "/usr/add-on/local" ;
	cchar		*pn = "imail" ;
	char		progfname[MAXPATHLEN+1] ;
	(void) envv ;

#if	CF_DEBUG 
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    DEBUGPRINTF("starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	rs = prgetprogpath(pr,progfname,pn) ;

	printf("rs=%d progfname=%s\n",rs,progfname) ;

	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DEBUGPRINTF("ret rs=%d ex=%d\b",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


