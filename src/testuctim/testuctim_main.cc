/* testuctim_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_SIGNAL	0

/* revision history:

	= 1988-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This is a small test of the |uc_tim{x}(3uc)| subroutines.

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
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<mutex>			/* C++STD */
#include	<iostream>		/* C++STD */
#include	<syncstream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<uctim.h>		/* LIBUC */
#include	<psem.h>		/* LIBUC */
#include	<strtime.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

import usigsets ;			/* |usigset(3u)| */

/* local defines */

#define	DEBUGFNVAR	"TESTUCTIM_DEBUGFN"
#define	NLOOPS		4

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif
#ifndef	CF_SIGNAL
#define	CF_SIGNAL	0
#endif


/* imported namespaces */

using std::mutex ;			/* type */
using std::cout ;			/* variable */


/* local typedefs */



/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int	loop(psem *,int)	noex ;
extern "C" {
    local int	fun(void *,int,int) noex ;
} /* end extern (C) */


/* local variables */

std::osyncstream	sout(std::cout) ;
mutex			omtx ;
cint			tlen		= TIMEBUFLEN ;
cbool			f_debug		= CF_DEBUG ;


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
	} /* end */
	if (rs >= 0) {
	    if (psem nsem ; (rs = nsem.create) >= 0) {
	        uctimnote note{} ;
		note.psemp = &nsem ;
	        note.notfun = fun ;	/* notification function pointer */
	        note.notarg = 42 ;	/* notification function argument */
	        if ((rs = uc_timcreate(&note)) >= 0) {
		    cint tid = rs ;
		    {
	    	        DEBUGPRINTF("-> loop\n") ;
	    	        rs = loop(&nsem,tid) ;
	    	        DEBUGPRINTF("loop() rs=%d\n",rs) ;
		    }
		    rs1 = uc_timdestroy(tid) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (uc_tim) */
	        DEBUGPRINTF("uctim-out rs=%d\n",rs) ;
	        rs1 = nsem.destroy ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (psem) */
	    DEBUGPRINTF("psem-out rs=%d\n",rs) ;
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int loop(psem *psemp,int tid) noex {
	cnullptr	np{} ;
	cnothrow	nt{} ;
	cint		tint = 2 ;
    	int		rs = SR_NOMEM ;
	DEBUGPRINTF("ent\n") ;
	if (char *tbuf = new(nt) char[tlen + 1]) {
	    itimerval	itv ;
	    timeval	otv{} ;
	    timeval	ntv{} ;
	    ustime	dt = getustime ;
    	    cint	n = NLOOPS ;
	    if ((rs = itimerval_load(&itv,&otv,&ntv)) >= 0) {
	        for (int i = 0 ; i < n ; i += 1) {
	            DEBUGPRINTF("-> uc_timset\n") ;
		    itv.it_value.tv_sec = (dt + tint) ;
	            if ((rs = uc_timset(tid,np,&itv)) >= 0) {
	                DEBUGPRINTF("-> psemwait\n") ;
		        rs = psemp->wait ;
	                DEBUGPRINTF("psemwait() rs=%d\n",rs) ;
		        dt = getustime ;
		        strtime_log(dt,tbuf) ;
		        omtx.lock() ;
		        cout << "wake-up " << tbuf << eol ;
		        cout.flush() ;
	    	        omtx.unlock() ;
	            } /* end if (uc_timeset) */
	            DEBUGPRINTF("uctimerset-out rs=%d\n",rs) ;
		    if (rs < 0) break ;
	        } /* end for */
	    } /* end if (itimerval_load) */
	    delete [] tbuf ;
	} /* end if (new-char) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
    	return rs ;
} /* end subroutine (process) */

local int fun(void *objp,int id,int ag) noex {
	cnothrow	nt{} ;
	custime		dt = getustime ;
	int		rs = SR_OK ;
    	(void) objp ;
	(void) id ;
	(void) ag ;
	if (char *tbuf = new(nt) char[tlen + 1]) {
	    strtime_log(dt,tbuf) ;
	    omtx.lock() ;
	    cout << "    fun " << tbuf << " a=" << ag << eol ;
	    cout.flush() ;
	    omtx.unlock() ;
	    delete [] tbuf ;
	} /* end if (new-char) */
	return rs ;
} /* end subroutine (fun) */


