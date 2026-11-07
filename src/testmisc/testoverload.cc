/* testoverload SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program (TESTOVERLOAD) */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-07-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<climits>		/* CSTD |INT_MAX| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<algorithm>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |resumelife(3u)| */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

#define	VARDFN		"TESTOVERLOAD_DFN"

#define	AN		4

using std::min ;			/* subroutine */
using std::max ;			/* subroutine */


/* forward references */

constexpr char		fmt[] = "str> %s\n" ;

local int proc(int n) noex {
	return n ;
} /* end subroutine (proc) */


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		rs1 ;
	if (cchar *cp = getourenv(envv,VARDFN)) {
	    rs = DEBUGOPEN(cp) ;
	    DEBUGPRINTF("starting DFD=%d\n",rs) ;
	}
	if (rs >= 0) {
	    rs = proc(1) ;
	    printf("rs=%d\n",rs) ;
	} /* end if (ok) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	DEBUGCLOSE ;
	return 0 ;
} /* end subroutine (main) */


