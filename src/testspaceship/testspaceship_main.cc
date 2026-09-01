/* testspaceship_main SUPPORT (testspaceship) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test |sntmtime(3uc)| */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_ORDER	1		/* use |std::strong_order| */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<compare>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<tmtime.hh>		/* LIBUC */
#include	<sntmtime.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/cmdutils.ccm"

import libutil ;			/* |lenstr(3u)| */
import cmdutils ;			/* |optval(3uc)| */

/* local defines */

#define	VARDEBUGFNAME	"TESTSPACESHIP_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif
#ifndef	CF_ORDER
#define	CF_ORDER	1		/* use |std::strong_order| */
#endif


/* external subroutines */


/* external variables */


/* local structures */

struct thing {
    	int		x ;
	int		y ;
} ; /* end struct (thing) */


/* forward references */

#if	CF_ORDER
constexpr std::strong_ordering operator <=> (con thing &v1,con thing &v2) noex {
    	return std::strong_order(v1.x,v2.x) ;
} /* end subroutine (operator <=>) */
constexpr bool operator == (con thing &v1,con thing &v2) noex {
    	return (v1.x == v2.x) ;
} /* end subroutine (operator ==) */
#else /* COMMENT */
constexpr std::strong_ordering operator <=> (con thing &v1,con thing &v2) noex {	cmpord_strong cv = cmpord_strong::equal ;
    	if (v1.x != v2.x) {
	    cv = (v1.x > v2.x) ? cmpord_strong::greater : cmpord_strong::less ;
	}
    	return cv ;
}
constexpr bool operator == (con thing &v1,con thing &v2) noex {
    	return (v1.x == v2.x) ;
} /* end subroutine (operator ==) */
#endif /* CF_ORDER */


/* local variables */

constexpr thing		things[] = {
    	{ 5	, 0 },
    	{ 6	, 0 },
    	{ 4	, 0 },
    	{ 9	, 0 },
    	{ 0	, 0 }
} ; /* end array */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) noex {
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
#if	CF_DEBUG
	if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	    DEBUGOPEN(cp) ;
	    DEBUGPRINTF("starting dfn=%s\n",cp) ;
	}
#endif /* CF_DEBUG */
	if (rs >= 0) {
	    const thing tg(7,0) ;
	    for (cauto &e : things) {
		cc *sr = "?" ;
		if (e > tg) {
		    sr = "gt" ;
		} else if (e == tg) {
		    sr = "eq" ;
		} else if (e < tg) {
		    sr = "lt" ;
		}
		printf("sr=%s\n",sr) ;
	    } /* end for */
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (exit-return) */
	DEBUGPRINTF("ret rs=%d  ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


