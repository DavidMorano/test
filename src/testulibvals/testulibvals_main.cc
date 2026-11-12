/* testulibvals_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |sysconf(2)| standard C-library subroutine */
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
  	Test the |sysconf(3c)| standard C-library call.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD |getenv(3c)| */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

constexpr bool		f_debug = CF_DEBUG ;

int main(int,con mainv,con mainv) {
    	cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
    	DPRINTF("ent\n") ;
	if (rs >= 0) {
	    if ((rs = ulibval.maxpathlen) >= 0) {
    	        printf("maxpathlen=%d\n",rs) ;
	        if ((rs = ulibval.maxnamelen) >= 0) {
    	            printf("maxnamelen=%d\n",rs) ;
	            if ((rs = ulibval.maxline) >= 0) {
    	                printf("maxline=%d\n",rs) ;
	                if ((rs = ulibval.maxarg) >= 0) {
    	                    printf("maxarg=%d\n",rs) ;
	                    if ((rs = ulibval.digbuflen) >= 0) {
    	                        printf("digbuflen=%d\n",rs) ;
	                        if ((rs = ulibval.maxbase) >= 0) {
    	                            printf("maxbase=%d\n",rs) ;
	    			    if ((rs = ulibval.maxpathlen) >= 0) {
    	                                printf("maxpathlen=%d\n",rs) ;
				    }
			        }
			    }
			}
		    }
		}
	    } /* end */
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = unprocessors ;
	    printf("ncpu=%d\n",rs) ;
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
    	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


