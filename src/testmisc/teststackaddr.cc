/* teststackaddr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test various stack operations */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<stackaddr.h>
#include	<localmisc.h>
#include	<libdebug.h>


#define	VARDEBUGFNAME	"TESTSTACKADDR_DEBUGFILE"

struct xpair {
	cchar	*hp ;
	cchar	*up ;
} ; /* end struct (xpair) */

constexpr xpair		xpairs[] = {
	{ "h3", "u3" },
	{ "h3", "u3a" },
	{ "h2", "u2" },
	{ nullptr, "u2a" },
	{ "h2", "u2b" },
	{ "h1", "u1" },
	{ nullptr, "u0" },
	{ nullptr, nullptr }
} ; /* end array (xparis) */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	STACKADDR	s ;
	cint		rlen = MAXPATHLEN ;
	int		rs ;
	int		rs1 ;
	char		rbuf[MAXPATHLEN+1] ;

#if	CF_DEBUG
	{
	    if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	        debugopen(cp) ;
	    }
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

	if ((rs = stackaddr_start(&s,rbuf,rlen)) >= 0) {
	    cchar	*hp ;
	    cchar	*up ;
	    debugprintf("main: stackaddr_start() rs=%d\n",rs) ;

	    for (int i = 0 ; xpairs[i].up ; i += 1) {
		hp = xpairs[i].hp ;
		up = xpairs[i].up ;
		rs = stackaddr_add(&s,hp,-1,up,-1) ;
	        debugprintf("main: stackaddr_add() rs=%d\n",rs) ;
		if (rs < 0) break ;
	    } /* end for */

	    rs1 = stackaddr_finish(&s) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (grcache) */
	debugprintf("main: out rs=%d\n",rs) ;

	printf("sa=%s\n",rbuf) ;

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


