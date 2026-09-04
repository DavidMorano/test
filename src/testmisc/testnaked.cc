/* testnaked SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debugging memory-allocations */
#define	CF_DEBUGN	0		/* special debugging */
#define	CF_UGETPID	1		/* |ugetpid(3uc)| */
#define	CF_TIME		1		/* |time(3c)| */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdarg>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<ugetpid.h>
#include	<localmisc.h>


#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif

#define	VARDEBUGFNAME	"TESTNAKED_DEBUGFILE"

#define	NDF		"testnaked.deb"

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif

#if	CF_DEBUGN
extern int	nprintf(cchar *,cchar *,...) ;
#endif


/* forward references */

/* exported subroutines */

/* ARGSUSED */
int main(int argc,con mainv argv,con mainv envv) {
	FILE		*ofp = stdout ;

#if	CF_DEBUG && CF_DEBUGMALL
	uint		mo_start = 0 ;
#endif

	cint	ps = getpagesize() ;
	int		rs = SR_OK ;
	int		rs1 ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	        rs = debugopen(cp) ;
	        debugprintf("main: starting fd=%d\n",rs) ;
	    }
	}
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

#if	CF_DEBUGN
	nprintf(NDF,"main: inside\n") ;
#endif

	fprintf(ofp,"ps=%u\n",ps) ;

#if	CF_UGETPID
	{
	    cint	pid = ugetpid() ;
	    fprintf(ofp,"pid=%d\n",pid) ;
	}
#endif /* CF_UGETPID */

#if	CF_TIME
	{
	    const time_t	dt = time(NULL) ;
	    fprintf(ofp,"dt=%u\n",dt) ;
	}
#endif /* CF_TIME */

	fflush(ofp) ;

#if	CF_DEBUG
	debugprintf("main: out rs=%d\n",rs) ;
#endif

#if	CF_DEBUGN
	nprintf(NDF,"main: leaving\n") ;
#endif

#if	CF_DEBUG && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


/* local subroutines */


