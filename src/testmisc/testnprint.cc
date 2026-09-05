/* testnprint SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1


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
#include	<localmisc.h>		/* LIBU |COLUMNS| */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#define	VARDEBUGFNAME	"TESTNPRINT_DEBUGFILE"

#define	NDF		"testnprint.deb"


int main(int argc,con mainv argv,con mainv envv) {
	cint		cols = COLUMNS ;
	int		rs ;
	cchar		*msg = "here/nis/hello" ;

#if	CF_DEBUG
	cchar		*cp ;
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	rs = nprintf(NDF,"main: msg=%s\n",msg) ;

#if	CF_DEBUG
	    debugprintf("main: nprintf() rs=%d\n",rs) ;
#endif

	rs = nprinthexblock(NDF,"main: ",cols,msg,-1) ;

#if	CF_DEBUG
	    debugprintf("main: nprinthexblock() rs=%d\n",rs) ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif
} /* end subroutine (main) */


