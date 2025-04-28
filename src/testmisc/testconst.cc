/* testconst SUPPORT (testconst) */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* test constant evaluations */
/* version %I% last-modified %G% */


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

consteval int subval(int v) noex {
    	return (v * 1) ;
}

struct values {
    	int	res ;
	consteval values() noex {
	    res = 1 ;
	    for (int i = 1 ; i < 10 ; i += 1) {
		res *= subval(i) ;
	    }
	} ;
} ;


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
    	constexpr values	val ;
	cout << staticstr << eol ;
	cout << str << eol ;
	cout << "fpi=" << fpi << eol ;
	cout << "pi=" << pi << eol ;
	cout << localstr << eol ;
	cout << val.res << eol ;
}
/* end subroutine (main) */


/* local subroutines */


