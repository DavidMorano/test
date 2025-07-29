/* mainlog SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

#define	CF_DEBUGS	1		/* compile-time debugging */

/* revision history:

	= 2013-07-11, David A�D� Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright � 2013 David A�D� Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<sys/types.h>
#include	<cmath>
#include	<cinttypes>
#include	<cstdlib>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<forward_list>
#include	<vector>
#include	<string>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<usystem.h>
#include	<getourenv.h>
#include	<localmisc.h>


/* local defines */

#define	VARDEBUGFNAME	"LOG_DEBUGFILE"


/* name-spaces */

using namespace std ;


/* external subroutines */

extern "C" double	log2(double) ;

#if	CF_DEBUGS
extern "C" int	debugopen(cchar *) ;
extern "C" int	debugprintf(cchar *,...) ;
extern "C" int	debugclose() ;
extern "C" int	strlinelen(cchar *,cchar *,int) ;
#endif


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
	int		rs = SR_OK ;
	int		ex = 0 ;
	cchar		*cp ;
#if	CF_DEBUGS
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */
	{
	    const int	vals[] = { 1024, 100, 184 } ;
	    double	d, r ;
	    for (auto v : vals) {
	        d = v ;
		r = log2(d) ;
		cout << r << endl ;
	    }
	} /* end block */

#if	CF_DEBUGS
	debugprintf("main: ret rs=%d\n",rs) ;
#endif

#if	CF_DEBUGS
	debugclose() ;
#endif
	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


