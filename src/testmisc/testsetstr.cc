/* testsetstr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* I test the SETSTR (a set of strings) object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory allocations */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"setstr.h"


#define	VARDEBUGFNAME	"TESTSETSTR_DEBUGFILE"
#define	VARDEBUGFD1	"TESTSETSTR_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"


/* external subroutines */


/* exported variables */


/* exported subroutines */

int main(int argc,cchar **argv,cchar **envv) {
	SETSTR		ss ;
	FILE		*ofp = stdout ;

#if	(CF_DEBUG || CF_DEBUG) && CF_DEBUGMALL
	uint		mo_start = 0 ;
#endif

	int		rs ;
	int		rs1 ;

#if	CF_DEBUG
	{
	    cchar		*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	        rs = debugopen(cp) ;
	        debugprintf("main: starting DFD=%d\n",rs) ;
	    }
	}
#endif /* CF_DEBUG */

#if	(CF_DEBUG || CF_DEBUG) && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	if (argc > 1) {
	    if ((rs = setstr_start(&ss)) >= 0) {
	        int	i ;
#if	CF_DEBUG
	debugprintf("testsetstr: insert1\n") ;
#endif
		if (rs >= 0) {
		    for (i = 1 ; i < argc ; i += 1) {
		        rs = setstr_add(&ss,argv[i],-1) ;
		        if (rs < 0) break ;
		    }
		}
#if	CF_DEBUG
	debugprintf("testsetstr: insert2\n") ;
#endif
		if (rs >= 0) {
		    for (i = 1 ; i < argc ; i += 1) {
		        rs = setstr_add(&ss,argv[i],-1) ;
		        if (rs < 0) break ;
		    }
		}
#if	CF_DEBUG
	debugprintf("testsetstr: retrieve\n") ;
#endif
		if (rs >= 0) {
		    SETSTR_CUR	c ;
		    if ((rs = setstr_curbegin(&ss,&c)) >= 0) {
			cchar	*cp ;
			while ((rs1 = setstr_curenum(&ss,&c,&cp)) >= 0) {
	
#if	CF_DEBUG
			debugprintf("testsetstr: s=%s\n",cp) ;
#endif
	    		    fprintf(ofp,"main: s=%s\n",cp) ;

			    if (rs < 0) break ;
			} /* end while */
			if ((rs >= 0) && (rs1 != SR_NOTFOUND)) rs = rs1 ;
			rs1 = setstr_curend(&ss,&c) ;
			if (rs >= 0) rs = rs1 ;
		    }
		}
		if (rs >= 0) {
			cchar	*cp = "one" ;
			if ((rs = setstr_already(&ss,cp,-1)) > 0) {
	    		    fprintf(ofp,"main: already s=%s\n",cp) ;
			}
		}
	        rs1 = setstr_finish(&ss) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (setstr) */
	} /* end if (arguments) */

#if	CF_DEBUG
	debugprintf("main: ret rs=%d\n",rs) ;
#endif

#if	(CF_DEBUG || CF_DEBUG) && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif /* CF_DEBUGMALL */

#if	(CF_DEBUG || CF_DEBUG)
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


