/* main SUPPOER (testlang */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<iostream>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<clanguage.h>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |eol| */


/* local defines */


/* imported namespaces */

using std::cout ;			/* variable */


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

	cout << a << eol ;
	cout << lamb() << eol ;

	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


