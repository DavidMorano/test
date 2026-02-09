/* teststring_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test some string manipulations */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cinttypes>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<vector>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<mkx.h>
#include	<strwcpy.h>
#include	<localmisc.h>


/* name-spaces */

using std::string ;			/* type */
using std::endl ;			/* subroutine? */
using std::cout ;			/* variable */
using std::nothrow ;			/* constant */


/* external subroutines */


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	string		s = "hello world!" ;
	string		w ;
	int		i ;
	int		rs = SR_OK ;

/* one */

	{
	    cint n = intconv(s.length()) ;
	    for (i = 0 ; i < n ; i += 1) {
	        w += s[i] ;
	    }
	    cout << s << endl ;
	    cout << w << endl ;
	} /* end block */

/* two */

	{
	    cchar	*ns = "hello world more!" ;
	    for (i = 0 ; ns[i] ; i += 1) {
	  	int 	ch = ns[i] ;
	        s.replace(i,1,1,ch) ;
	    }
	    cout << s << endl ;
	} /* end block */

/* three */

	{
	    cint	sl = s.length() ;
	    cchar	*sp = s.c_str() ;
	    char	*bp ;
	    if ((bp = new(nothrow) char [sl+1]) != np) {
		cint	bl = sl ;
		strwcpy(bp,sp,sl) ;
		{
		    cint	rlen = sl ;
		    if (char *rbuf ; (rbuf = new(nt) char[rlen + 1]) != np) {
			cint m = 1 ;
		        mklineclean(rbuf,rlen,m,bp,bl) ;
		        cout << rbuf << endl ;
		        delete [] rbuf ;
		    } /* end if (new-char) */
		}
		delete [] bp ;
	    } else {
		rs = SR_NOMEM ;
	    } /* end if (m-a-f) */
	} /* end block */

	return 0 ;
}
/* end subroutine (main) */


/* local subroutines */


