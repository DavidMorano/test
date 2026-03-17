/* testobuf SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test the STRNUL object */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	1		/* compile-time debugging */

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
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<strnul.hh>
#include	<exitcodes.h>
#include	<libdebug.h>		/* LIBDEBUG */


/* local defines */


/* external subroutines */


/* external variables */


/* exported variables */


/* exported subroutines */

int main(int argc,cchar **arvv,cchar **envv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;

	strnul		o1 ;
	o1.add('a') ;
	printf("o1.count=%u\n",o1.count()) ;
	{
		obuf o2("Hello world!") ;
		printf("o2.count=%u\n",o2.count()) ;
	}

	if ((ex == EX_OK) && (rs < 0)) {
	       	ex = EX_DATAERR ;
	}
	return ex ;
}
/* end subroutine (main) */


