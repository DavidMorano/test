/* testenv_main SUPPORT (testenv) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test some aspect of environment handling */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* special debugging */

/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was written for use as a front-end for Korn
	Shell (KSH) commands that are compiled as stand-alone
	programs.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testenv

	Description:
	This is the front-end to make the various SHELL (KSH)
	built-in commands into stand-alone programs.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstring>		/* |strchr(3c)| */
#include	<string_view>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usupport.h>		/* |cfdec(3u)| */
#include	<getenver.h>
#include	<intceil.h>
#include	<mapex.h>
#include	<strkeycmp.h>
#include	<matkeystr.h>
#include	<strnul.hh>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |COLUMNS| + |DECBUFLEN| */
#include	<dprint.hh>		/* |DPRINTF(3u)| */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* special debugging */
#endif


/* imported namespaces */

using std::string_view ;		/* type */
using libu::cfdec ;			/* subroutine */


/* typ-defs */

typedef string_view	strview ;


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr MAPEXENT	mapexs[] = {
	{ SR_NOENT,	EX_NOUSER },
	{ SR_AGAIN,	EX_TEMPFAIL },
	{ SR_DEADLK,	EX_TEMPFAIL },
	{ SR_NOLCK,	EX_TEMPFAIL },
	{ SR_TXTBSY,	EX_TEMPFAIL },
	{ SR_ACCESS,	EX_NOPERM },
	{ SR_REMOTE,	EX_PROTOCOL },
	{ SR_NOSPC,	EX_TEMPFAIL },
	{ SR_INTR,	EX_INTR },
	{ SR_EXIT,	EX_TERM },
	{ SR_DOM,	EX_NOPROG },
	{ 0, 0 }
} ; /* end array (mapexs) */

constexpr cpcchar	tests[] = {
    "HOME",
    "PATH",
    "LIBPATH",
    "INCPATH"
} ; /* end array */

cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EX_INFO ;
	int		len = (COLUMNS-40) ;
	DPRINTF("ent\n") ;
	if (argc > 1) {
	    if (cchar *ap = argv[1] ; ap) {
	        if (int v ; cfdec(ap,-1,&v) >= 0) {
		    len = v ;
		}
	    }
	} /* end if (arguments) */
	{
	    printf("search-raw\n") ;
	    for (cauto &e : tests) {
		if (cint ei = matkeystr(envv,e,-1) ; ei >= 0) {
		    cchar *valp = envv[ei] ;
		    if (cchar *tp = strchr(envv[ei],'=') ; tp) {
			valp = (tp+1) ;
		    } /* end if */
		    {
			strnul es(valp,len) ;
		        printf("test=%s v=%s\n",e,ccp(es)) ;
		    }
		} else {
		    printf("test=%s not-found\n",e) ;
		} /* end if */
	    } /* end for */
	} /* end block */
	{
	    printf("getenver\n") ;
	    for (cauto &e : tests) {
		if (cchar *valp = getenver(e,-1) ; valp) {
			strnul es(valp,len) ;
		        printf("test=%s v=%s\n",e,ccp(es)) ;
		} else {
		    printf("test=%s not-found\n",e) ;
		} /* end if */
	    } /* end for */
	} /* end block */
	if ((rs < 0) && (ex == EX_OK)) {
	    ex = mapex(mapexs,rs) ;
	}
	DPRINTF("ret rs=%d ex=%u\n",rs,ex) ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


