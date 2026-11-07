/* testucgetpid SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_FORK		1		/* test |uc_fork(3uc)| */

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
#ifndef	CF_FORK
#define	CF_FORK		1		/* test |uc_fork(3uc)| */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cbool			f_debug		= CF_DEBUG ;
cbool			f_fork		= CF_FORK ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	FILE		*ofp = stdout ;
	int		rs = SR_OK ;
	int		rs1 ;
	(void) argc ;
	(void) argv ;
	if (cchar *cp = getourenv(envv,VARDFN)) {
	    rs = DEBUGOPEN(cp) ;
	    DEBUGPRINTF("starting fd=%d\n",rs) ;
	} /* end if (debugging) */
	if (rs >= 0) {
	    if (lockrw lo ; (rs = lo.create) >= 0) {
	        DEBUGPRINTF("lo.create() rs=%d\n",rs) ;
		{
		    if ((rs = lo.lockrd) >= 0) {
	                DEBUGPRINTF("lo.lockrd() rs=%d\n",rs) ;
			rs = SR_OK ;
		    } /* end if */
	            DEBUGPRINTF("lo.lockrd-out rs=%d\n",rs) ;
		} /* end block */
		rs1 = lo.destroy ;
		if (rs >= 0) rs = rs1 ;
	        DEBUGPRINTF("lo.destroy() rs=%d\n",rs) ;
	    } /* end if (lockrw) */
	} /* end if (ok) */
	if (rs >= 0) {
	    pid_t pid = getpid() ;
	    fprintf(ofp,"getpid() pid=%d\n",int(pid)) ;
	    rs = uc_getpid() ;
	    fprintf(ofp,"p uc_getpid() rs=%d\n",rs) ;
	    fflush(ofp) ;
	} /* end */
	if (f_fork && (rs >= 0)) {
	    DEBUGPRINTF("fork()\n") ;
	    fflush(ofp) ;
	    if ((rs = uc_fork()) == 0) { /* child */
	        DEBUGPRINTF("child rs=%d\n",rs) ;
	        rs = uc_getpid() ;
	        fprintf(ofp,"c uc_getpid() rs=%d\n",rs) ;
	        u_exit(0) ;
	    } else if (rs > 0) { /* parent */
	        int	cs ;
	        DEBUGPRINTF("parent rs=%d\n",rs) ;
	        u_wait(&cs) ;
	        fprintf(ofp,"cs=%u\n",cs) ;
	    } else {
	        DEBUGPRINTF("fork-err rs=%d\n",rs) ;
	        pid_t pid = getpid() ;
	        DEBUGPRINTF("fork-err pid=%d\n",int(pid)) ;
	    } /* end if */
	    DEBUGPRINTF("fork-out rs=%d\n",rs) ;
	} /* end if (ok) */
	if (rs < 0) {
	    fprintf(ofp,"failure (%d)\n",rs) ;
	} /* end if (error) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	DEBUGCLOSE ;
	return 0 ;
} /* end subroutine (main) */


/* local subroutines */


