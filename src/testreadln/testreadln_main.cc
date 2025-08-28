/* testreadln_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the language itself */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |atoi(3c)| */
#include	<cstdio>
#include	<new>			/* |nothrow(3c++)| */
#include	<string_view>
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<getfdfile.h>		/* |FD_STDERR| */
#include	<readln.hh>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |eol| */

#pragma		GCC dependency	"mod/debug.ccm"

import debug ;

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
using std::cin ;			/* variable */
using std::cout ;			/* variable */
using std::cerr ;			/* variable */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* exported variables */


/* local structures */


/* forward references */


/* local variables */

cbool		f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv) {
    	constexpr int	dfd = (f_debug) ? FD_STDERR : -1 ;
    	cnullptr	np{} ;
	cint		rlen = 4 ;
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	debfd(dfd) ;
	if (argc > 0) {
	    istream	*isp = &cin ;
	    cint	llen = LINEBUFLEN ;
	    if (char *lbuf ; (lbuf = new(nothrow) char[llen + 1]) != np) {
	        while ((rs = readln(isp,lbuf,rlen)) > 0) {
		    string_view	s(lbuf,rs) ;
		    cout << rs << " " << s << eol ;
		    if (rs < 0) break ;
		} /* end while */
		if (rs < 0) {
		    cerr << "error (" << rs << ")" << eol ;
		}
		delete [] lbuf ;
	    } /* end if (m-a-f) */
	} /* end if */
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


