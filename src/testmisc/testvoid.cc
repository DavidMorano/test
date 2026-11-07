/* testvoid SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program (TESTVOID) */
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

#define	VARDFN		"TESTVOID_DFN"

#define	AN		4

using std::min ;			/* subroutine */
using std::max ;			/* subroutine */


/* forward references */

constexpr char		fmt[] = "str> %s\n" ;

local int proci(int *a,int idx,int **ipp) noex {
    	*ipp = (a + idx) ;
	return SR_OK ;
} /* end subroutine (proci) */

template<typename T>
local int procx(T *a,int idx,T **ipp) noex {
    	*ipp = (a + idx) ;
	return SR_OK ;
} /* end subroutine (procx) */

local int procv(int *a,int idx,void **vpp) noex {
    	int **ipp = (int **) vpp ;
    	*ipp = (a + idx) ;
	return SR_OK ;
} /* end subroutine (procv) */


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
	    int		a[AN] = { 0, 1, 2, 3 } ;
	    intp	ip = (a + 0) ;
	    printf("a=%d\n",a[0]) ;
	    rs = proci(a,1,&ip) ;
	    printf("ae=%d\n",*ip) ;
	    rs = procx(a,2,&ip) ;
	    printf("ae=%d\n",*ip) ;
	    {
		voidp vp{} ;
	        rs = procv(a,3,&vp) ;
		{
		    int *ip = intp(vp) ;
	            printf("ae=%d\n",*ip) ;
		}
	    }
	} /* end if (ok) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	DEBUGCLOSE ;
	return 0 ;
} /* end subroutine (main) */


