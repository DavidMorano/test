/* teststr SUPPORT (strchr) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |strchr(3c)| C-Library subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This is test code (in the present case for the |strchr(3c|
	C-Library call).

*******************************************************************************/

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
	cchar	*a = "this­that­other" ;
	cchar	*sp ;
	int	n = 0 ;
	int	sch = MKCHAR('­') ;
	{
	    sp = a ;
	    for (cchar *tp ; (tp = strchr(sp,sch)) != nullptr ; ) {
	        n += 1 ;
	        sp = (tp + 1) ;
	    } /* end for */
	}
	printf("n=%u\n",n) ;

	return 0 ;
}
/* end subroutine (main) */


