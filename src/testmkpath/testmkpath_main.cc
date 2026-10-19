/* testmkpath_main SUPPORT */
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


/* local variables */

cint		plen		= MAXPATHLEN ;
cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* external subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	int		ex = EXIT_SUCCESS ;
    	int		rs = SR_OK ;
	(void) envv ;
	if (argc > 1) {
	    char pbuf[plen + 1] ;
	    membset(pbuf,plen,'a') ;
	    switch (argc - 1) {
	    case 1:
	        rs = mkpath(pbuf,argv[1]) ;
	        break ;
	    case 2:
	        rs = mkpath(pbuf,argv[1],argv[2]) ;
	        break ;
	    case 3:
	        rs = mkpath(pbuf,argv[1],argv[2],argv[3]) ;
	        break ;
	    case 4:
	        rs = mkpath(pbuf,argv[1],argv[2],argv[3],argv[4]) ;
	        break ;
	    } /* end switch */
	    printf("rs=%d pbuf=%s\n",rs,pbuf) ;
	} /* end if */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


