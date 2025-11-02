/* testvector SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the C++ |vector| container object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<vector>
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>

using std::vector ;			/* type */
using std::cout ;			/* variable */

int main(int,mainv,mainv) {
    	vector<int>	l ;
	l.push_back(2) ;
	l.push_back(3) ;
	for (cauto &m : l) {
	    cout << ' ' << m ;
	}
	cout << eol ;
} /* end subroutine (main) */


