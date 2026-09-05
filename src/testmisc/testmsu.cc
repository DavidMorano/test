/* testmsu SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"msuclients.h"


#define	VARDEBUGFNAME	"TESTMSU_DEBUGFILE"
#define	VARDEBUGFD1	"TESTMSU_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#ifndef	VARPRLOCAL
#define	VARPRLOCAL	"LOCAL"
#endif

#define	PRLOCAL		"/usr/add-on/local"
#define	TO_MSU		10

/* exported subroutines */

int main()
{
	MSUCLIENTS	mc ;
	FILE		*ofp = stdout ;
	int		rs ;
	int		to = TO_MSU ;
	cchar	*pr ;
	cchar		*cp ;

#if	CF_DEBUG || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	if ((pr = getenv(VARPRLOCAL)) == NULL)
		pr = PRLOCAL ;

/* object, program-root, req-filename, time-out */

	if ((rs = msuclients_open(&mc,pr,NULL,to)) >= 0) {
	    fprintf(ofp,"main: msuclients_init() rs=%d\n",rs) ;
	    rs = msuclients_status(&mc) ;
	    fprintf(ofp,"main: msuclients_status() rs=%d\n",rs) ;
	    msuclients_close(&mc) ;
	} /* end if (msuclients) */

#if	(CF_DEBUG || CF_DEBUG)
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


