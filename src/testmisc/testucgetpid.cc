/* testucgetpid SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Description:
	This tests the |ucgetpid(3u)| variable.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdarg>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<ucfork.h>		/* LIBUC */
#include	<ucgetpid.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBUC */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */


/* local defines */


#define	VARDFN		"TESTUCGETPID_DFN"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	FILE		*ofp = stdout ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (cchar *cp ; cp = getourenv(envv,VARDFN)) {
	    rs = DEBUGOPEN(cp) ;
	    DEBUGPRINTF("starting fd=%d\n",rs) ;
	} /* end if (debugging) */
	if (rs >= 0) {
	    rs = uc_getpid() ;
	    fprintf(ofp,"p ugetpid() rs=%d\n",rs) ;
	    fflush(ofp) ;
	}
	if (rs >= 0) {
	    DEBUGPRINTF("fork()\n") ;
	    if ((rs = uc_fork()) == 0) { /* child */
	        rs = uc_getpid() ;
	        fprintf(ofp,"c uc_getpid() rs=%d\n",rs) ;
	        u_exit(0) ;
	    } else if (rs > 0) { /* parent */
	        int	cs ;
	        u_wait(&cs) ;
	        fprintf(ofp,"cs=%u\n",cs) ;
	    } /* end if */
	} /* end if (ok) */
	if (rs < 0) {
	    fprintf(ofp,"failure (%d)\n",rs) ;
	}
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	DEBUGCLOSE ;
	return 0 ;
} /* end subroutine (main) */


/* local subroutines */


