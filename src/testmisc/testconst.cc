/* testconst SUPPORT (testconst) */
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


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */

static const char	staticstr[] = "staticstr" ;

const char		localstr[] = "localstr" ;

extern const char	str[] = "Hello world!" ;

extern const float	fpi = 3.1415 ;

const int	pi = 3 ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	cout << staticstr << eol ;
	cout << str << eol ;
	cout << "fpi=" << fpi << eol ;
	cout << "pi=" << pi << eol ;
	cout << localstr << eol ;
}
/* end subroutine (main) */


/* local subroutines */


