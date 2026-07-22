/* testdigtab SUPPORT (testdigtab) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* the the |digtab(3u)| facility */
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
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol| */

#pragma		GCC dependency		"mod/digtab.ccm"

import digtab ;				/* |getdig(3u)| */

using std::cout ;

int main(int,con mainv,con mainv) {
    for (int i = 0 ; i < 64 ; i += 1) {
	if (uchar uch = getdig(i) ; (uch >= '0') && (uch <= uchar('ÿ'))) {
	    cout << "dig[" << i << "]=" << uch << eol ;
	} else {
	    cout << "dig[" << i << "]=" << "invalid" << eol ;
	}
    } /* end for */
} /* end subroutine (main) */


