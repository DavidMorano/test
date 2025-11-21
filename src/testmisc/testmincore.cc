/* testmincore SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |mincore(2)| UNIX® (POSIX®) system call */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This is test code (in the present case for the |mincore(2)|
	system call).

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdarg>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>		/* TIMEBUFLEN */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;			/* |ulibval(3u)| */

/* local defines */


/* imported namespaces */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv) {
    	cint		ps = ulibval.pagesz ;
	int		rs = SR_OK ;
	int		rs1 ;



	if (rs < 0) {
	    printf("failure (%d)\n",rs) ;
	}
	(void) ps ;
	(void) rs1 ;
}
/* end subroutine (main) */


/* local subroutines */


