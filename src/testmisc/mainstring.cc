/* mainstring SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

#define	CF_DEBUGS	0		/* compile-time debugging */

/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<cstdlib>
#include	<cinttypes>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<string>
#include	<vector>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<usystem.h>
#include	<mkx.h>
#include	<strwcpy.h>
#include	<localmisc.h>


/* name-spaces */

using namespace std ;


/* external subroutines */


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	string		s = "hello world!" ;
	string		w ;
	int		i ;
	int		rs = SR_OK ;

/* one */

	for (i = 0 ; i < s.length() ; i += 1) {
	    w += s[i] ;
	}
	cout << s << endl ;
	cout << w << endl ;

/* two */

	{
	    cchar	*ns = "hello world more!" ;
	    for (i = 0 ; ns[i] ; i += 1) {
	  	int 	ch = ns[i] ;
	        s.replace(i,1,1,ch) ;
	    }
	    cout << s << endl ;
	}

/* three */

	{
	    cint	sl = s.length() ;
	    cchar	*sp = s.c_str() ;
	    char	*bp ;
	    if ((bp = new(nothrow) char [sl+1]) != NULL) {
		cint	bl = sl ;
		strwcpy(bp,sp,sl) ;

		cint	rlen = sl ;
		if (char *rbuf ; (rbuf = new(nt) char[rlen + 1]) != np) {
		    mklineclean(rbuf,rlen,bp,bl) ;
		    cout << rbuf << endl ;
		    delete {} rbuf ;
		}

		delete [] bp ;
	    } else {
		rs = SR_NOMEM ;
	    } /* end if (m-a-f) */
	}

	return 0 ;
}
/* end subroutine (main) */


/* local subroutines */


