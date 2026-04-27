/* testrandom SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* small test of the system random number generator */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* compile-time debugging */

/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testrandom

	Description:
	We perform a small test of the system random number generator.

*******************************************************************************/

#include	<envstandards.h>
#include	<sys/types.h>
#include	<climits>
#include	<cstdlib>
#include	<string>
#include	<cinttypes>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<vector>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* name-spaces */

using std::cout ;
using std::endl ;


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	cint	n = 10 ;
	cint	m = 100 ;
	for (int v, rn, i = 0 ; i < n ; i += 1) {
	    rn = random() ;
	    v = (rn % m) ;
	    cout << v << endl ;
	} /* end for */
}
/* end subroutine (main) */


/* local subroutines */


