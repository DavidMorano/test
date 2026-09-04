/* testuserattr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<user_attr.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>

int main() {
	userattr_t	*uap ;

	int	rs ;

	cchar	*un = "junker" ;

	rs = uc_getusernam(un,&uap) ;

	fprintf(stderr,"main: uc_getusernam() rs=%d\n",rs) ;

	return 0 ;
} /* end subroutine (main) */


