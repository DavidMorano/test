/* testmkuuid SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstdio>
#include	<usystem.h>
#include	<mkuuid.h>
#include	<snmkuuid.h>
#include	<localmisc.h>

#define	VARDEBUGFNAME	"TESTMKUUID_DEBUGFILE"


#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugprinthex(cchar *,int,cchar *,int) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,cchar **argv,cchar **envv) {
	MKUUID		uuid ;
	int		rs = SR_OK ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

	if ((rs = mkuuid(&uuid,0)) >= 0) {
	    cint	rlen = MAXPATHLEN ;
	    char	rbuf[MAXPATHLEN+1] ;
#if	CF_DEBUG
	    debugprinthex("main: time=",80,&uuid.time,8) ;
	    debugprinthex("main: clk=",80,&uuid.clk,8) ;
	    debugprinthex("main: node=",80,&uuid.node,8) ;
#endif
	    if ((rs = snmkuuid(rbuf,rlen,&uuid)) >= 0) {
		printf("rs=%d uuid=%s\n",rs,rbuf) ;
	    }
	} /* end if (argv) */

#if	CF_DEBUG
	debugprintf("main: out rs=%d\n",rs) ;
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


