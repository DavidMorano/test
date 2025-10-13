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
#include	<ccfile.hh>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |eol| */

#include	<langparse.h>

/* local defines */


/* imported namespaces */

using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* local typedefs */


/* external subroutines */


/* exported variables */


/* local structures */


/* forward references */

local int procfile(langparse *,cchar *) noex ;
local int procln(langparse *,cchar *,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (argc > 0) {
	    if (langparse pa ; (rs = pa.start) >= 0) {
	        for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		    cchar	*fn = argv[ai] ;
		    rs = procfile(&pa,fn) ;
		    if (rs < 0) break ;
	        } /* end for */
	        rs1 = pa.finish ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (langparse) */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int procfile(langparse *lpp,cchar *fn) noex {
    	cnothrow	nt{} ;
    	cnullptr	np{} ;
	cint		llen = LINEBUFLEN ;
    	int		rs = SR_FAULT ;
	int		rs1 ;
	if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) {
	    if (ccfile rf ; (rs = rf.open(fn,"r",0)) >= 0) {
		while ((rs = rf.readln(lbuf,llen)) > 0) {
		    rs = procln(lpp,lbuf,rs) ;
		    if (rs < 0) break ;
		} /* end while */
		rs1 = rf.close ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (ccfile) */
	    delete [] lbuf ;
	} /* end if (new-char) */
	return rs ;
} /* end subroutine (procfile) */

local int procln(langparse *lpp,cchar *lp,int ll) noex {
    	int		rs = SR_OK ;
	(void) lpp ;
	(void) lp ;
	(void) ll ;
	return rs ;
} /* end subroutine (procln) */


