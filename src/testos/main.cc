/* main SUPPOER (testlang */
/* lang=C++20 */

/* testing operating system (OS) feathres */
/* version %I% last-modified %G% */

#define	CF_SBRK		0		/* test for depracation of |sbrk(2)| */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/wait.h>
#include	<unistd.h>		/* |sbrk(2)| */
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

/* does |waitid(2)| compile (and link) properly? */

	{
	    idtype_t	t = static_cast<idtype_t>(0) ;
	    waitid(t,0,nullptr,0) ;
	}

/* can we call (my beloved) |sbrk(2)| without it being depracated? */

#if	CF_SBRK
	sbrk(2) ;
#endif /* CF_SBRK */


	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


