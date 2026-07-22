/* testsaturate SUPPORT (testsaturate) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* some tests on the 'constespr' feature in C++ */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	testsaturate

	Description:
	Test the extent of the 'consteval' feature.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<climits>		/* CSTD |INT_MIN| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<numeric>		/* C++STD */
#include	<array>			/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */


/* imported namespaces */

using std::add_sat ;
using std::cast_saturate ;


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    	long	lw = (long(INT_MIN + 2) - 4L) ;
	{
	    printf("intmin=%d\n",INT_MIN) ;
	    printf("lw=%ld\n",lw) ;
	    int iw = saturate<int>(lw) ;
	    printf("iw=%d\n",iw) ;
	}
	{
	    cint iw = add_sat(1,2) ;
	    printf("iw=%d\n",iw) ;
	}
} /* end subroutine (main) */


/* local subroutines */


