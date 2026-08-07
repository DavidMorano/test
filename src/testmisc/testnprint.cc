/* testnprint SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#define	CF_DEBUGS	1

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |COLUMNS| */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#define	VARDEBUGFNAME	"TESTNPRINT_DEBUGFILE"

#define	NDF		"testnprint.deb"


int main(int argc,con mainv argv,con mainv envv) {
	cint		cols = COLUMNS ;
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
}
/* end subroutine (main) */


