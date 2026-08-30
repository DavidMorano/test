/* teststrnul SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test the STRNUL objects */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2012 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:

	Description:
	Test of the OBUF object.  It hardly needs any testing, really.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<strnul.hh>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* external subroutines */


/* external variables */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv arvv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;

	strnul		o1 ;
	o1.add('a') ;
	printf("o1.count=%u\n",o1.count()) ;
	{
		strnul o2("Hello world!") ;
		printf("o2.count=%u\n",o2.count()) ;
	}

	if ((ex == EX_OK) && (rs < 0)) {
	    ex = EX_DATAERR ;
	}
	return ex ;
} /* end subroutine (main) */


