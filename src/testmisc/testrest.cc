/* testrest SUPPORT */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debugging memory-allocations */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdarg>
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<exitcodes.h>
#include	<localmisc.h>

#ifndef	UEBUFLEN
#define	UEBUFLEN	UTMPACCENT_BUFLEN
#endif

#define	VARDEBUGFNAME	"TESTREST_DEBUGFILE"


#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* forward references */

local int fileclear(int) ;


/* exported subroutines */

int main(int argc,cchar **argv,cchar **envv)
{

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs = SR_OK ;
	int	rs1 ;
	int	ex = EX_INFO ;
	int	n = 1000 ;


#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	if (argv != NULL) {
	    int		asize ;
	    int		ai ;
	    int		i ;
	    int		ac = MIN(argc,2) ;
	    cchar	**av ;
	    asize = ((ac+1)*sizeof(cchar *)) ;
	    if ((rs = uc_malloc(asize,&av)) >= 0) {

		av[0] = "rest" ;
		for (ai = 1 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
		    av[ai] = argv[ai] ;
		}
		av[ai] = NULL ;

	        for (i = 0 ; i < n ; i += 1) {
		    fileclear(2) ;

		    ex = p_rest(ai,av,envv,NULL) ;

		    if (ex != EX_OK) break ;
	        } /* end for */

#if	CF_DEBUG
	        debugprintf("main: while-out rs=%d\n",rs1) ;
#endif

	    } /* end if (memory-allocation) */

	} /* end if (argv) */

#if	CF_DEBUG
	debugprintf("main: all-out rs=%d\n",rs) ;
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

local int fileclear(int fd) {
	int	rs ;
	if ((rs = u_rewind(fd)) >= 0) {
	    rs = uc_ftruncate(fd,0z) ;
	}
	return rs ;
} /* end subroutine (fileclear) */


