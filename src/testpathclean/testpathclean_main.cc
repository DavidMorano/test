/* testpathclean_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |pathclean(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/******************************************************************************

  	Description:
	This little subroutine tests something! :-)

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<path.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<deb.hh>		/* LIBD |DEBPRINTF(3u)| */

#pragma		GCC dependency		"mod/deb.ccm"

import deb ;				/* debugging */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

#define	VARPATHGROUP		"PATHGROUP_DFN"
#define	TESTPATHCLEAN_DFN	"testpathclean.deb"


/* external subroutines */


/* external variables */


/* local variables */

cint			maxpathlen	= MAXPATHLEN ;
cchar			dfn[]		= TESTPATHCLEAN_DFN ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subrouines */

int main(int argc,con mainv argv,con mainv envv) {
    	cnullptr	np{} ;
	cint		plen = maxpathlen ;
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	(void) envv ;
	if (ccharp dcp = getenv(VARPATHGROUP)) {
	    if (cint rs1 = DEBOPEN(dcp) ; rs1 >= 0) {
		DEBPRINTF("debinit fd=%d\n",rs1) ;
	    } /* end if (DEBOPEN) */
	} /* end if (getenv) */
	if (debugopen(dfn) >= 0) {
	    DEBUGPRINTF("ent\n") ;
	} /* end if */
	if (argc > 1) {
	    char	pbuf[plen + 1] ;
	    DEBUGPRINTF("args\n") ;
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *ap = argv[ai] ; ap[0]) {
	    	    DEBUGPRINTF("path> %s\n",ap) ;
	            printf("path> %s\n",ap) ;
		    rs = pathclean(pbuf,ap) ;
		    printf("rs=%d pbuf=>%s<\n",rs,pbuf) ;
		} /* end if (non-empty) */
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	DEBCLOSE ;
	return ex ;
} /* end subroutine (main) */


