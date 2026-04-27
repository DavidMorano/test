/* testucodenames_main SUPPORT */
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
	testucodenames

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
#include	<localmisc.h>

constexpr int	tests[] = {
    	SR_NOENT,
	SR_PERM,
	SR_NXIO,
	SR_LOCKFAIL
} ; /* end array */

int main(int,con mainv,con mainv) {
    	int	rs = SR_OK ;
	cchar	*cp ;
    	for (cauto &e : tests) {
	    if ((rs = ucodename_sr(e,&cp)) >= 0) {
	        printf("e=%6d rs=%2d s=%s\n",e,rs,cp) ;
	    } else {
		printf("failed on %d\n",e) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	if (rs < 0) printf("failed\n") ;
} /* end subroutine (main) */


