/* testcfdig_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |cfdig(3uc)| subroutine */
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
  	Test the |cfdig(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfdig(3u)| */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#include	"cfdig.h"		/* *local* */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

import ulibvals ;			/* |maxbase| */

constexpr bool		f_debug = CF_DEBUG ;

local int procval(int base,cchar *ap,int al) noex ;

int main(int argc,con mainv argv,con mainv) {
    	cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
    	DPRINTF("ent\n") ;
	if (argc > 1) {
	    int base = 0 ;
	    int	c = 0 ;
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *ap = argv[ai] ; ap[0]) {
		    cint al = -1 ;
		    if (c++ == 0) {
			base = atoi(ap) ;
		    } else {
		        rs = procval(base,ap,al) ;
		    }
		} /* end if (non-empty) */
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
    	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


local int procval(int b ,cchar *ap,int al) noex {
    	int		rs = SR_INVALID ;
	if ((b >= 0) && (b <= ulibval.maxbase)) {
            if (int v ; (rs = cfdig(ap,al,b,&v)) >= 0) {
                printf("libuc I  s=>%s<  v=%d\n",ap,v) ;
                    if (longlong vv ; (rs = cfdig(ap,al,b,&vv)) >= 0) {
                        long lv = conv<long>(vv) ;
                        printf("libuc LL s=>%s< lv=%ld\n",ap,lv) ;
                    } /* end if (cfdig) */
            } /* end if (libuc::cfdig) */
	} /* end if (valid base) */
	return rs ;
} /* end subroutine (procval) */



