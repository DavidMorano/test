/* testmod_main SUPPORT (testmodules) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test modules */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/*******************************************************************************

  	Name:
	testmod_main

*******************************************************************************/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<vector>
#include	<string>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"testmod_sub.hh"

import modhello ;


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */

extern void	sub(cchar *) noex ;


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	hello_there("main-there") ;
	sub("main-sub") ;
}
/* end subroutine (main) */


/* local subroutines */


