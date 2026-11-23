/* testgetnode_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program (TESTGETNODEDOMAIN) */
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
	This little diddy test the |getdnodedmain(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<netdb.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<getnodedomain.h>	/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<deb.hh>		/* LIBU |DEBPRINTF(3u)| */
#include	<prognamevar.hh>	/* LIBDAM */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/deb.ccm"

import libutil ;			/* |lenstr(3u)| */
import deb ;				/* debugging */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif

#define	VARDFN		"TESTGETNODE_DFN"


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cint			nlen		= NODENAMELEN ;
cint			dlen		= MAXHOSTNAMELEN ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
    	cnullptr	np{} ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (ccharp cp = getourenv(envv,VARDFN)) {
	    rs = DEBOPEN(cp) ;
	    DEBPRINTF("starting pn=%s rs=%d\n",ccp(pn),rs) ;
	} /* end if (debugging) */
	if (rs >= 0) {
	    char	nbuf[nlen + 1] = {} ;
	    char	dbuf[dlen + 1] = {} ;
	    if ((rs = getnodedomain(nbuf,dbuf)) >= 0) {
		printf("  node=%s\n",nbuf) ;
		printf("domain=%s\n",dbuf) ;
	    } /* end if (getnodedomain) */
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
	DEBPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBCLOSE ;
	return ex ;
} /* end subroutine (main) */


