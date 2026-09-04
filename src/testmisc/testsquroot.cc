/* testsquroot SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-09-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	What were we doing here?  A custom version of SQRT?

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<cmath>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>


int main(int argc,cchar **argv,cchar **envv) {
	double		a = 2.0 ;
	double		b ;
	(void) argc ;
	(void) argv ;
	(void) envv ;

	b = sqrt(a) ;
	printf("sqrt(2)=%2.40f\n",b) ;

	return 0 ;
} /* end subroutine (main) */


