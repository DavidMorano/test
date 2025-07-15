/* testprgetprogpath */


#define	CF_DEBUGS	1		/* compile-time debugging */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>

#include	"testprgetprogpath_config.h"


#if	CF_DEBUGS || CF_DEBUGN
extern int	nprintf(cchar *,cchar *,...) ;
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


extern cchar	*getourenv(cchar **,cchar *) ;


int main(int argc,mainv argv,mainv envv) {
	int	rs = 0 ;

	cchar	*pr = "/usr/add-on/local" ;
	cchar	*pn = "imail" ;
	char		progfname[MAXPATHLEN+1] ;

#if	CF_DEBUGS 
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	rs = prgetprogpath(pr,progfname,pn) ;

	printf("rs=%d progfname=%s\n",rs,progfname) ;

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

}
/* end subroutine (main) */


