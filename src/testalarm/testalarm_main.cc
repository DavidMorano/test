/* testalarm_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* main subroutine for several programs */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_SIGNAL	0

/* revision history:

	= 1988-02-01, David A­D­ Morano
	This subroutine was originally written.

	= 1988-02-01, David A­D­ Morano
	This subroutine was modified to not write out anything
	to standard output if the access time of the associated
	terminal has not been changed in 10 minutes.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This is a pretty much generic subroutine for several program.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<csignal>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<timestr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

import usigsets ;			/* |usigset(3u)| */

/* local defines */

#define	DEBUGFNVAR	"TESTALARM_DEBUGFN"
#define	NLOOPS		5

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif
#ifndef	CF_SIGNAL
#define	CF_SIGNAL	0
#endif


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

[[maybe_unused]]
local void	int_all(int)	noex ;
local int	process()	noex ;


/* local variables */

local sig_atomic_t	fsig		= 0 ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	if (char *cp = getenv(DEBUGFNVAR)) {
	    debugopen(cp) ;
	    DEBUGPRINTF("starting\n") ;
	}
	if (rs >= 0) {
	    cint how = SIG_UNBLOCK ;
	    if (con usigset nsm(SIGALARM) ; (rs = u_sigmask(how,&nsm)) >= 0) {
		SIGACTION nsa{} ;
		con sigset_t signalmask = 0 ;
		cint sig = SIGALRM ;
		nsa.sa_handler = int_all ;
		nsa.sa_mask = signalmask ;
		nsa.sa_flags = 0 ;
		if ((rs = u_sigaction(sig,&nsa)) >= 0) {
	    	    rs = process() ;
		} /* end if */
	    } /* end if (u_sigmask) */
	} /* end block */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local void int_all(int signum) noex {
    	(void) signum ;
    	fsig = signum ;
} /* end subroutine (intall) */

local int process() noex {
    	FILE		*ofp = stdout ;
	cnothrow	nt{} ;
	cint		tlen = TIMEBUFLEN ;
    	int		rs = SR_NOMEM ;
	DEBUGPRINTF("ent\n") ;
	if (char *tbuf = new(nt) char[tlen + 1]) {
    	    [[maybe_unused]] usigset	wsm(SIGALARM) ;
    	    cint	n = NLOOPS ;
	    rs = SR_OK ;
	    for (int i = 0 ; i < n ; i += 1) {
	        if ((rs = u_alarm(2)) >= 0) {
		    if ((rs = u_sigwait(&wsm)) >= 0) {
			custime dt = getustime ;
			DEBUGPRINTF("signo=%d\n",rs) ;
			timestr_log(dt,tbuf) ;
			fprintf(ofp,"%s\n",tbuf) ;
			fflush(ofp) ;
		    } /* end if (u_sigwait) */
	        } /* end if (u_alarm) */
		if (rs < 0) break ;
	    } /* end for */
	    delete [] tbuf ;
	} /* end if (new-char) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
    	return rs ;
} /* end subroutine (process) */


