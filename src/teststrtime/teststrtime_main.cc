/* teststrtime_main SUPPORT (teststrtime) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test some aspect of environment handling */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* special debugging */

/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was written for use as a front-end for Korn
	Shell (KSH) commands that are compiled as stand-alone
	programs.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	teststrtime

	Description:
	This is a small test of the |strtime{x}(3uc)| subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD |strchr(3c)| */
#include	<string_view>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfdec(3u)| */
#include	<usyscalls.h>		/* LIBU */
#include	<strnul.hh>		/* LIBU */
#include	<intceil.h>		/* LIBU */
#include	<ucgetx.h>		/* LIBUC |uc_gettimeofday(3uc)| */
#include	<strkeycmp.h>		/* LIBUC */
#include	<matkeystr.h>		/* LIBUC */
#include	<timeval.hh>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |COLUMNS| + |DECBUFLEN| */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */
#include	<strtime.h>		/* LIBUC */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* special debugging */
#endif


/* imported namespaces */


/* type-defs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr mapex_map	mapexs[] = {
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

cint			tlen	= TIMEBUFLEN ;
cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	DPRINTF("ent\n") ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	if (rs >= 0) {
	    if (TIMEVAL tv ; (rs = uc_gettimeofday(&tv,np)) >= 0) {
		if (char tbuf[tlen + 1] ; strtimeval(tv,tbuf) != np) {
		    printf("tv=%s\n",tbuf) ;
		} /* end if (strtimeval) */
	    } /* end if (timeval_load) */
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DPRINTF("ret rs=%d ex=%u\n",rs,ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


