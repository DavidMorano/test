/* testgetprogroot_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* get the |getprogroot(3abeyance)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<new>			/* CSTD placement-new */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ubufdefs.h>		/* LIBU */
#include	<vardefs.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#include	"getprogroot.h"

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/uconstants.ccm"

import libutil ;			/* |lenstr(3u)| */
import uconstants ;			/* |varname(3u)| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr cpcchar	prns[] = {
    	VARPRPCS,
	VARPRLOCAL,
	VARPRUSRLOCAL,
	VARPRNCMP,
	VARPRAST,
	VARPRGNU,
	VARPREXTRA,
	nullptr
} ; /* end array (prns) */

cint			maxpathlen	= MAXPATHLEN ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv) {
    	cnullptr	np{} ;
    	cnothrow	nt{} ;
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	DPRINTF("ent\n") ;
	if (argc > 1) {
	    rs = SR_NOMEM ;
	    if (char *rbuf = new(nt) char[maxpathlen + 1] ; rbuf) {
		rs = SR_OK ;
	        for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
	            cchar *ap = argv[ai] ;
		    DPRINTF("ap=%s\n",ap) ;
		    rs = getprogroot(rbuf,np,np,ap) ;
		    if (rs < 0) break ;
		    printf("----\n") ;
		    printf("prog=%s\n",ap) ;
		    printf("pr=%s\n",rbuf) ;
	        } /* end for */
		delete [] rbuf ;
	    } /* end if (m-a-f) */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


