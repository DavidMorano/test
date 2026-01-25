/* termcharliteral SUPPORT */
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
	I test what is a valie character literal in the latest C++
	programming language.

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
#include	<usysbase.h>
#include	<localmisc.h>		/* |eol(3ocal)| */


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	int	hpos = 40 ;
    	cout << "\e7" ;
    	cout << "\e[10;1H" ;
    	for (int i = 1 ; i < 10 ; i += 1) {
    	    cout << "\e[40C\e[" << i << "mblinking\e[m\n" ;
	}
    	cout << "\e8" ;
}
/* end subroutine (main) */


/* local subroutines */


