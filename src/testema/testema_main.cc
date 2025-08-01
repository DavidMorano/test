/* testema_main SUPPORT (testema) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* program to test the EMA object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

  	Description:
	This is a test program for the EMA object.

	Synopsis:
	$ testema.x < testfile

******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<ema.h>
#include	<usystem.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */


/* external subroutines */


/* local structures */


/* local variables */

cchar	ts[] = "(David A Morano) dave.a.morano@gmail.com <d@gmail.com>"


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;


	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */



