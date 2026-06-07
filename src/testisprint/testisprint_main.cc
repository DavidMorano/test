/* testisprint_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |isprint(3uc)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	Test character property subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* CSTD |UCHAR_MAX| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ascii.h>		/* LIBU */
#include	<ischarx.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cint		chtablen = (UCHAR_MAX + 1) ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	for (int ch, ans, i = 0 ; i < chtablen ; i += 1) {
	    if (isprintlatin(i)) {
		ch = ((i == CH_TAB) || (i == CH_NBSP)) ? ' ' : i ;
		ans = 'y' ;
	    } else {
		ans = 'n' ;
		ch = ' ' ;
	    }
	    printf("%02x %c %c\n",i,ch,ans) ;
	} /* end for */
} /* end subroutine (main) */


