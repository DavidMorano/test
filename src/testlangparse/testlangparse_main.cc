/* testlangparse_main SUPPORT (testlangparse) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the LANGPARSE object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

	= 2025-11-03, David A-D- Morano
	I am updating this to the latest API of the LANGPARSE object.

*/

/* Copyright © 1998,2025 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Description:
	I test the LANGPARSE object.

*******************************************************************************/

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

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |getlenstr(3u)| */

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
local int procout(langparse *,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (argc > 0) {
	    if (langparse pa ; (rs = pa.start) >= 0) ylikely {
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
	if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) ylikely {
	    if (ccfile rf ; (rs = rf.open(fn,"r",0)) >= 0) ylikely {
		while ((rs = rf.readln(lbuf,llen)) > 0) {
		    if ((rs = procln(lpp,lbuf,rs)) > 0) {
			rs = procout(lpp,llen) ;
		    }
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
    	int		rs ;
	int		c = 0 ;
	if ((rs = getlenstr(lp,ll)) > 0) {
	    rs = lpp->load(lp,ll) ;
	    c = rs ;
	} /* end if (getlenstr) */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (procln) */

local int procout(langparse *lpp,int slen) noex {
    	cnullptr	np{} ;
    	cnothrow	nt{} ;
    	int		rs = SR_OK ;
	int		wlen = 0 ;
	if (short *sb ; (sb = new(nt) short [slen + 1]) != np) {
	    while ((rs = lpp->read(sb,slen)) > 0) {
		for (int i = 0 ; i < rs ; i += 1) {
		    char	ch = char(sb[i]) ;
		    cout << ch ;
		    wlen += 1 ;
		} /* end for */
		cout << eol ;
	    } /* end while */
	    delete [] sb ;
	} /* end if (new-short) */
	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (procout) */


