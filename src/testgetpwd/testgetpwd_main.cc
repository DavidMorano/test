/* testgetpwd_main SUPPORT (testgetpwd) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |getpwd(3uc)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<getx.h>		/* |getpwd(3uc)| */
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */

#define	BUFLEN	MAXPATHLEN


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cint	plen = BUFLEN ;
	int	rs ;
	char	pbuf[BUFLEN + 1] ;
	if ((rs = getpwd(pbuf,plen)) >= 0) {
	    printf("%s\n",pbuf) ;
	}
	return (rs >= 0) ? EX_OK : EX_DATAERR ;
}
/* end subroutine (main) */


