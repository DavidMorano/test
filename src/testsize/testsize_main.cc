/* testsize_main SUPPORT (testsize) */
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

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */



struct testsize {
	uint	a ;
	uint	b : 4 ;
	uint	c : 1 ;
} ; /* end struct */

struct structshort {
	short	a ;
} ; /* end struct */

struct structbits {
	short	ch ;
	uint	a:1 ;
	uint	b:1 ;
} ; /* end struct */


int main(int,con mainv,con mainv) {
	int	sz ;
	sz = szof(struct testsize) ;
	printf("szof testsize=%d\n",sz) ;
	sz = szof(structshort) ;
	printf("sz=%d\n",sz) ;
	sz = szof(structbits) ;
	printf("sz=%d\n",sz) ;
} /* end subroutine (main) */


