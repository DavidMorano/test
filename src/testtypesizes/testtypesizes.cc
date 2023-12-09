/* testtypesizes */
/* lang=C++20 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/param.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<usystem.h>
#include	<stdintx.h>
#include	<valuelimits.hh>
#include	<digbufsizes.hh>
#include	<ucvariables.hh>
#include	<localmisc.h>


/* forward references */


/* external subroutines */


/* local variables */


/* exported subroutines */

int main(int,cchar **,cchar **) {
	cint	tsize = sizeof(uid_t) ;
	    printf("s=%u\n",tsize) ;
	return 0 ;
}
/* end subroutine (main) */


