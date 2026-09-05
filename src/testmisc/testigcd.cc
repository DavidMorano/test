/* testigcd SUPPORT (testigcd) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	The the |igcd(3dam)| function.


*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>


/* local defines */

#ifndef	DIGBUFLEN
#define	DIGBUFLEN	40
#endif

#define	MAXTRY		20		/* maximum value for each element */

#define	VARDEBUGFNAME	"TESTISHEX_DEBUGFILE"


/* external subroutines */

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* local variables */


/* exported subroutines */


int main(int argc,cchar **argv,cchar **envv)
{
	int		rs = SR_OK ;
	int		ex = 0 ;
	int		maxtry = MAXTRY ;
	int		i, j ;
	cchar		*cp ;

#if	CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	if ((rs >= 0) && (argc > 1)) {
	    if ((argv[1] != NULL) && (argv[1][0] != '\0')) {
		cchar	*ap = argv[1] ;
		rs = optvalue(ap,-1) ;
		maxtry = rs ;
	    }
	}

#if	CF_DEBUG
	debugprintf("main: maxtry=%u\n",maxtry) ;
#endif

	if (rs >= 0) {
	    for (i = 1 ; i < maxtry ; i += 1) {
	        for (j = 1 ; j < maxtry ; j += 1) {
		    cint	g = igcd(i,j) ;
		    printf("g(%2u,%2u)=%u\n",i,j,g) ;
	        }
	    }
	}

#if	CF_DEBUG
	debugprintf("main: done rs=%d\n",rs) ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

	if (rs < 0) ex = 1 ;
	return ex ;
} /* end subroutine (main) */


