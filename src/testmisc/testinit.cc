/* testinit SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++98 */

/* test program initialization */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A�D� Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright � 2000 David A�D� Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


#ifndef	eol
#define	eol	'\n'
#endif

using std::cout ;			/* variable */
using std::cerr ;			/* variable */

typedef const char *const 	*mainv ;

struct multi {
	int	a ;
	int	b ;
	int	c ;
} ;

static int	mkterms() noexcept ;

static multi	aa = { 1 } ;

extern "C" {
    static void __attribute__ ((constructor)) init() noexcept {
	printf("init\n") ;
    }
}

int main(int argc,mainv argv,mainv) {
	static cint	srs = mkterms() ;
	static cchar	*under = getenv("_") ;
	int		rs ;
	int		ex = 0 ;
	if ((rs = srs) >= 0) {
	    if ((argc > 0) && argv[0]) {
		cout << "argz=" << argv[0] << eol ;
	    }
	    if (under) {
		cout << "under=" << under << eol ;
	    }
	    printf("aa.a=%08x aa.b=%08x\n",aa.a,aa.b) ;
	    {
		cchar	*pn = getprogname() ;
		if (pn) {
		    cout << "pn=" << pn << eol ; 
		} else {		
		    cerr << "pn=NULL" << eol ;
		}
	    } /* end block */
	} /* end if */
	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */

extern "C" {
    static void __attribute__ ((destructor)) fini() noexcept {
	printf("fini\n") ;
    }
}

static int mkterms() noexcept {
    cout << "mkterms\n" ;
    return 0 ;
}


