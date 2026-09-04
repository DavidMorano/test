/* testlookup SUPPOET */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* non-switchable debug print-outs */
#define	CF_DEBUG	1		/* switchable at invocation */
#define	CF_DEBUGMALL	1		/* debug memory allocation */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstdio>
#include	<usystem.h>
#include	<bufsizeget.h>
#include	<hostent.h>
#include	<localmisc.h>

#ifndef	VARDEBUGFNAME
#define	VARDEBUGFNAME	"TESTGETHOST_DEBUGFILE"
#endif

#if	CF_DEBUG || CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,cchar **argv,cchar **envv) {
	int		rs = SR_OK ;
	cchar	*cp ;

#if	CF_DEBUG || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	if (argc > 0) {
	    HOSTENT	he ;
	    cint	helen = bufsizeget(bufsizeget_he) ;
	    char	*hebuf ;
	    if ((rs = uc_malloc((helen+1),&hebuf)) >= 0) {
	    	int	ai ;
	        for (ai = 1 ; ai < argc ; ai += 1) {
	            cchar	*name = argv[ai] ;
	            if (name[0] != '\0') {
	                rs = uc_gethostbyname(name,&he,hebuf,helen) ;
		        printf("rs=%d \n",rs) ;
	            }
	        } /* end for */
		uc_free(hebuf) ;
	    } /* end if (memory-allocation) */
	} /* end if (positive) */

#if	(CF_DEBUG || CF_DEBUG)
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */

