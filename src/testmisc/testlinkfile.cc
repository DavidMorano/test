/* testlinkfile SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test if |printf(3c)| can print out ISO-Latin1 characters */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testlinkfile

  	Description:
  	Test the |u_linkfile(3u)| UNIX® system-interface subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<localmisc.h>

using std::cout ;			/* variable */
using std::cerr ;			/* variable */

int main(int argc,mainv argv,mainv) {
    	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	cchar		*pn = "testlinkfile" ;
	if (argc > 2) {
	    rs = SR_INVALID ;
	    if (argv[1] && argv[2]) {
		rs = u_linkfile(argv[1],argv[2]) ;
		cerr << pn << ": " << "u_linkfile() rs=" << rs << eol ;
	    } /* end if (valid) */
	} /* end if (arguments) */
	if (rs < 0) ex = EXIT_FAILURE ;
	return ex ;
} /* end subroutine (main) */


