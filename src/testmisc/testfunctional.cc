/* testfunctional SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test fcuntional features of C++ */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	main

	Description:
	I test something to do with functional library features of the
	C++ language.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<new>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<string>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>		/* |eol(3ocal)| */


/* local defines */


/* name-spaces */

using std::function ;			/* subroutine-template */
using std::bind ;			/* subroutine-template */
using std::bind_front ;			/* subroutine-template */
using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures */

struct teststruct {
    	int	num = 30 ;
	int operator () (int a) noex {
	    return a ;
	} ;
	int sub(int a) const noex {
	    return (num - a) ;
	} ;
} ; /* end struct (teststruct) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	using namespace std::placeholders ;
    	teststruct	our ;
	{
    	    cauto fn = bind(&teststruct::sub,&our,_1) ;
	    cout << "bind fn=" << fn(10) << eol ;
	}
	{
    	    cauto fn = bind_front(&teststruct::sub,&our) ;
	    cout << "bind_front fn=" << fn(10) << eol ;
	}
	{
    	    cauto fn = bind_front(&teststruct::sub,teststruct{50}) ;
	    cout << "bind_front fn=" << fn(10) << eol ;
	}
	{
    	    cauto fn = bind_front(&teststruct::sub,teststruct{}) ;
	    cout << "bind_front fn=" << fn(10) << eol ;
	}
	{
    	    cauto fn = bind_front(&teststruct::sub,our) ;
	    cout << "bind_front fn=" << fn(10) << eol ;
	}
}
/* end subroutine (main) */


/* local subroutines */


