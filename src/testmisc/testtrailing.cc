/* mailtrailing SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */

/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Fun and games.  We find the nunber of trailing zero digits (in decimal)
	for a given factorial value (itself computed from a given source).

	Keywords:
	fives, zeros, twos, tailing, digits

	Synopsis:
	$ trailing

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cinttypes>
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
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>


/* name-spaces */

using namespace std ;


/* external subroutines */

extern "C" uint	factorial(uint) ;

extern "C" int	sisub(cchar *,int,cchar *) ;


/* external variables */


/* local structures (and methods) */


/* forward references */

local int trailing(longlong_t) ;


/* local variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	cint	nmax = 30 ;
	string		w ;
	int		z ;
	(void) argc ;
	(void) argv ;
	(void) envv ;

	for (int n = 0 ; n < nmax ; n += 1) {
	    z = trailing(n) ;
	    cout << "n=" << n << " z=" << z << endl ;
	}
	
	return 0 ;
} /* end subroutine (main) */


/* local subroutines */

local int trailing(longlong_t n) {
	longlong_t	v = n ;
	int		c = 0 ;
	
	while (v >= 5) {
	    longlong_t	t = (v/5) ;
	    c += t ;
	    v = t ;
	}

	return c ;
} /* end subroutine (trailing) */


