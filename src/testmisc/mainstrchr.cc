/* main SUPPORT (strchr) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test to see how |strchr(3c)| reacts to 8-bit character */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-09-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

/*****************************************************************************

  	Description:
	This test is *not* conclusive, because we do not know the
	signedness of the type 'char' in all compilation environments.
	We are also not testing our own |nchr(3dam)| function ...
	because we already know that it works correctly! Haha.

*****************************************************************************/

#include	<envstandards.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<cstdio>
#include	<localmisc.h>

extern int	nchr(const char *,int,int) ;

int main() {
	const int	sch = MKCHAR('­') ;
	int		n = 0 ;
	const char	*a = "this­that­other" ;
	const char	*sp, *tp ;

	sp = a ;
	while ((tp = strchr(sp,sch)) != nullptr) {
	    n += 1 ;
	    sp = (tp+1) ;
	} /* end while */

	printf("n=%u\n",n) ;

	return 0 ;
}
/* end subroutine (main) */


