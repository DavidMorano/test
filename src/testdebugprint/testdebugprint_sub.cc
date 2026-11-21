/* testdebugprint_sub SUPPORT */
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

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif

cbool			f_debug		= CF_DEBUG ;

int sub() noex {
    	int		rs = SR_OK ;
	if (rs >= 0) {
	    rs = DEBUGPRINTF("Hello world!\n") ;
	} /* end if (ok) */
	return rs ;
} /* end subroutine (sub) */


