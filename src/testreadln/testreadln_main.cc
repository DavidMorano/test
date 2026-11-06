/* testreadln_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |readln(3uc) subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	readreadln

	Description:
	Test the |readln(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<new>			/* C++STD placement-new */
#include	<algorithm>		/* C++STD |min(3c++)| + |max(3c++)| */
#include	<string_view>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<readln.hh>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol| */

#pragma		GCC dependency		"mod/deb.ccm"

import deb ;

/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	1024
#endif

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* imported namespaces */

using std::istream ;			/* type */
using std::string_view ;		/* type */
using std::min ;			/* subroutine */
using std::max ;			/* subroutine */
using std::cin ;			/* variable */
using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* local typedefs */


/* external subroutines */


/* exported variables */


/* local structures */


/* forward references */


/* local variables */

cint		rlen		= LINEBUFLEN ;
cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv) {
    	constexpr int	dfd = (f_debug) ? FD_STDERR : -1 ;
    	cnullptr	np{} ;
	cnothrow	nt{} ;
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	debfd(dfd) ;
	if (argc > 0) {
	    istream	*isp = &cin ;
	    cint	llen = LINEBUFLEN ;
	    if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) {
		cint ll = min(llen,rlen) ;
	        while ((rs = readln(isp,lbuf,ll)) > 0) {
		    string_view	s(lbuf,rs) ;
		    cout << "rs=" << rs << " " << s ;
		    if (rs < 0) break ;
		} /* end while */
		if (rs < 0) {
		    cerr << "error (" << rs << ")" << eol ;
		} /* end if (error) */
		delete [] lbuf ;
	    } /* end if (m-a-f) */
	} /* end if */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = EX_DATAERR ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


