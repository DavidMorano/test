/* testlastlog SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<lastlog.h>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>

#define	VARDEBUGFNAME	"TESTLASTLOG_DEBUGFILE"

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,cchar **argv,cchar **envv)
{

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs ;
	int	rs1 ;

	cchar	*llfname = "/var/adm/lastlog" ;


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

	if ((rs = u_open(llfname,O_WRONLY,0666)) >= 0) {
	    off_t	eoff ;
	    cint	llsize = sizeof(struct lastlog) ;
	    int		fd = rs ;
	    char	lbuf[sizeof(struct lastlog)] ;
	    eoff = (215*llsize) ;
	    if ((rs = u_seek(fd,eoff,SEEK_SET)) >= 0) {
		memset(lbuf,0,llsize) ;
		rs = u_write(fd,lbuf,llsize) ;
	    }
	    u_close(fd) ;
	} /* end if (file-open) */

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


