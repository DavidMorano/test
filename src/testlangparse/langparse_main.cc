/* testlangparse_main SUPPORT (testlangparse) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the LANGPARSE object */
/* version %I% last-modified %G% */


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
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |eol| */


/* local defines */


/* imported namespaces */

using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* local typedefs */


/* external subroutines */


/* exported variables */


/* local structures */


/* forward references */

local int procfile(cchar *) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	if (argc > 0) {
	    for (int ai = 1 ; (rs >= 0) && (ai < argc) && argv[ai] ; ai += 1) {
		cchar	*fn = argv[ai] ;
		rs = procfile(fn) ;
	    } /* end for */
	}
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int procfile(cchar *fn) noex {
    	cnothrow	nt{} ;
    	cnullptr	np{} ;
	cint		llen = LINEBUFLEN ;
    	int		rs = SR_FAULT ;
	if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) {
	    if (ccfile rf ; (rs = rf.open(fn,"r",0)) >= 0) {
		while ((rs = rf.readln(lbuf,llen)) > 0) {
		    rs = 0 ;
		} /* end while */
		rs1 = rf.close ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (ccfile) */
	    delete lbuf ;
	} /* end if (new-char) */
	return rs ;
} /* end subroutine (procfile) */


