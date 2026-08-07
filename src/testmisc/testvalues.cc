/* testvalues SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test how the more recent GCC compiler versions handle 'volatile' */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This is code that explores how the more recent GCC compiler
	versions handle the 'volatile' feature.

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>		/* POSIX® |getgroups(2)| */
#include	<sys/param.h>		/* POSIX® |getgroups(2)| */
#include	<unistd.h>		/* POSIX® |sysconf(2)| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


local int testvol() noex ;

volatile int	volval = 0 ;

int main(int,con mainv,con mainv) {
    	int		rs = SR_OK ;
	int		ex = EX_SUCCESS ;
	if (rs >= 0) {
    	    rs = testvol() ;
	}
	if ((rs ==  EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int testvol() noex {
    	int		rs = SR_OK ;
	{
	    cint v = ++volval ;
	    printf("volval=%d\n",v) ;
	} /* end block */
    	return rs ;
} /* end subroutine (testvol) */


