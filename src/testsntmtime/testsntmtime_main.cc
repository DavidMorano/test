/* testsntmtime_main SUPPORT (testsntmtime) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test |sntmtime(3uc)| */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<tmtime.hh>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"sntmtime.h"

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/cmdutils.ccm"

import libutil ;			/* |lenstr(3u)| */
import cmdutils ;			/* |optval(3uc)| */

/* local defines */

#define	VARDEBUGFNAME	"TESTSNTMTIME_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) noex {
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;

#if	CF_DEBUG
	if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	    debugopen(cp) ;
	    DEBUGPRINTF("starting dfn=%s\n",cp) ;
	}
#endif /* CF_DEBUG */

	if (rs >= 0) {
	    custime dt = time(nullptr) ;
	    if (tmtime tmt ; (rs = tmtime_timelocal(&tmt,dt)) >= 0) {
	        cint	tlen = TIMEBUFLEN ;
	        char	tbuf[TIMEBUFLEN+1] ;
	        cchar	*fmt ;
                 for (int ai = 1 ; ai < argc ; ai += 1) {
                     fmt = argv[ai] ;
                     rs = sntmtime(tbuf,tlen,&tmt,fmt) ;
                     if (rs >= 0) {
                         printf("%s\n",tbuf) ;
                     }
                     if (rs < 0) break ;
                 } /* end for */
	    } /* end if (tmtime_timelocal) */
	} /* end if (ok) */
	debugclose() ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (exit-return) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


