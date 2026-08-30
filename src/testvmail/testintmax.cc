/* testintmax SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* CALYEAR object loader */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ndigit.h>
#include	<localmisc.h>		/* LIBU */


int main() {
	int	n ;
	int	v = INT_MAX ;

	n = ndigit(v,10) ;

	printf("v=%d n=%u\n",v,n) ;

	return 0 ;
} /* end subroutine (main) */


