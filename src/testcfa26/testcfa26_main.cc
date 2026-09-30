/* testcfa26_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |cfa26(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
  	Test the |cfa26(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfa26(3u)| */
#include	<cfa26.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<deb.hh>		/* LIBU |DEBPRINTF(3u)| */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import deb ;				/* DEBPRINTF(3u)| */

constexpr bool		f_debug = CF_DEBUG ;

int main(int argc,con mainv argv,con mainv) {
    	cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
	DEBOPEN("testcfa26.deb") ;
    	DEBPRINTF("ent\n") ;
	if (argc > 1) {
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *ap = argv[ai] ; ap[0]) {
		    if (int v ; (rs = cfa26(ap,-1,&v)) >= 0) {
			printf("int  s=>%s< v=%d\n",ap,v) ;
		        if (longlong vv ; (rs = cfa26(ap,-1,&vv)) >= 0) {
			   {
			       clong lv = conv<long>(vv) ;
			       printf("long s=>%s< lv=%ld\n",ap,lv) ;
			   }
			} /* end if (libu::cfa26) */
		    } /* end if (libuc::cfa26) */
		} /* end if (non-empty) */
		DEBPRINTF("loop rs=%d\n",rs) ;
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
    	DEBPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBCLOSE ;
	return ex ;
} /* end subroutine (main) */


