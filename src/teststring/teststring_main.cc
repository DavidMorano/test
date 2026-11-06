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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cinttypes>		/* C++STD */
#include	<new>			/* C++STD */
#include	<initializer_list>	/* C++STD */
#include	<utility>		/* C++STD */
#include	<functional>		/* C++STD */
#include	<algorithm>		/* C++STD */
#include	<vector>		/* C++STD */
#include	<fstream>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<iomanip>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mkx.h>
#include	<strwcpy.h>
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* name-spaces */

using std::string ;			/* type */
using std::cout ;			/* variable */


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
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	/* one */
	{
	    cint n = intconv(s.length()) ;
	    string	w ;
	    for (int i = 0 ; i < n ; i += 1) {
	        w += s[i] ;
	    } /* end for */
	    cout << s << eol ;
	    cout << w << eol ;
	} /* end block */
	/* two */
	{
	    cchar	*ns = "hello world more!" ;
	    for (int i = 0 ; ns[i] ; i += 1) {
	  	cchar c = ns[i] ;
	        s.replace(i,1,1,c) ;
	    } /* end for */
	    cout << s << eol ;
	} /* end block */
	/* three */
	{
	    cint	sl = intconv(s.length()) ;
	    cchar	*sp = s.c_str() ;
	    char	*bp ;
	    if ((bp = new(nt) char [sl+1]) != np) {
		cint	bl = sl ;
		strwcpy(bp,sp,sl) ;
		{
		    cint	rlen = sl ;
		    if (char *rbuf = new(nt) char[rlen + 1]) {
			cint m = 1 ;
		        mklineclean(rbuf,rlen,m,bp,bl) ;
		        cout << rbuf << eol ;
		        delete [] rbuf ;
		    } /* end if (new-char) */
		}
		delete [] bp ;
	    } else {
		rs = SR_NOMEM ;
	    } /* end if (m-a-f) */
	} /* end block */
	/* four */
	if (rs >= 0) {
	    ccharp ysp = "Hello from the void!" ;
	    cint   ysl = 50 ;
	    {
	        string y(ysp,ysl) ;
		cout << y << eol ;
	    }
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


