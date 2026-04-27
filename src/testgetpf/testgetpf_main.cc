/* testgetpf SUPPORT */
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
	testgetpf

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
#include	<getpf.h>
#include	<localmisc.h>

constexpr int	tests[] = {
	PF_NATM,
	PF_PPP,
    	AF_INET4,
	AF_INET,
	AF_INET6,
	AF_UNIX,
	AF_LOCAL,
	AF_UNSPEC
} ; /* end array */

int main(int,con mainv,con mainv) {
    	int	rs = SR_OK ;
    	for (cauto &e : tests) {
	    if ((rs = getpf(e)) >= 0) {
	        printf("e=%6d rs=%2d\n",e,rs) ;
	    } else {
		printf("e=%6d failed\n",e) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	if (rs < 0) printf("failed\n") ;
} /* end subroutine (main) */


