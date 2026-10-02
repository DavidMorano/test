/* teststpcpy_main SUPPORT (teststpcpy) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
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
	teststpcpy

	Description:
	This is a small test of the |stpcpy(3u)| subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD |strchr(3c)| + |stpcpy(3c)| */
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

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

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

local bool oklen(int,con mainv) noex ;


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

cint			rlen	= TIMEBUFLEN ;
cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	char *endp{} ;
	DPRINTF("ent\n") ;
	(void) envv ;
	if (argc > 1) {
	    con mainv av = argv ;
	    char rbuf[rlen + 1] = {} ;
	    endp = rbuf ;
	    switch (argc) {
	    case 2:
		if (oklen(argc,av)) {
		    endp = stpcpy(rbuf,av[1]) ;
		}
		break ;
	    case 3:
		if (oklen(argc,av)) {
		    endp = stpcpy(rbuf,av[1],av[2]) ;
		}
		break ;
	    case 4:
		if (oklen(argc,av)) {
		    endp = stpcpy(rbuf,av[1],av[2],av[3]) ;
		}
		break ;
	    } /* end switch */
	    if (rbuf[0]) {
	        printf("rl=%d rbuf=>%s<\n",intconv(endp - rbuf),rbuf) ;
	    } else {
	        printf("rl=%d overflow\n",intconv(endp - rbuf)) ;
	    }
	} /* end for (arguments) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DPRINTF("ret rs=%d ex=%u\n",rs,ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local bool oklen(int ac,con mainv av) noex {
	int len = 0 ;
	for (int ai = 1 ; (ai < ac) && av[ai] ; ai += 1) {
	    len += lenstr(av[ai]) ;
	} /* end for */
	return (len <= rlen) ;
} /* end subroutine (oklen) */


