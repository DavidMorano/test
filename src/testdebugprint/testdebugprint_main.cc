/* testdebugprint_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |debugptinf(3debug)| subroutine and some friends */
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
	This program tests the LIBEBUG facility.  This library is
	more complcated than it should be, and likely has more bugs
	in it than it should have.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ugetx.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<prognamevar.hh>	/* LIBDAM */

#define	VARDFN		"TESTDEBUGPRINT_DFN"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif

extern int sub() noex ;

cbool			f_debug		= CF_DEBUG ;

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (cchar *cp = getourenv(envv,VARDFN) ; cp) {
	    if ((rs = DEBUGOPEN(cp)) >= 0) {
	        rs = DEBUGPRINTF("starting DFD=%d\n",rs) ;
	    }
	} /* end */
	if (rs >= 0) {
	    rs = DEBUGPRINTF("pn=>%s<\n",ccp(pn)) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    cchar *msg = "here\nis" ;
	    rs = DEBUGPRINTF("msg=>%s<\n",msg) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    rs = sub() ;
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	printf("ret ex=%d rs=%d\n",ex,rs) ;
	DEBUGPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


