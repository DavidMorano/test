/* testtmtime_main SUPPORT (testtmtime) */
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
#include	<sntmtime.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/cmdutils.ccm"

import libutil ;			/* |lenstr(3u)| */
import cmdutils ;			/* |optval(3uc)| */

/* local defines */

#define	VARDEBUGFNAME	"TESTTMTIME_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int procargs	(int,con mainv) noex ;
local int procvals	() noex ;


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) noex {
	[[maybe_unused]] cnullptr	np{} ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	    debugopen(cp) ;
	    DEBUGPRINTF("starting dfn=%s\n",cp) ;
	} /* end if (debugopen) */
	if ((rs >= 0) && (argc > 1)) {
	    rs = procargs(argc,argv) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = procvals() ;
	    DEBUGPRINTF("procvals() rs=%d\n",rs) ;
	} /* end if (ok) */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	debugclose() ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (exit-return) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procargs(int argc,con mainv argv) noex {
	custime		dt = getustime ;
	int		rs ;
	if (tmtime tmt ; (rs = tmt.timelocal(dt)) >= 0) {
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
	return rs ;
} /* end subroutine (procargs) */

local int procvals() noex {
    	custime		dt = getustime ;
	cint		tlen = TIMEBUFLEN ;
    	int		rs = SR_OK ;
	char		tbuf[TIMEBUFLEN + 1] ;
	printf(" dt=%ld\n",dt) ;
	printf("time-loc » %s «\n",timestr_edate(dt,tbuf)) ;
	if (tmtime tmd ; (rs = tmd.timelocal(dt)) >= 0) {
	    printf("loc-off           isdst=%d\n",tmd.isdst) ;
	    printf("loc-off (secs west GMT)=%d\n",tmd.gmtoff) ;
	    cchar *fmt = "%y:%m:%d %H%M:%S $Z %O %z" ;
	    if ((rs = sntmtime(tbuf,tlen,&tmd,fmt)) >= 0) {
	        if (time_t ntv ; (rs = tmd.mktime(&ntv)) >= 0) {
		    printf("ntv=%ld\n",ntv) ;
	            printf("time-loc » %s «\n",timestr_edate(ntv,tbuf)) ;
		    ntv += (3600) ;
	            printf("time-rem » %s «\n",timestr_edate(ntv,tbuf)) ;
		    {
			tmd.gmtoff += (1 * 3600) ;
	        	if (time_t rtv ; (rs = tmd.mktime(&rtv)) >= 0) {
	            	    printf("time-rem » %s «\n",
				   timestr_edate(rtv,tbuf)) ;
			} /* end if (tmtime_mktime) */
		    } /* end block */
	        } /* end if (tmtime_mktime) */
	    } /* end if (sntmtime) */
	} /* end if (tmtime) */
    	return rs ;
} /* end subroutine (procvals) */


