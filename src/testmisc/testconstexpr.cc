/* testconstexpr SUPPORT (testconstexpr) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* some tests on the 'constespr' feature in C++ */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	testconstexpr

	Description:
	Test the extent of the 'consteval' feature.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<array>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */


/* imported namespaces */

using std::array ;			/* type */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct tester {
	int	val ;
	consteval void mkval() noex ;
	consteval tester() noex {
	    val = 0 ;
	    mkval() ;
	} ;
    } ; /* end struct (tester) */
} /* end namespace */

constexpr int		preps[] = {
    	1, 2, 3
} ;

consteval int sumpreps(int mval) noex {
    	int sum = 0 ;
    	for (cauto &v: preps) {
	    if (v == mval) {
	        sum += v ;
	    }
	} /* end for */
	return sum ;
} /* end subroutine (sumpreps) */

consteval void tester::mkval() noex {
    	constexpr array<int,4>	a{ 1, 3, 5, 7 } ;
	for (cauto &av : a) {
    	    val += sumpreps(av) ;
	}
} /* end method (tester::mkval) */


/* forward references */

consteval int summer(int a, int b) noex {
    	return a + b ;
}

consteval int deliver() noex {
	constexpr array<int,3> a = { 1, 2, 3 } ;
	int sum = 0 ;
	for (int i = 0 ; i < 3 ; i += 1) {
	    sum += summer(1,a[i]) ;
	}
	return sum ;
} /* end subroutine (deliver) */


/* local variables */

constexpr tester	test_data ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	printf("val=%d\n",test_data.val) ;
	{
	    constexpr int sum = deliver() ;
	    printf("sum=%d\n",sum) ;
	}
}
/* end subroutine (main) */


/* local subroutines */


