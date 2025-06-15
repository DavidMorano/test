/* testsqrt SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */


/* revision history:

	= 2017-09-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	What were we doing here?  A custom version of SQRT?

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<math.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>


int main(int argc,mainv,mainv) {
	double		a = 2.0 ;
	double		b ;

	b = sqrt(a) ;
	printf("sqrt(2)=%2.40f\n",b) ;

}
/* end subroutine (main) */


