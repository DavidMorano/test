/* testvector SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the C++ |vector| container object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<vector>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

using std::vector ;			/* type */
using std::cout ;			/* variable */

int main(int,con mainv,con mainv) {
    	vector<int>	lvec ;
	lvec.push_back(2) ;
	lvec.push_back(3) ;
	for (cauto &m : lvec) {
	    cout << ' ' << m ;
	} /* end for */
	cout << eol ;
} /* end subroutine (main) */


