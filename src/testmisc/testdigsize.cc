/* testdigsize SUPPORT (testdigsize) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test constant evaluations */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cinttypes>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<new>			/* C++STD |nothrow(3c++)| */
#include	<initializer_list>	/* C++STD */
#include	<utility>		/* C++STD */
#include	<functional>		/* C++STD */
#include	<algorithm>		/* C++STD */
#include	<vector>		/* C++STD */
#include	<string>		/* C++STD */
#include	<cmath>			/* C++STD |log2(3c++)| */
#include	<fstream>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<iomanip>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


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

int main(int,con mainv,con mainv) {
    	cint	bsizes[] = { 8, 16, 32, 64, 128, 256, 512, 1024 } ;
	cint	bases[] = { 2, 8, 10, 16, 64 } ;
	for (cauto bs : bsizes) {
	    double	bsf(bs) ; 
	    cout << "bs=" << bs << eol ;
	    for (cauto b : bases) {
	        cout << "bs=" << bs << " b=" << b ;
	        cout << " log2(b)=" << log2(b) << eol ;
		double	ndf = (bsf / log2(b)) ;
		double	nd = ceil(ndf) ;
		cout << "ndigs=" << nd << " ndf=" << ndf << eol ;
	    } /* end for */
	} /* end for */
} /* end subroutine (main) */


/* local subroutines */


