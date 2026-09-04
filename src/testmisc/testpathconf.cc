/* testpathconf SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* requests for |pathconf(2)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


int main(int argc,con mainv argv,con mainv) {
	if (argc > 1) {
	    cint	req = _PC_LINK_MAX ;
	    cchar	*fn = argv[1] ;
	    long	r = pathconf(fn,req) ;
    	    printf("maxlink=%ld\n",r) ;
	}
    	return 0 ;
} /* end subroutine (main) */


