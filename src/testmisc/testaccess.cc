/* testaccess SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<climits>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<exitcodes.h>
#include	<localmisc.h>


/* ARGSUSED */
int main(int argc,con mainv argv,con mainv envv) {
	cint		am = R_OK ;
	int		rs ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	rs = u_access("main.c",am) ;

	printf("hooray! rs=%d\n",rs) ;

	return EX_OK ;
} /* end subroutine (main) */


