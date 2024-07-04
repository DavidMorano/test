/* main SUPPORT (testlang) */
/* lang=C++20 */

/* test the language itself */
/* version %I% last-modified %G% */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
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


/* exported variables */


/* local structures */


/* forward references */

static void sub1() noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv) {
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	int		a = ({ cint b = 1 ; cint c = 2 ; (b + c) ; }) ;
	auto lamb = [] () -> int {
	    cint	b = 1 ;
	    cint	c = 2 ;
	    return (b + c) ;
	} ;
	(void) argc ;
	cout << a << eol ;
	cout << lamb() << eol ;
	sub1() ;
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

static void sub1() noex {
	cchar	*sp = "hello\n" ;
	for (int i = 0 ; *sp ; i += 1) {
	    cout << i << *sp++ << eol ;
	}
}


