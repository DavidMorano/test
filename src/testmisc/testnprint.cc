/* testnprint SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#define	CF_DEBUGS	1
#include	<envstandards.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>		/* |COLUMNS| */
#include	<debug.h>

#define	VARDEBUGFNAME	"TESTNPRINT_DEBUGFILE"

#define	NDF		"testnprint.deb"

extern cchar 	*getourenv(cchar **,cchar *) noex ;

int main(int argc,mainv argv,mainv envv) {
	const int	cols = COLUMNS ;
	int		rs ;
	cchar		*msg = "here/nis/hello" ;

#if	CF_DEBUGS
	cchar		*cp ;
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	rs = nprintf(NDF,"main: msg=%s\n",msg) ;

#if	CF_DEBUGS
	    debugprintf("main: nprintf() rs=%d\n",rs) ;
#endif

	rs = nprinthexblock(NDF,"main: ",cols,msg,-1) ;

#if	CF_DEBUGS
	    debugprintf("main: nprinthexblock() rs=%d\n",rs) ;
#endif

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


