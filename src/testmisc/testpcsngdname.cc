/* testpcsngdname */
/* charset=ISO8859-1 */
/* lang=C89 */

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

#ifndef	PCS
#define	PCS		"/usr/add-on/pcs"
#endif

#ifndef	BBNEWSDNAME
#define	BBNEWSDNAME	"spool/boards"
#endif

#define	VARDEBUGFNAME	"TESTPCSNGDNAME_DEBUGFILE"

extern int	pcsngdname(cchar *,char *,cchar *,cchar *) ;

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,cchar **argv,cchar **envv) {
	cint	rlen = MAXPATHLEN ;

	int	rs = SR_OK ;
	int	rs1 ;

	cchar	*pr = PCS ;
	cchar	*newsdname = BBNEWSDNAME ;

	char	rbuf[MAXPATHLEN+1] = { 0 } ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

	if (argv != NULL) {
	    int	ai ;
	    for (ai = 1 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
		cchar	*np = argv[ai] ;

	        rs = pcsngdname(pr,rbuf,newsdname,np) ;

#if	CF_DEBUG
	        debugprintf("main: pcsngdname() rs=%d\n",rs) ;
#endif

		if (rs < 0) break ;
	    } /* end for */
	} /* end if (argv) */
#if	CF_DEBUG
	debugprintf("main: out rs=%d\n",rs) ;
#endif

	printf("rs=%d ngdname=%s\n",rs,rbuf) ;

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


