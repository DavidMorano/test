/* testgetrunlevel */
/* charset=ISO8859-1 */
/* lang=C++20 */

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
#include	<tmpx.h>

#define	VARDEBUGFNAME	"TESTGETRUNLEVEL_DEBUGFILE"


#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,cchar **argv,cchar **envv) {
	cint	hlen = MAXPATHLEN ;
	int		rs ;
	char		hbuf[MAXPATHLEN+1] ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

	rs = getrunlevel(NULL) ;

	printf("getrunlevel() rs=%d\n",rs) ;
	if ((rs >= 0) && isprintlatin(rs)) {
	    printf("runlevel %c\n",rs) ;
	}

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */

