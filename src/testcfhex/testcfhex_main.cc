/* testcfhex_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |cfhex(3uc)| sunroutine */
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
  	Test the |cfhex(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfhex(3u)| */
#include	<cfhex.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

constexpr bool		f_debug = CF_DEBUG ;

int main(int argc,con mainv argv,con mainv) {
    	cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
    	DPRINTF("ent\n") ;
	if (argc > 1) {
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *ap = argv[ai] ; ap[0]) {
		    cint al = -1 ;
		    if (int v ; (rs = cfhex(ap,al,&v)) >= 0) {
			printf("libuc I  s=>%s<  v=%d\n",ap,v) ;
		        if ((rs = libu::cfhex(ap,al,&v)) >= 0) {
			    printf("libu  I  s=>%s<  v=%d\n",ap,v) ;
			    if (longlong vv ; (rs = cfhex(ap,al,&vv)) >= 0) {
			        long lv = conv<long>(vv) ;
			        printf("libuc LL s=>%s< lv=%ld\n",ap,lv) ;
		                if ((rs = libu::cfhex(ap,al,&vv)) >= 0) {
			            lv = conv<long>(vv) ;
			            printf("libu  LL s=>%s< lv=%ld\n",ap,lv) ;
			        } /* end if (libu::cfhex) */
			    } /* end if (cfhex) */
			} /* end if (libu::cfhex) */
		    } /* end if (libuc::cfhex) */
		} /* end if (non-empty) */
		DPRINTF("loop rs=%d\n",rs) ;
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
    	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


