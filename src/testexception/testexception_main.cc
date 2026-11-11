/* textexception_main SUPPORT (textexception) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |std::exception(3c++)| subroutine */
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
#include	<stdexcept>		/* C++STD |std::exception(3c++)| */
#include	<algorithm>		/* C++STD |min(3c++)| + |max(3c++)| */
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
#include	<prognamevar.hh>	/* LIBDAM */

#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;			/* |{x}buflen| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif

#define	NRAND		10000		/* number of random numbers */


/* imported namespaces */

using std::exception ;			/* type */
using std::invalid_argument ;		/* type */
using std::out_of_range ;		/* type */
using libu::ctdec ;			/* subroutine */
using std::cout ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external subroutines */


/* local structures */


/* forward references */

local int	procexcept() noex ;


/* local variables */

cint		diglen		= DIGBUFLEN ;
cchar		strinvarg[]	= "invalid_argument" ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (rs >= 0) {
	    rs = procexcept() ;
	    printf("procexcept rs=%d\n",rs) ;
	} /* end if (ok) */
	if ((rs == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	    printf("%s: error rs=%d ex=%d\n",ccp(pn),rs,ex) ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procexcept() noex {
    	int		rs = SR_OK ;
	try {
	    invalid_argument	exc_invarg(strinvarg) ;
	    {
		ccharp strwhat = exc_invarg.what() ;
		printf("invarg w=%s\n",strwhat) ;
	    } /* end block */
	} catch (...) {
	    rs = SR_BADE ;
	} /* end (try-catch) */
	return rs ;
} /* end subroutine (procexcept) */


