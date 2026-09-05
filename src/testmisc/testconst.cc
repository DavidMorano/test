/* testconst SUPPORT (testconst) */
/* charset=ISO8859-1 */
/* lang=C++20 */

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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>

#if	defined(_WCHAR_T)
#define	WCHAR	1
#else
#define	WCHAR	0
#endif


int main(int argc,con mainv argv,con mainv *envv) {
	cint64_t	a = 0 ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	printf("%lld wchar=%u\n",a,WCHAR) ;

	return 0 ;
} /* end subroutine (main) */


