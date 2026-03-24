/* testspace_main SUPPORT (testspace) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the space-ship operator */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testspace

	Description:
	This test program tests the space-ship operator.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<iomanip>
#include	<compare>		/* space-ship */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<timeval.hh>		/* <- under test */
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* local defines */


/* local namespaces */

using std::cout ;			/* variable */


/* local typedefs */

using ord = std::ordering_strong ;


/* external subroutines */


/* external variables */


/* local structures */

struct duo {
    	int	x0, x1 ;
	ord operator <=> (const duo &) const = default ;
} ; /* end struct (duo) */


/* forward references */

local int	test_duo() noex ;
local int	test_timeval() noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	cout << std::boolalpha ;
	{
	    if (rs == SR_OK) rs = test_duo() ;
	    if (rs == SR_OK) rs = test_timeval() ;
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */

local int test_duo() noex {
    	const duo	d1(2,1) ;
    	const duo	d2(1,2) ;
    	int		rs = SR_OK ;
	cout << "duo" << eol ;
	cout << "grater " << (d1 > d2) << eol ;
	cout << "lesser " << (d1 < d2) << eol ;
    	return rs ;
} /* end subroutine (test_duo) */

local int test_timeval() noex {
	const timeval_t	tv1(1,2) ;
	const timeval_t	tv2(1,1) ;
	int		rs = SR_OK ;
	cout << "timeval" << eol ;
	cout << "grater " << (tv1 > tv2) << eol ;
	cout << "lesser " << (tv1 < tv2) << eol ;
	return rs ;
} /* end subroutine (test) */


