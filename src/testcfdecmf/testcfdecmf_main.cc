/* testcfdecmf_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |cfdecmf(3uc)| sunroutine */
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
  	Test the |cfdecmf(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD |nullptr_t| */
#include	<cstdlib>		/* CSTD |getenv(3c)| */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<cfdecmf.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBF |DPRINTF(3u)| */

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
		    if (int v ; (rs = cfdecmf(ap,-1,&v)) >= 0) {
			printf("s=>%s< v=%d\n",ap,v) ;
		    }
		} /* end if (non-empty) */
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	}
    	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


