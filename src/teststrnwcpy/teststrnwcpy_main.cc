/* teststrnwcpy_main SUPPORT (teststrnwcpy) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* special debugging */

/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was originally written to facilitate
	testing of software writen for RightCore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	teststrnwcpy

	Description:
	This is a small test of the |strnwcpy(3u)| subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<strn.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |COLUMNS| + |DECBUFLEN| */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

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

local void fillbuf(char *bp,int bl) noex {
    	for (int i = 0 ; i < bl ; i += 1) {
	    bp[i] = charconv(i + 1) ;
	} /* end for */
} /* end */

local bool hasallzero(cc *sp,int sl) noex {
    	bool f = true ;
	for (int i = 0 ; i < sl ; i += 1) {
	    f = (sp[i] == '\0') ;
	    if (!f) break ;
	} /* end for */
    	return f ;
} /* end */


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
	    cint dsz = rlen ;
	    char rbuf[rlen + 1] ;
	    endp = rbuf ;
	    fillbuf(rbuf,rlen) ;
	    switch (argc - 1) {
	    case 1:
		if (oklen(argc,av)) {
		    endp = strnwcpy(rbuf,rlen,av[1],dsz) ;
		}
		break ;
	    case 2:
		if (oklen(argc,av)) {
		    endp = strnwcpy(rbuf,rlen,av[1],av[2],dsz) ;
		}
		break ;
	    case 3:
		if (oklen(argc,av)) {
		    endp = strnwcpy(rbuf,rlen,av[1],av[2],av[3],dsz) ;
		}
		break ;
	    case 4:
		if (oklen(argc,av)) {
		    endp = strnwcpy(rbuf,rlen,av[1],av[2],av[3],av[4],dsz) ;
		}
		break ;
	    } /* end switch */
	    if (endp && rbuf[0]) {
		printf("rl=%d rbuf=>%s<\n",intconv(endp - rbuf),rbuf) ;
		if (cint el = intconv((rbuf + rlen) - endp) ; el > 0) {
	            if (! hasallzero(endp,el)) {
		        printf("non-zero\n") ;
		    } /* end if (non-zero) */
		} /* end if */
	    } else {
	        printf("rl=%d overflow\n",intconv(endp - rbuf)) ;
	    } /* end if */
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


