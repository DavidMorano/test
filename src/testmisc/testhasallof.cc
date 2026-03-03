/* testhasallof SUPPORT */
/* charset=ISO8859-1 */
/* lang=C89 */

#define	CF_DEBUGS	1

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
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG */

#define	VARDEBUGFNAME	"TESTHASALLOF_DEBUGFILE"


int main(int argc,mainv argv,mainv envv) {
	cint		hlen = MAXPATHLEN ;
	int		rs ;
	int		f ;
	cchar		*ans[3] = { "NO", "YES" } ;
	cchar		*sp = "this is ( a comment )" ;

#if	CF_DEBUGS
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	        debugopen(cp) ;
	    }
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUGS */

	f = hasallof(sp,-1,"hn") ; printf("%s\n",ans[f]) ;

	f = hasallof(sp,-1,"hwn") ; printf("%s\n",ans[f]) ;

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


