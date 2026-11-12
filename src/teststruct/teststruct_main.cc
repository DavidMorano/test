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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

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
	    } ; /* end */
	    operator int () noex ;
	} ; /* end struct */
	thing_co	member ;
	thing(int ªa) noex {
	    a = b = ªa ;
	    member	(this) ;
	} ; /* end ctor */
	thing() noex : thing(0) { } ;
    } ; /* end struct (thing) */
} /* end namespace */

namespace {
    struct testcon {
	static int	a ;
	int		b ;
	consteval testcon() noex {
	    b = 2 ;
	} ; /* end ctor */
    } ; /* end struct */
} /* end namespace */

#ifdef	COMMENT
	void operator = (int v) noex {
	    val = v ;
	} ; /* end */
#endif /* COMMENT */

struct memer {
    	int	val ;
	memer() = delete ;
	memer(int ªv) noex : val(ªv) { } ;
	operator int () noex {
	    return val ;
	} ; /* end */
} ; /* end struct (memer) */

struct container {
	static memer	a ;
} ; /* end struct (container) */

struct bindvaler {
    	int	v1 ;
	int	v2 ;
} ; /* end struct (bindvaler) */

local bindvaler bindfuner(int n) noex {
    	bindvaler v(n,(n+1)) ;
	return v ;
} /* end subroutine */


/* forward references */


/* local variables */

constexpr testcon	tst ;
constexpr substruct	ss ;

int testcon::a = 1 ;

/* instantiation */
memer container::a	= 1 ;		/* direct construction */


/* exported variables */


/* exported subroutines */

consteval int getval() noex {
    return ss.a ;
} /* end */

constexpr int	c = getval() ;

int main(int,con mainv,con mainv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	printf("c=%d\n",c) ;
	{
	    thing some(1) ;
	    int v = some.member ;
	    printf("ome=%d\n",v) ;
	} /* end */
	{
	    printf("tst.a=%d\n",tst.a) ;
	    printf("tst.b=%d\n",tst.b) ;
	} /* end */
	{
	    printf("ss.a=%d\n",ss.a) ;
	    sub1() ;
	    sub2() ;
	} /* end */
	{
	    container conval ;
	    {
		cint v = conval.a ;
	        printf("conval=%d\n",v) ;
	    }
	} /* end */
	{
	    for (int i = 0 ; i < 3 ; i += 1) {
		cauto [a, b] = bindfuner(i) ;
	        printf("a=%d b=%d\n",a,b) ;
	    } /* end for */
	} /* end if */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */

thing::thing_co::operator int () noex {
	return op->a ;
} /* end */


