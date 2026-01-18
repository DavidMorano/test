/* testdebugprint SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#define	CF_DEBUGS	1
#include	<envstandards.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>
#include	<debug.h>

#define	VARDEBUGFNAME	"TESTDEBUGPRINT_DEBUGFILE"


int main(int argc,mainv argv,mainv envv) {
	int		rs ;
	int		ex = 0 ;
	cchar		*msg = "here\nis\033" ;
	cchar		*cp ;

#if	CF_DEBUGS
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	rs = debugprintf("main: msg=>%s<\n",msg) ;

	if (rs < 0) {
	    debugprintf("main: rs=%d\n",rs) ;
	}

#if	CF_DEBUGS
	debugclose() ;
#endif

	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


