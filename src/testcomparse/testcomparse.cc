/* testcomparse */
/* lang=C89 */

#define	CF_DEBUGS	1

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<cstdio>
#include	<usystem.h>

#include	"comparse.h"

#define	VARDEBUGFNAME	"TESTCOMPARSE_DEBUGFILE"

#if	CF_DEBUGS
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif

extern cchar 	*getourenv(cchar **,cchar *) ;

int main(int argc,mmainv argv,mainv envv) {
	COMPARSE	coms ;
	cint	hlen = MAXPATHLEN ;
	int		rs ;
	cchar	*sp = "this is ( a comment )" ;
	char		hbuf[MAXPATHLEN+1] ;

#if	CF_DEBUGS
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUGS */

	if ((rs = comparse_start(&coms,sp,-1)) >= 0) {
	    cchar	*vp, *cp ;
	    int		vl, cl ;

	    rs = comparse_getval(&coms,&vp) ;
	    vl = rs ;
	    printf("getval() rs=%d\n",rs) ;
	    printf("getval() v=>%s<\n",vp) ;

	    rs = comparse_getcom(&coms,&cp) ;
	    cl = rs ;
	    printf("getcom() rs=%d\n",rs) ;
	    printf("getcom() c=>%s<\n",cp) ;

	    comparse_finish(&coms) ;
	} /* end if (comparse) */

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */

