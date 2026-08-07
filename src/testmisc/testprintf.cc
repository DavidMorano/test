/* testprintf SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the C-language standard-library |printf(3c)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


static const double	pi = 2673.1415926 ;



int main(int,con mainv,con mainv) {
    	cint	prec = 3 ;
	int	ex = EXIT_SUCCESS ;
	int	rs = SR_OK ;
	cchar	*s = "Hello world!" ;
	cchar	*fmt = "%7s\n" ;
	{
	printf(fmt,s) ;
	}
	{
	    fmt = "val(6.2d)=%6.2d\n" ;
	    printf(fmt,0) ;
	    printf(fmt,1) ;
	}
	{
	    fmt = "val(#o)=%#o\n" ;
	    printf(fmt,0) ;
	    printf(fmt,1) ;
	    printf(fmt,10) ;
	}
	{
	    fmt = "val(6.2o)=%6.2o\n" ;
	    printf(fmt,0) ;
	    printf(fmt,1) ;
	}
	{
	fmt = "%6.4d\n" ;
	printf(fmt,100) ;
	}
	{
	printf("%.*f\n",prec,pi) ;
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if */
	return ex ;
} /* end subroutine (main) */


