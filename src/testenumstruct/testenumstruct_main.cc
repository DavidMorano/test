/* testenumstruct_main SUPPORT (testenumstruct) */
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

import testenumstruct_mod ;

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* local namespaces */

using enum keys ;

/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

enum struct vals : int {
    	val0,
	val1,
	val2
} ; /* end enum (vals) */


/* forward references */

local int sub(keys) noex ;


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* export subroutines */

int main(int,con mainv,con mainv) {
	keys		a = key_one ;
	DPRINTF("ent szof=%d\n",szof(keys)) ;

	{
	    cint k = int(a) ;
	    printf("key_zero=%d\n",k) ;
	}
	{
	    cint i = int(key_two) ;
	    printf("i=%d\n",i) ;
	}
	sub(key_two) ;
	{
	    using enum vals ;
	    cint v = int(val0) ;
	    printf("v=%d\n",v) ;
	}
	DPRINTF("ret\n") ;
} /* end subroutine (main) */


/* local subroutine */

local int sub(keys n) noex {
    	cint k = int(n) ;
	DPRINTF("n=%d\n",k) ;
	return 0 ;
} /* end subroutine (sub) */


