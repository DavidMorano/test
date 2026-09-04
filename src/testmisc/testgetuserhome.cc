/* testgetuserhome */
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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#define	VARDEBUGFNAME	"TESTGETUSERHOME_DEBUGFILE"


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

	if ((argv != NULL) && (argc > 1)) {
	    int	ai ;
	    for (ai = 1 ; argv[ai] != NULL ; ai += 1) {
	        cchar	*un = argv[ai] ;
	        rs = getuserhome(hbuf,hlen,un) ;
	        printf("un=%s rs=%d hd=%s\n",un,rs,hbuf) ;
	    } /* end for */
	} /* end if */

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


