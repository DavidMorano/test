/* main SUPPORT (testenum) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test enumerations */
/* version %I% last-modified %G% */


/* revision history:

	= 1989-03-01, David A-D- Morano
	This subroutine was originally written.

*/

/* Copyright © 1989 David A-D- Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

enum keys {
	key_zero,
	key_one,
	key_two,
	key_overlast
} ;


/* forward references */

static int sub(keys) noex ;


/* local variables */


/* exported variables */


/* export subroutines */

int main(int,mainv,mainv) {
	keys	a ;
	int		i ;

	printf("sizeof=%d\n",szof(keys)) ;

	a = key_one ;
	printf("a=%d zero=%d\n",a,key_zero) ;

	i = key_two ;
	printf("i=%d\n",i) ;

	sub(key_two) ;
}
/* end subroutine (main) */


/* local subroutine */

static int sub(keys n) noex {
	printf("sub: n=%d\n",n) ;
	return 0 ;
}
/* end subroutine (sub) */


