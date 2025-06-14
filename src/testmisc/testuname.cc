/* testuname SUPPORT (testuname) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test |uname(2)| system-call */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/utsname.h>		/* |uname(2)| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cinttypes>
#include	<cstring>
#include	<new>			/* |nothrow(3c++)| */
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

int main(int,mainv,mainv) {
    	struct utsname		ut ;
	cout << szof(ut.nodename) << eol ;
}
/* end subroutine (main) */


/* local subroutines */


