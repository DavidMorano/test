/* testpow SUPPORR (testexp) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |pow(3m)| C-Math-Library call */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This is test code (in the present case for the |pow(3m)|
	library call).

*******************************************************************************/

#include	<envstandards.h>
#include	<cstring>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<cmath>
#include	<iostream>		/* |cout(3c++)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<mkchar.h>
#include	<localmisc.h>

using std::cout ;			/* variable */

int main() {
	long double	n49 = 49.0 ;
	long double	n50 = 50.0 ;
	long double	n51 = 51.0 ;
	long double	e1, e2 ;
	e1 = pow(n50,n50) ;
	e2 = pow(n49,n51) ;
	printf("e1=%ld\n",e1) ;
	printf("e2=%ld\n",e2) ;
}
/* end subroutine (main) */


