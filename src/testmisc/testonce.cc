/* testonce SUPPORT (Test-Once) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test calling once */
/* version %I% last-modified %G% */

#define	CF_SYNC		0	

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* |getpid(2)| */
#include	<libproc.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<syncstream>		/* |osyncstream(3c++)| */
#include	<thread>
#include	<mutex>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>


#define	NTHREADS	6

#ifndef	eol
#define	eol	'\n'
#endif

typedef std::thread::id		threadid ;

using std::thread ;
using std::osyncstream ;

using std::cout ;			/* variable */
using std::cerr ;			/* variable */

#if	CF_SYNC
std::osyncstream	sout(cout) ;
#else
std::ostream		sout(cout.rdbuf()) ;
#endif /* COMMENT */

std::mutex		omx ;

static int oncesub() noex {
    	osyncstream(cout) << "oncesub: sleeping\n" ;
    	sleep(4) ;
    	osyncstream(cout) << "oncesub: waking\n" ;
	return 1 ;
}

static int oncer() noex {
    	static cint	rso = oncesub() ;
	return rso ;
}

static void tryer() noex {
    	threadid	id = std::this_thread::get_id() ;
	[[maybe_unused]] int		rso = 0 ;
	osyncstream(cout) << "thread=" << id << " ent\n" ;
	sleep(2) ;
    	for (int i = 0 ; i < NTHREADS ; i += 1) {
	    osyncstream(cout) <<  "thread=" << id << " trying\n" ;
	    rso = oncer() ;
	    osyncstream(cout) << id << " rso=" << rso << eol ;
	    sleep(1) ;
	}
	    osyncstream(sout) << "thread=" << id << " ret\n" ;
}

int main(int argc,mainv argv,mainv) {
    	int		ex = 0 ;
	int		rs = 0 ;
	thread		ts[5] ;
    	osyncstream(cout) << "main: call\n" ;
	for (int i = 0 ; i < NTHREADS ; i += 1) {
	    ts[i] = thread(tryer) ;
	}
	{
	    sleep(1) ;
	    tryer() ;
	    sleep(1) ;
	}
	for (int i = 0 ; i < NTHREADS ; i += 1) {
	    ts[i].join() ;
	}
    	osyncstream(cout) << "main: ret\n" ;
	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


