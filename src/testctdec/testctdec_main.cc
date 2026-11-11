/* testctdec_main SUPPORT (testctdec) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |ctdec(3uc)| subroutine */
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
	This little program tests the |ctdec(3uc)| subroutine,
	and similar other subroutines.

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>		/* CSTD */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD |strcmp(3c)| */
#include	<algorithm>		/* C++STD |min(3c++)| + |max(3c++)| */
#include	<string>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |ctdec(3u)| */
#include	<xxtostr.h>		/* LIBU |uitostr(3u)| */
#include	<atox.h>		/* LIBU */
#include	<xxtostr.h>		/* LIBU */
#include	<ctdec.h>		/* LIBUC */
#include	<ctxxx.h>		/* LIBUC */
#include	<ctchars.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |DECBUFLEN| */
#include	<convdec.h>		/* LIBDAM */

#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;			/* |{x}buflen| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif

#define	NRAND		10000		/* number of random numbers */


/* imported namespaces */

using std::string ;			/* type */
using std::cout ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external subroutines */


/* local structures */


/* forward references */

local int	procval(longlong) noex ;
local int	procxtostr() noex ;
local int	procdec() noex ;
local int	procxxx() noex ;
local int	procstd() noex ;


/* local variables */

cint		diglen = DIGBUFLEN ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv) {
    	int	ex = EXIT_SUCCESS ;
	int	rs = SR_OK ;
	if (rs >= 0) {
	errno = 0 ;
	for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
	    if (cchar *ap = argv[ai] ; ap[0]) {
		if (longlong vv = atosll(ap) ; isvalzero(errno)) {
		    rs = procval(vv) ;
		} /* end if (atosll) */
	    } /* end if (non-empty) */
	    if (rs < 0) break ;
	} /* end for (arguments) */
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = procxtostr() ;
	    printf("procread rs=%d\n",rs) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = procdec() ;
	    printf("procdec  rs=%d\n",rs) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = procxxx() ;
	    printf("procxxx  rs=%d\n",rs) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = procstd() ;
	    printf("procstd  rs=%d\n",rs) ;
	} /* end if (ok) */
	if ((rs == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procval(longlong vv) noex {
    	int		rs ;
	if (static cint	dlen = ulibval.digbuflen ; (rs = dlen) >= 0) {
	    char	dbuf[dlen +1] ;
	    if (rs >= 0) {
	        cint vs = conv<int>(vv) ;
	        errno = 0 ;
	        char *bp = sitostr(vs,(dbuf+dlen)) ;
	        rs = (neg errno) ;
	        printf("sitostr S rs=%d bp=>%s<\n",rs,bp) ;
	    } /* end if */
	    if (rs >= 0) {
	        const uint vu = conv<uint>(vv) ;
	        errno = 0 ;
	        char *bp = uitostr(vu,(dbuf+dlen)) ;
	        rs = (neg errno) ;
	        printf("uitostr U rs=%d bp=>%s<\n",rs,bp) ;
	    } /* end if */
	    if (rs >= 0) {
	        errno = 0 ;
	        char *bp = xtostr(vv,(dbuf+dlen)) ;
	        rs = (neg errno) ;
	        printf("xtostr  S rs=%d bp=>%s<\n",rs,bp) ;
	    } /* end if (ok) */
	    if (rs >= 0) {
	        rs = ctdec(dbuf,dlen,vv) ;
	        printf("ctdec   S rs=%d dbuf=>%s<\n",rs,dbuf) ;
	    } /* end if (ok) */
	    if (rs >= 0) {
	        ulonglong vull = conv<ulonglong>(vv) ;
	        rs = ctdec(dbuf,dlen,vull) ;
	        printf("ctdec   U rs=%d dbuf=>%s<\n",rs,dbuf) ;
	    } /* end if (ok) */
	} /* end if (ulibval) */
	return rs ;
} /* end subroutine (procval) */

local int procxtostr() noex {
    	cint		seed = uint(getustime) ;
    	int		rs = SR_OK ;
	int		c = 0 ; /* return-value */
	char		digbuf1[diglen + 1] = {} ;
	char		digbuf2[diglen + 1] = {} ;
	srand(seed) ;
	for (int i = 0 ; (rs >= SR_OK) && (i < NRAND) ; i += 1) {
	    cint rv = rand() ;
	    ccharp d1p = xtostr		(rv,(digbuf1 + diglen)) ;
	    ccharp d2p = convdec	(rv,(digbuf2 + diglen)) ;
	    if (d1p && d2p) {
	        if (cmpstr(d1p,d2p) != 0) {
		    cchar fmt[] = "mismatch rv=%d\n" ;
		    printf(fmt,rv) ;
		    printf("b1=%s",digbuf1) ;
		    printf("b2=%s",digbuf2) ;
		    rs = SR_INVALID ;
	        } /* end if (strcmp) */
	        c += 1 ;
	    } else {
		rs = SR_DOM ;
	    } /* end if (ok) */
	} /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (procxtostr) */
 
local int procdec() noex {
    	cint		seed = uint(getustime) ;
    	int		rs = SR_OK ;
	int		c = 0 ; /* return-value */
	char		digbuf1[diglen + 1] = {} ;
	char		digbuf2[diglen + 1] = {} ;
	srand(seed) ;
	for (int i = 0 ; (rs >= SR_OK) && (i < NRAND) ; i += 1) {
	    cint rv = rand() ;
	    if ((rs = libu::ctdec(digbuf1,diglen,rv)) >= 0) {
	        if ((rs = ctdec(digbuf2,diglen,rv)) >= 0) {
	            if (cmpstr(digbuf1,digbuf2) != 0) {
		        cchar fmt[] = "mismatch rv=%d\n" ;
		        printf(fmt,rv) ;
		        printf("b1=%s",digbuf1) ;
		        printf("b2=%s",digbuf2) ;
		        rs = SR_INVALID ;
	            } /* end if (strcmp) */
	            c += 1 ;
		} /* end if (ok) */
	    } /* end if (ok) */
	} /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (procdec) */
 
local int procxxx() noex {
    	cint		seed = uint(getustime) ;
	cint		b = 10 ; /* <- base-10 */
    	int		rs = SR_OK ;
	int		c = 0 ; /* return-value */
	char		digbuf1[diglen + 1] = {} ;
	char		digbuf2[diglen + 1] = {} ;
	srand(seed) ;
	for (int i = 0 ; (rs >= SR_OK) && (i < NRAND) ; i += 1) {
	    cint rv = rand() ;
	    if ((rs = libu::ctdec(digbuf1,diglen,rv)) >= 0) {
	        if ((rs = ctxxx(digbuf2,diglen,b,rv)) >= 0) {
	            if (cmpstr(digbuf1,digbuf2) != 0) {
		        cchar fmt[] = "mismatch rv=%d\n" ;
		        printf(fmt,rv) ;
		        printf("b1=%s",digbuf1) ;
		        printf("b2=%s",digbuf2) ;
		        rs = SR_INVALID ;
	            } /* end if (strcmp) */
	            c += 1 ;
		} /* end if (ok) */
	    } /* end if (ok) */
	} /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (procxxx) */
 
local int procstd() noex {
    	cint		seed = uint(getustime) ;
	cint		b = 10 ; /* <- base-10 */
    	int		rs = SR_OK ;
	int		c = 0 ; /* return-value */
	char		digbuf1[diglen + 1] = {} ;
	char		digbuf2[diglen + 1] = {} ;
	srand(seed) ;
	for (int i = 0 ; (rs >= SR_OK) && (i < NRAND) ; i += 1) {
	    cint rv = rand() ;
	    if ((rs = libu::ctdec(digbuf1,diglen,rv)) >= 0) {
	        if ((rs = ctchars(digbuf2,diglen,b,rv)) >= 0) {
	            if (cmpstr(digbuf1,digbuf2) != 0) {
		        cchar fmt[] = "mismatch rv=%d\n" ;
		        printf(fmt,rv) ;
		        printf("b1=%s",digbuf1) ;
		        printf("b2=%s",digbuf2) ;
		        rs = SR_INVALID ;
	            } /* end if (strcmp) */
	            c += 1 ;
		} /* end if (ok) */
	    } /* end if (ok) */
	} /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (procstd) */
 

