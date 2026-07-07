/* nprocs_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test getting the number of processes currently on the system */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>		/* POSIX */
#include	<sys/stat.h>		/* POSIX */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usys.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	if ((rs = usys_nprocs()) >= 0) {
	    printf("nprocs=%d\n",rs) ;
	} else {
	    printf("error rs=%d\n",rs) ;
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


