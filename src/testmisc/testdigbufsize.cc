/* testdigbufsize SUPPORT (testdigbufsize) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* the the |digbufsizes(3u)| facility */
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
#include	<iostream>		/* C++STD */
#include	<iomanip>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol| */

#pragma		GCC dependency		"mod/uconstants.ccm"

import uconstants ;			/* |digbufsize(3u)| */

using std::setw ;			/* subroutine */
using std::cout ;			/* variable */

cint cols = 16 ;

int main(int,con mainv,con mainv) {
    int c = 0 ;
    for (int b = 2 ; b <= MAXBASE ; b += 1) {
	cout << setw(4) << b ;
	for (int t = 0 ; t <= MAXTYPE ; t += 1) {
	    cout << " " << setw(4) << digbufsize[t,b] ;
	} /* end for */
	cout << eol ;
    } /* end for */
} /* end subroutine (main) */


