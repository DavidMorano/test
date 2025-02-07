/* mod_sub SUPPORT (testmodules) */
/* encoding=ISO8859-1 */
/* lang=C++20 */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cinttypes>
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
#include	<usystem.h>
#include	<localmisc.h>

import hello ;


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

void sub(cchar *sp) noex {
    	hello_there(sp) ;
}
/* end subroutine (sub) */

    void subfrank(cchar *sp) noex {
    	cout << "sub-frank - " << sp << eol ;
    }


/* local subroutines */


