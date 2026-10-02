/* testcthex_main SUPPORT (testcthex) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* the the |cthex(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */

/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

  	Name:
	main

	Description:
	This little program tests the |cthex(3uc)| subroutine.

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>		/* CSTD */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<algorithm>		/* C++STD |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cthex(3u)| */
#include	<xxtostr.h>		/* LIBU |uitostr(3u)| */
#include	<atox.h>		/* LIBU */
#include	<cthex.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */

#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;			/* |{x}buflen| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif


/* imported namespaces */

using libu::cthex ;			/* subroutine */


/* local typedefs */


/* external subroutines */


/* external subroutines */


/* local structures */


/* forward references */

local int	procval(longlong) noex ;


/* local variables */

static cint	digbuflen = ulibval.digbuflen ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv) {
    	int	ex = EXIT_SUCCESS ;
	int	rs = SR_OK ;
	errno = 0 ;
	for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
	    if (cchar *ap = argv[ai] ; ap[0]) {
		if (longlong vv = atosll(ap) ; iszval(errno)) {
		    rs = procval(vv) ;
		} /* end if (atosll) */
	    } /* end if (non-empty) */
	    if (rs < 0) break ;
	} /* end for (arguments) */
	if ((rs == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procval(longlong vv) noex {
    	int		rs = SR_OK ;
	cint		dlen = digbuflen ;
	char		dbuf[digbuflen+1] ;
	if (rs >= 0) {
	    cint v = conv<int>(vv) ;
	    errno = 0 ;
	    char *bp = sitostr(v,(dbuf+dlen)) ;
	    rs = (neg errno) ;
	    printf("sitostr S rs=%d bp=>%s<\n",rs,bp) ;
	} /* end if */
	if (rs >= 0) {
	    const uint uv = conv<uint>(vv) ;
	    errno = 0 ;
	    char *bp = uitostr(uv,(dbuf+dlen)) ;
	    rs = (neg errno) ;
	    printf("uitostr U rs=%d bp=>%s<\n",rs,bp) ;
	} /* end if */
	if (rs >= 0) {
	    errno = 0 ;
	    char *bp = xtostr(vv,(dbuf+dlen)) ;
	    rs = (neg errno) ;
	    printf("xtostr S rs=%d bp=>%s<\n",rs,bp) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    cint b = 16 ;
	    errno = 0 ;
	    char *bp = xtostr(vv,(dbuf+dlen),b) ;
	    rs = (neg errno) ;
	    printf("xtostr S rs=%d bp=>%s<\n",rs,bp) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    ulonglong uvv = conv<ulonglong>(vv) ;
	    cint b = 16 ;
	    errno = 0 ;
	    char *bp = xtostr(uvv,(dbuf+dlen),b) ;
	    rs = (neg errno) ;
	    printf("xtostr rs=%d bp=>%s<\n",rs,bp) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = cthex(dbuf,dlen,vv) ;
	    printf("cthex S rs=%d dbuf=>%s<\n",rs,dbuf) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    ulonglong uvv = conv<ulonglong>(vv) ;
	    rs = cthex(dbuf,dlen,uvv) ;
	    printf("cthex U rs=%d dbuf=>%s<\n",rs,dbuf) ;
	} /* end if (ok) */
	return rs ;
} /* end subroutine (procval) */


