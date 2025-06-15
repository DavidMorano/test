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
#include	<cmath>			/* |log2(3c++)| */
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
	    }
	} /* end for */
}
/* end subroutine (main) */


/* local subroutines */


