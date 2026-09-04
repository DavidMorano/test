/* testmkpathuser SUPPORT */
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
#include	<clanguage.h>
#include	<usysbase.h>
#include	<getx.h>

#define	VARDEBUGFNAME	"TESTMKUSERPATH_DEBUGFILE"

extern "C" int	mkpathuser(char *,cchar *,cchar *,int) noex ;

#if	CF_DEBUG
extern int	debugopen(cchar *) noex ;
extern int	debugprintf(cchar *,...) noex ;
extern int	debugclose() noex ;
extern int	strlinelen(cchar *,int,int) noex ;
#endif


int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	char		rbuf[MAXPATHLEN+1] ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	        debugopen(cp) ;
	    }
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

	if (argv != nullptr) {
	    int	ai ;
	    for (ai = 1 ; (ai < argc) && (argv[ai] != nullptr) ; ai += 1) {
		rs = mkpathuser(rbuf,nullptr,argv[ai],-1) ;
		printf("rs=%d p=%s\n",rs,rbuf) ;
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (argv) */

#if	CF_DEBUG
	debugprintf("main: out rs=%d\n",rs) ;
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


