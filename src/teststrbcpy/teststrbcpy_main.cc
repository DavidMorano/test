/* teststrbcpy_main SUPPORT (teststrbcpy) */
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
	teststrbcpy

	Description:
	This is a small test of the |strbcpy(3u)| subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<string_view>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<strbcpy.h>		/* LIBU */
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

local int proc1(int,con mainv) noex ;
local int proc2(int,con mainv) noex ;

cint			rlen	= TIMEBUFLEN ;
cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	DPRINTF("ent\n") ;
	(void) envv ;
	if (argc > 1) {
	    rs = proc1(argc,argv) ;
	} /* end */
	if (rs >= 0) {
	    rs = proc2(argc,argv) ;
	} /* end if (ok) */
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

local int proc1(int argc,con mainv argv) noex {
    	int		rs = SR_OK ;
	    con mainv av = argv ;
	char *endp{} ;
	    char rbuf[rlen + 1] = {} ;
	    char fbuf[rlen + 1] = {} ;
	    endp = rbuf ;
	    switch (argc - 1) {
	    case 1:
		if (oklen(argc,av)) {
		    endp = strbcpy(rbuf,rlen,av[1]) ;
		    strbcpylc(fbuf,rlen,av[1]) ;
		}
		break ;
	    case 2:
		if (oklen(argc,av)) {
		    endp = strbcpy(rbuf,rlen,av[1],av[2]) ;
		    strbcpylc(fbuf,rlen,av[1],av[2]) ;
		}
		break ;
	    case 3:
		if (oklen(argc,av)) {
		    endp = strbcpy(rbuf,rlen,av[1],av[2],av[3]) ;
		    strbcpylc(fbuf,rlen,av[1],av[2],av[3]) ;
		}
		break ;
	    case 4:
		if (oklen(argc,av)) {
		    endp = strbcpy(rbuf,rlen,av[1],av[2],av[3],av[4]) ;
		    strbcpylc(fbuf,rlen,av[1],av[2],av[3],av[4]) ;
		}
		break ;
	    } /* end switch */
	    if (rbuf[0]) {
	        printf("rl=%d rbuf=>%s<\n",intconv(endp - rbuf),rbuf) ;
	        printf("rl=%d fbuf=>%s<\n",intconv(endp - rbuf),fbuf) ;
	    } else {
	        printf("rl=%d overflow\n",intconv(endp - rbuf)) ;
		rs = SR_BADE ;
	    } /* end if */
	return rs ;
} /* end subroutine (proc1) */

local int proc2(int,con mainv) noex {
    	int		rs = SR_OK ;
	return rs ;
} /* end subroutine (proc2) */


