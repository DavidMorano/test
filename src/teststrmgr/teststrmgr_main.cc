/* teststrmgr_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |mkpath{3uc)| subroutine */
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
	This program tests the |mkpath(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mkpathx.h>		/* LIBUC */
#include	<strmgr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int proc1(int,con mainv argv) noex ;
local int proc2(int,con mainv argv) noex ;


/* local variables */

cint		plen		= MAXPATHLEN ;
cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* external subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
	(void) envv ;
	DPRINTF("ent\n") ;
	if ((rs >= 0) && (argc > 1)) {
	    rs = proc1(argc,argv) ;
	} /* end if */
	if ((rs >= 0) && (argc > 1)) {
	    rs = proc2(argc,argv) ;
	} /* end if */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int proc1(int argc,con mainv argv) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	int		pl = 0 ; /* accummulator */
	    char pbuf[plen + 1] ;
	    membset(pbuf,plen,'a') ;
	    if (strmgr mo ; (rs = mo.start(pbuf,plen)) >= 0) {
	        for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		    cchar *ap = argv[ai] ;
		    rs = mo.str(ap) ;
		    pl += rs ;
		    if (rs < 0) break ;
	        } /* end for */
		rs1 = mo.finish ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (strmgr) */
	    printf("rs=%d pl=%d pbuf=%s\n",rs,pl,pbuf) ;
	return rs ;
} /* end subrutine (proc1) */

local int proc2(int argc,con mainv argv) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	int		pl = 0 ;
	char pbuf[plen + 1] ;
	membset(pbuf,plen,'a') ;
	if (strmgr mo ; (rs = mo.start(pbuf,plen)) >= 0) {
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		    cchar *ap = argv[ai] ;
		    rs = mo.chr(ap[0]) ;
		    pl += rs ;
		    if (rs < 0) break ;
	    } /* end for */
	    rs1 = mo.finish ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (strmgr) */
	printf("rs=%d pl=%d pbuf=%s\n",rs,pl,pbuf) ;
	return rs ;
} /* end subrutine (proc1) */


