/* testctdecf_main SUPPOERT (testctdecf) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* the the |ctdecf)3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */
#define	CF_CTDECF	0		/* compile-time debugging */
#define	CF_CTDEC	1		/* compile-time debugging */
#define	CF_XXTOSTR	1		/* compile-time debugging */

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
	This little program tests the 'ctdecf(3dam)' subroutine.

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usupport.h>
#include	<ctdecf.h>
#include	<xxtostr.h>		/* |uitostr(3u)| */
#include	<localmisc.h>

#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;

/* local defines */

#define	DBUFLEN		100

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif
#ifndef	CF_CTDECF
#define	CF_CTDECF	0		/* compile-time debugging */
#endif
#ifndef	CF_CTDEC
#define	CF_CTDEC	0		/* compile-time debugging */
#endif
#ifndef	CF_XXTOSTR
#define	CF_XXTOSTR	1		/* compile-time debugging */
#endif


/* imported namespaces */

using libu::ctdec ;			/* subroutine */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern int	ctdecf(char *,int,double,int,int,int,int) noex ;
}


/* external subroutines */


/* local structures */


/* forward references */


/* local variables */

static int	decbuflen = ulibval.decbuflen ;

cbool		f_debug		= CF_DEBUG ;
cbool		f_ctdecf	= CF_CTDECF ;
cbool		f_ctdec		= CF_CTDEC ;
cbool		f_xxtostr	= CF_XXTOSTR ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	int	ex = EXIT_SUCCESS ;
	int	rs = SR_OK ;
	if_constexpr (f_ctdecf) if (rs >= 0) {
	    double	v = 1.62 ;
	    cint	dlen = DBUFLEN ;
	    cint	fcode = 'f' ;
	    cint	w = -1 ;
	    cint	p = 3 ;
	    cint	fill = -1 ;
	    char	dbuf[DBUFLEN+1] ;
	    rs = ctdecf(dbuf,dlen,v,fcode,w,p,fill) ;
	    printf("rs=%d s=>%s<\n",rs,dbuf) ;
	} /* end if */
	if_constexpr (f_ctdec) if (rs >= 0) {
	    int dlen = decbuflen ;
	    cint v = 1234567 ;
	    char dbuf[decbuflen+1] ;
	    rs = ctdec(dbuf,dlen,v) ;
	    printf("ctdec rs=%d dbuf=>%s<\n",rs,dbuf) ;
	} /* end if */
	if_constexpr (f_xxtostr) if (rs >= 0) {
	    const uint v = 1234567 ;
	    int dlen = decbuflen ;
	    char dbuf[decbuflen+1] ;
	    errno = 0 ;
	    char *bp = uitostr(v,(dbuf+dlen)) ;
	    rs = (- errno) ;
	    printf("uitostr rs=%d bp=>%s<\n",rs,bp) ;
	} /* end if */
	if ((rs == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */



