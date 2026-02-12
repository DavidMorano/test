/* testurmdirs SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |u_rmdirs(3u)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<iostream>		
#include	<iomanip>		
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>		/* |u_rmdirs(3u)| */
#include	<localmisc.h>		/* |eol| */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

using std::cerr ;

int main(int argc,mainv argv,mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 1) {
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *fn = argv[ai] ; fn[0]) {
		    rs = u_rmdirs(fn) ;
		}
		if (rs < 0) break ;
	    } /* end for */
	} /* end block */
	if ((rs < 0) && (ex == EXIT_SUCCESS)) {
	    cerr << "ret: " << rs << eol ;
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


