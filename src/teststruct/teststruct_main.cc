/* teststruct_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* perform some stests on a structure */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-06-15, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

#include	"teststruct_sub.hh"


/* local defines */


/* imported namespaces */


/* local typedefs */


/* external subroutines */

extern void	sub1() noex ;
extern void	sub2() noex ;


/* external variables */


/* local structures */

namespace {
    struct thing {
	int	a, b ;
	struct thing_co {
	    thing *op ;
	    void operator () (thing *p) noex {
		op = p ;
	    } ;
	    operator int () noex ;
	} ;
	thing_co	member ;
	thing(int ªa) noex {
	    a = b = ªa ;
	    member	(this) ;
	} ;
	thing() noex : thing(0) { } ;
    } ; /* end struct (thing) */
} /* end namespace */

namespace {
    struct testcon {
	static int	a ;
	int		b ;
	consteval testcon() noex {
	    b = 2 ;
	} ;
    } ; /* end struct */
} /* end namespace */


/* forward references */


/* local variables */

constexpr testcon	tst ;
constexpr substruct	ss ;

int testcon::a = 1 ;


/* exported variables */


/* exported subroutines */

consteval int getval() noex {
    return ss.a ;
}

constexpr int	c = getval() ;

int main(int,mainv,mainv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	printf("c=%d\n",c) ;
	{
	    thing some(1) ;
	    int v = some.member ;
	    printf("ome=%d\n",v) ;
	}
	{
	    printf("tst.a=%d\n",tst.a) ;
	    printf("tst.b=%d\n",tst.b) ;
	}
	{
	    printf("ss.a=%d\n",ss.a) ;
	    sub1() ;
	    sub2() ;
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */

thing::thing_co::operator int () noex {
	return op->a ;
}


