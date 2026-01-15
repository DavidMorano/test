/* testsizeof SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */


/* test getting the size of various types (using 'sizeof') */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdarg>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;

	printf("nlink_t=%d\n",szof(nlink_t)) ;

	return ex ;
} /* end subroutine (main) */


/* local subroutines */


