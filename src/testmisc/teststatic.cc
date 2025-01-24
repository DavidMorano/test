/* main SUPPORT (teststatic) */
/* encoding=ISO8859-1 */
/* lang=C20 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<sys/types.h>
#include	<stdio.h>
#include	<usystem.h>
#include	<localmisc.h>


/* local defines */


/* forward references */

	static void hello() ;


/* exported variables */


/* exported subroutines */

int main() {
	hello() ;
	return 0 ;
}
/* end subroutine (main) */

static void hello() {
    	printf("Hello world!\n") ;
}


