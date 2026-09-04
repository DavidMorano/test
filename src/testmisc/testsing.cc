/* mainsing SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<forward_list>
#include	<cinttypes>
#include	<string>
#include	<vector>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<localmisc.h>

#include	"singlist.hh"


/* local defines */

#define	VARDEBUGFNAME	"SING_DEBUGFILE"


/* name-spaces */

using namespace std ;


/* external subroutines */

#if	CF_DEBUG
extern "C" int	debugopen(cchar *) ;
extern "C" int	debugprintf(cchar *,...) ;
extern "C" int	debugclose() ;
extern "C" int	strlinelen(cchar *,cchar *,int) ;
#endif


/* external variables */


/* local structures (and methods) */

local int	printlist(singlist<int> &,cchar *) ;


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv envv) {
	int		rs = SR_OK ;
	int		ex = 0 ;
#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	        rs = debugopen(cp) ;
	        debugprintf("main: starting DFD=%d\n",rs) ;
	    }
	}
#else
	(void) envv ;
#endif /* CF_DEBUG */
	{
	    singlist<int>	srclist = { 2, 4, 8, 1, 0 } ;

	    cout << "= zero\n" ;
	    printlist(srclist,"zero") ;

	    cout << "= one\n" ;
	    for (auto v : srclist) {
		cout << "v=" << v << endl ;
	    }

	    cout << "= two\n" ;
	    {
	        if ((rs = srclist.inshead(5)) >= 0) {
		    printlist(srclist,"added") ;
		}
	    }

	    cout << "= three\n" ;
	    if (rs >= 0) {
	        int		v ;
	        while ((rs = srclist.rem(&v)) >= 0) {
#if	CF_DEBUG
	debugprintf("main: srclist.rem() rs=%d\n",rs) ;
#endif
		    cout << "v=" << v << endl ;
	        }
#if	CF_DEBUG
	debugprintf("main: while-out rs=%d\n",rs) ;
#endif
		if (rs == SR_EMPTY) {
		    cout << "EOL rs=" << rs << endl ;
		    rs = SR_OK ;
		}
	    }

	} /* end block */

#if	CF_DEBUG
	debugprintf("main: ret rs=%d\n",rs) ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif
	if (rs < 0) ex = 1 ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int printlist(singlist<int> &l,cchar *s) {
	int		c = 0 ;
	cout << s ;
	for (auto v : l) {
	    c += 1 ;
	    cout << " " << v ;
	}
	cout << endl ;
	return c ;
} /* end subroutine (printlist) */


