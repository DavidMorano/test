/* main SUPPORT (teststatic) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>


/* local defines */


/* forward references */

	local void hello() ;


/* exported variables */


/* exported subroutines */

int main() {
	hello() ;
	return 0 ;
} /* end subroutine (main) */

local void hello() {
    	printf("Hello world!\n") ;
}


