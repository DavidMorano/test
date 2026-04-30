/* testgetaf SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |ucodenames(3u)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testgetaf

  	Description:
  	I do a small test on the |ucodenames(3u)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>		/* |ucodenames(3u)| */
#include	<getaf.h>
#include	<localmisc.h>


constexpr cpcchar	testafs[] = { 
    "unspec", "unix", "local", "inet4", "inet6",
    "decnet", "x25"
} ; /* end array */

int main(int,con mainv,con mainv) {
    	int ex = EXIT_SUCCESS ;
	int rs = SR_OK ;
	printf("ent\n") ;
	for (cauto &n : testafs) {
	    printf("n=%s\n",n) ;
	    if ((rs = getaf(n,-1)) >= 0) {
		printf("req=%s af=%d\n",n,rs) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	printf("ret rs=%d\n",rs) ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


