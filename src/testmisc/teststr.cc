/* main (strchr) */
/* lang=C++20 */


/* revision history:

	= 2017-09-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */


#include	<envstandards.h>
#include	<cstring>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<mkchar.h>
#include	<localmisc.h>


int main() {
	const char	*a = "this­that­other" ;
	const char	*sp, *tp ;
	int	n = 0 ;
	int	sch = MKCHAR('­') ;

	sp = a ;
	while ((tp = strchr(sp,sch)) != NULL) {
	    n += 1 ;
	    sp = (tp+1) ;
	} /* end while */

	printf("n=%u\n",n) ;

	return 0 ;
}
/* end subroutine (main) */


