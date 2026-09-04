/* testopendialer SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<filer.h>
#include	<localmisc.h>

#ifndef	UEBUFLEN
#define	UEBUFLEN	UTMPACCENT_BUFLEN
#endif

#ifndef FILER_RCNET
#define	FILER_RCNET	4		/* read-count for network */
#endif

#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif

#define	VARDEBUGFNAME	"TESTOPENDIALER_DEBUGFILE"

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* forward references */


/* exported variables */


/* exported subroutines */

int main(int argc,cchar **argv,cchar **envv) {

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs = SR_OK ;
	int	rs1 ;


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
	    cint	llen = LINEBUFLEN ;
	    int		ai ;
	    char	lbuf[LINEBUFLEN+1] ;
	    for (ai = 1 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
	        cchar	*fn = argv[ai] ;
	        cint	of = O_RDONLY ;
	        if ((rs = uc_open(fn,of,0666)) >= 0) {
	            cint	fo = (of | O_NETWORK) ;
	            int		fd = rs ;
	            if (filer b ; (rs = filer_start(&b,fd,0z,0,fo)) >= 0) {
	                cint	to = 5 ;
	                while ((rs = filer_read(&b,lbuf,llen,to)) > 0) {
	                    int	len = rs ;
	                    fbwrite(stdout,lbuf,len) ;
	                    if (rs < 0) break ;
	                } /* end while */
	                rs1 = filer_finish(&b) ;
			if (rs >= 0) rs = rs1 ;
	            } /* end if (filer) */
	            rs1 = u_close(fd) ;
		    if (rs >= 0) rs = rs1 ;
	        } else {
	            fbprintf(stdout,"not_found fn=%s (%d)\n",fn,rs) ;
	        }
	        if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */

#if	CF_DEBUG
	debugprintf("main: out rs=%d\n",rs) ;
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


