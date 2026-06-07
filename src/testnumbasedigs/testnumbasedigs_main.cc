/* testnumbasedigs_main SUPPORT (testnumbasedigs) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* the the |numbasedigs(3u)| facility */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<climits>		/* CSTD |UCHAR_MAX| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<iostream>		/* C++STD */
#include	<iomanip>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol| */

#pragma		GCC dependency		"mod/uconstants.ccm"

import uconstants ;			/* |numbasedig(3u)| */

using std::setw ;			/* IO manip */
using std::min ;			/* subroutine */
using std::max ;			/* subroutine */
using std::cout ;			/* variable */

cint		mtype = 7 ;
cint		mbase = 64 ;

int main(int,con mainv,con mainv) {
    cint ntype = min(mtype, numbasedigs_maxtype) ;
    cint nbase = min(mbase, numbasedigs_maxbase) ;
    for (int t = 0 ; t <= ntype ; t += 1) {
	for (int b = 2 ; b <= nbase ; b += 1) {
	    cout << " t=" << setw(2) << t ;
	    cout << " b=" << setw(2) << b ;
	    cout << " nd=" << setw(4) << numbasedig.digs[t][b] ;
	    cout << eol ;
	} /* end for */
    } /* end for */
} /* end subroutine (main) */


