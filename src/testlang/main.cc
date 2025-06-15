/* main SUPPORT (testlang) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the language itself */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |atoi(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |eol| */


/* local defines */


/* imported namespaces */

using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* local typedefs */

typedef int (*sub_f)() noex ;


/* external subroutines */


/* exported variables */


/* local structures */


/* forward references */

static int	sub0() noex ;
static int	sub1() noex ;
static int	sub2() noex ;
static int	sub3() noex ;
static int	sub4() noex ;


/* local variables */

constexpr sub_f		subs[] = {
	sub0,
	sub1,
	sub2,
	sub3,
	sub4
} ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	if (argc > 0) {
	    cint	ns = nelem(subs) ;
	    for (int ai = 1 ; (rs >= 0) && (ai < argc) && argv[ai] ; ai += 1) {
		cint	si = atoi(argv[ai]) ;
		if (si < ns) {
		    typeof(si) dummy = si ;
		    cerr << "sub=" << si << " dummy=" << dummy << eol ;
		    rs = (*subs[si])() ;
		} else {
		    cout << "out of range" << eol ;
		    rs = SR_RANGE ;
		}
	    } /* end for */
	}
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

static int sub0() noex {
	cout << "Hello world!" << eol ;
	return SR_OK ;
}
 
static int sub1() noex {
	cint		a = ({ cint b = 1 ; cint c = 2 ; (b + c) ; }) ;
	int		rs = SR_OK ;
	auto lamb = [] () -> int {
	    cint	b = 1 ;
	    cint	c = 2 ;
	    return (b + c) ;
	} ;
	cout << a << eol ;
	cout << lamb() << eol ;
	return rs ;
}

static int sub2() noex {
	int		rs = SR_OK ;
	cchar		*sp = "hello\n" ;
	for (int i = 0 ; *sp ; i += 1) {
	    cout << i << *sp++ << eol ;
	}
	return rs ;
}

static int sub3() noex {
	int		rs = SR_OK ;
	cvoid		*cvp = nullptr ;
	void		*vp{} ;
	cvp = vp ;
	(void) cvp ;
	return rs ;
}

static int sub4() noex {
	int		rs = SR_OK ;
	if (int	a = sub3()) {
	    cout << "true a=" << a << eol ;
	} else {
	    cout << "false a=" << a << eol ;
	}
	return rs ;
}


