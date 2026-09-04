/* testsendfile */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstdio>
#include	<usystem.h>
#include	<opendial.h>
#include	<localmisc.h>

#define	VARDEBUGFNAME	"TESTSENDFILE_DEBUGFILE"

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


local int procfile(int,cchar *) ;

int main(int argc,cchar **argv,cchar **envv) {

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	cint	d = OPENDIAL_DTCPNLS ;
	cint	opts = 0 ;
	cint	to = -1 ;
	cint	af = AF_UNSPEC ;

	int	rs ;
	int	rs1 ;

	cchar	*hs = "localhost" ;
	cchar	*ps = NULL ;
	cchar	*svc = "dump" ;
	cchar	**av = NULL ;
	cchar	**ev = NULL ;

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

	if ((rs = opendial(d,af,hs,ps,svc,av,ev,to,opts)) >= 0) {
	    int	fd = rs ;

	    sleep(2) ;

	    if (argv != NULL) {
	        int	ai ;
	        cchar	*fn ;
	        for (ai = 1 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
	            fn = argv[ai] ;
	            rs = procfile(fd,fn) ;
#if	CF_DEBUG
	            debugprintf("main: procfile() rs=%d\n",rs) ;
#endif
	            if (rs < 0) break ;
	        } /* end for */
	    } /* end if */

#if	CF_DEBUG
	    debugprintf("main: done rs=%d\n",rs) ;
#endif

	    rs1 = u_close(fd) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (open-dial) */

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

local int procfile(int wfd,cchar *fn)
{
	int	rs = SR_OK ;
	int	wlen = 0 ;

	if ((rs = uc_open(fn,O_RDONLY,0666)) >= 0) {
	    cint	llen = LINEBUFLEN ;
	    int		fd = rs ;
	    char	lbuf[LINEBUFLEN+1] ;
	    while ((rs = u_read(fd,lbuf,llen)) > 0) {
		int	len = rs ;
	        rs = u_write(wfd,lbuf,len) ;
		wlen += rs ;
		if (rs < 0) break ;
	    } /* end while */
	} /* end if (file-open) */

	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (main) */


