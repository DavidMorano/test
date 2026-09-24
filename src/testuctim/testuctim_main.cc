/* testuctim_main SUPPORT */
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
#include	<usupport.h>		/* LIBU */
#include	<uctimx.h>		/* LIBUC */
#include	<psem.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

import usigsets ;			/* |usigset(3u)| */

/* local defines */

#define	DEBUGFNVAR	"TESTUCTIM_DEBUGFN"
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
local void	int_all(int)		noex ;
local int	loop(psem *,int)	noex ;
extern "C" {
    local int	fun(void *,int,int) noex ;
} /* end extern (C) */


/* local variables */

cint		tlen		= TIMEBUFLEN ;
cbool		f_debug		= CF_DEBUG ;
sig_atomic_t	fsig		= 0 ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		rs1 ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	if (char *cp = getenv(DEBUGFNVAR)) {
	    debugopen(cp) ;
	    DEBUGPRINTF("starting\n") ;
	}
	if (rs >= 0) {
	    if (psem nsem ; (rs = nsem.create) >= 0) {
	        uctimxnote note{} ;
		note.psemp = &nsem ;
	        note.notf = fun ;	/* notification function */
	        if ((rs = uc_timxcreate(&note)) >= 0) {
		    cint tid = rs ;
		    {
	    	        DEBUGPRINTF("-> loop\n") ;
	    	        rs = loop(&nsem,tid) ;
	    	        DEBUGPRINTF("loop() rs=%d\n",rs) ;
		    }
		    rs1 = uc_timxdestroy(tid) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (uc_timx) */
	        DEBUGPRINTF("uctimx-out rs=%d\n",rs) ;
	        rs1 = nsem.destroy ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (psem) */
	    DEBUGPRINTF("psem-out rs=%d\n",rs) ;
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

local int loop(psem *psemp,int tid) noex {
    	FILE		*ofp = stdout ;
	cnullptr	np{} ;
	cnothrow	nt{} ;
	cint		tint = 2 ;
    	int		rs = SR_NOMEM ;
	DEBUGPRINTF("ent\n") ;
	if (char *tbuf = new(nt) char[tlen + 1]) {
	    ustime	dt = getustime ;
    	    cint	n = NLOOPS ;
	    rs = SR_OK ;
	    for (int i = 0 ; i < n ; i += 1) {
	DEBUGPRINTF("-> uc_timxset\n") ;
	        if ((rs = uc_timxset(tid,np,(dt + tint))) >= 0) {
	DEBUGPRINTF("-> psemwait\n") ;
		    rs = psemp->wait ;
	DEBUGPRINTF("psemwait() rs=%d\n",rs) ;
		    dt = getustime ;
		    timestr_log(dt,tbuf) ;
		    fprintf(ofp,"wake-up %s\n",tbuf) ;
	    	    fflush(ofp) ;
	        } /* end if (uc_timexset) */
	DEBUGPRINTF("uctimerset-out rs=%d\n",rs) ;
		if (rs < 0) break ;
	    } /* end for */
	    delete [] tbuf ;
	} /* end if (new-char) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
    	return rs ;
} /* end subroutine (process) */

local int fun(void *objp,int id,int ag) noex {
    	FILE		*ofp = stdout ;
	cnothrow	nt{} ;
	custime dt = getustime ;
	int		rs = SR_OK ;
    	(void) objp ;
	(void) id ;
	(void) ag ;
	if (char *tbuf = new(nt) char[tlen + 1]) {
	    timestr_log(dt,tbuf) ;
	    fprintf(ofp,"%s\n",tbuf) ;
	    fflush(ofp) ;
	    delete [] tbuf ;
	} /* end if (new-char) */
	return rs ;
} /* end subroutine (fun) */


