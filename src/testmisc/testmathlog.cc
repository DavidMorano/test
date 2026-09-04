/* testmathlog SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test math function |log| */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>
#include	<cstdio>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cmath>
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

int main() {
	long double	x, y ;

	x = pow(2.0,127.0) + 1.0 ;

	y = log10(x) ;
	if (errno != ERANGE) {
	    printf("y=%Lf\n",y) ;
	} else {
	    printf("y=RANGE\n") ;
	}
	return 0 ;
} /* end subroutine (main) */


