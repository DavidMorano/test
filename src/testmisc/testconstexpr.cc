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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<array>			/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

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
	} ; /* end ctor */
    } ; /* end struct (tester) */
} /* end namespace */

constexpr int		preps[] = {
    	1, 2, 3
} ; /* end array */

consteval int sumpreps(int mval) noex {
    	int sum = 0 ;
    	for (cauto &v : preps) {
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
	} /* end for */
} /* end method (tester::mkval) */


/* forward references */

consteval int summer(int a,int b) noex {
    	return a + b ;
} /* end subroutine */

consteval int deliver() noex {
	constexpr array<int,3> a = { 1, 2, 3 } ;
	int sum = 0 ;
	for (int i = 0 ; i < 3 ; i += 1) {
	    sum += summer(1,a[i]) ;
	} /* end for */
	return sum ;
} /* end subroutine (deliver) */


/* local variables */

constexpr tester	test_data ;

constexpr cpcchar	strs[] = {
    	"NUL",
	"TAB",
	nullptr
} ; /* end array (strs) */


/* exported variables */


/* exported subroutines */

consteval int sumstrs() noex {
    	int	v = 0 ;
    	for (int i = 0 ; strs[i] ; i += 1) {
	    v += clenstr(strs[i]) ;
	} /* end for */
	return v ;
} /* end subroutine (sumstrs) */

int main(int,con mainv,con mainv) {
    	printf("val=%d\n",test_data.val) ;
	{
	    constexpr int sum = deliver() ;
	    printf("sum=%d\n",sum) ;
	}
	{
	    constexpr int v = sumstrs() ;
	    printf("sumstrs=%d\n",v) ;
	}
} /* end subroutine (main) */


/* local subroutines */


