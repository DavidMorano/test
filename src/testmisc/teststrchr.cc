/* teststrchr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test to see how |strchr(3c)| reacts to 8-bit character */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*****************************************************************************

  	Description:
	This test is *not* conclusive, because we do not know the
	signedness of the type 'char' in all compilation environments.

*****************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<cstring>		/* |strchr(3c)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<mkchar.h>
#include	<localmisc.h>

int main(int,mainv,mainv) {
	cint	sch = MKCHAR('­') ;
	int	n = 0 ;
	cchar	*sp = "this­that­other" ;
	for (cchar *tp ; (tp = strchr(sp,sch)) != nullptr ; ) {
	    n += 1 ;
	    sp = (tp + 1) ;
	} /* end for */
	printf("n=%u\n",n) ;
}
/* end subroutine (main) */


