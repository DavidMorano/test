/* testio_main SUPPORT (testio) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1999-02-01, David A­D­ Morano
	This is a little (big) hack to try to test some parts of
	the C++ IO package functionality.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/************************************************************************

  	Descryption:
	This is a test program for the C+ IO functionality.

*************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<pwd.h>			/* POSIX® */
#include	<string>		/* C++STD */
#include	<sstream>		/* C++STD |stringstream| */
#include	<iostream>		/* C++STD */
#include	<iomanip>		/* C++STD */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<prognamevar.hh>	/* LIBDAM */


/* local defines */

#define	TESTIO_DFN	"testio.deb"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif


/* imported namespaces */

using std::string ;			/* type */
using std::streambuf ;			/* type */
using std::stringstream ;		/* type */
using std::ostringstream ;		/* type */
using std::ostream ;			/* type */
using std::cout ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct thing {
    	int	a ;
	thing() noex : a(0) { } ;
	thing(int ª) noex : a(ª) { } ;
    } ; /* end struct (thing) */
} /* end namespce (thing) */


/* forward references */

ostream &operator % (ostream &ol,const thing &ot) noex {
    	ol << ot.a ;
	return ol ;
} /* end */

local int procstr() noex ;
local int procbuf() noex ;


/* local variables */

constexpr mapex_map	mapexs[] = {
	{ SR_NOENT,	EX_NOUSER	},
	{ SR_AGAIN,	EX_TEMPFAIL	},
	{ SR_DEADLK,	EX_TEMPFAIL	},
	{ SR_NOLCK,	EX_TEMPFAIL	},
	{ SR_TXTBSY,	EX_TEMPFAIL	},
	{ SR_ACCESS,	EX_NOPERM	},
	{ SR_REMOTE,	EX_PROTOCOL	},
	{ SR_NOSPC,	EX_TEMPFAIL	},
	{ SR_INTR,	EX_INTR		},
	{ SR_EXIT,	EX_TERM		},
	{ SR_DOM,	EX_NOPROG	},
	{ 0, 0 }
} ; /* end array (mapexs) */

cchar			dfn[]		= TESTIO_DFN ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	if (DEBUGOPEN(dfn) >= 0) {
	    DEBUGPRINTF("ent pn=%s\n",ccp(pn)) ;
	}
	if ((rs >= 0) && (argc > 1)) {
	    thing item ;
	    for (int ai = 1 ; ai < argc ; ai += 1) {
		ccharp ap = argv[ai] ;
		cout << ap << "=" ;
		cout % item << eol ;
		if (rs < 0) break ;
	    } /* end for */
	    rs = SR_OK ;
	} /* end if (arguments) */
	if (rs >= 0) {
	    rs = procstr() ;
	} /* end if (procstr) */
	if (rs >= 0) {
	    rs = procbuf() ;
	} /* end if (procbuf) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DEBUGPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procstr() noex {
    	ostringstream sso ;
    	int rs = SR_OK ;
	sso << "Hello" ;
	sso << " " ;
	sso << "world!" << eol ;
	{
	    string str ;
	    str = sso.str() ;
	    cout << str ;
	}
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (procstr) */

local int procbuf() noex {
    	int rs = SR_OK ;
    	ostringstream sso ;
	{
    	    streambuf *sbufp = cout.rdbuf() ; /* <- save */
	    cout.rdbuf(sso.rdbuf()) ;
	    {
	        cout << "Hello" ;
	        cout << " " ;
	        cout << "world!" << eol ;
	    } /* end block */
	    cout.rdbuf(sbufp) ; /* <- restore */
	} /* end block */
	{
	    string str ;
	    str = sso.str() ;
	    cout << str ;
	}
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (procbuf) */


