/* testenum_main SUPPORT (testenum) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test enumerations */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1989-03-01, David A-D- Morano
	This subroutine was originally written.

*/

/* Copyright © 1989 David A-D- Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

enum keys {
	key_zero,
	key_one,
	key_two,
	key_overlast
} ; /* end enum */


/* forward references */

local int sub(keys) noex ;


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* export subroutines */

int main(int,con mainv,con mainv) {
	keys		a ;
	DPRINTF("ent szof=%d\n",szof(keys)) ;

	a = key_one ;
	printf("a=%d zero=%d\n",a,key_zero) ;
	{
	    cint i = key_two ;
	printf("i=%d\n",i) ;
	}

	sub(key_two) ;
	DPRINTF("ret\n") ;
} /* end subroutine (main) */


/* local subroutine */

local int sub(keys n) noex {
	DPRINTF("n=%d\n",n) ;
	return 0 ;
} /* end subroutine (sub) */


