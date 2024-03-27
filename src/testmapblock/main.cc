/* testmapblock SUPPORT */
/* lang=C++20 */

/* test the object |mapblock(3uc)| */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-03-28, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |EXIT_SUCCESS| */
#include	<string>
#include	<iostream>
#include	<localmisc.h>

#include	"singlist.hh"
#include	"mapblock.hh"

using namespace std ;

int main(int,mainv,mainv) {
	singlist<ccharp>	list ;
	list += "one" ;
	list += "two" ;
	list += "three" ;
	for (auto &e : list) {
	   cout << e << eol ;
	}
	(void) list ;
	cout << "¯return¯" << eol ;
	return EXIT_SUCCESS ;
}
/* end subroutine (main) */


