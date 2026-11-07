/* testsncpy_main SUPPORT (testsncpy) */
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
	testsncpy

	Description:
	This is a small test of the |sncpy(3u)| subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD |strchr(3c)| + |sncpy(3c)| */
#include	<string_view>		/* C++STD */
#include	<algorithm>		/* C++STD |min(3c++)| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<sncpy.h>		/* LIBU */
#include	<snadd.h>		/* LIBU */
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

using std::min ;			/* subroutine */


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
cint			flen	= TIMEBUFLEN ;
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
	    int rl{} ;
	    char rbuf[rlen + 1] = {} ;
	    char fbuf[rlen + 1] = {} ;
	    switch (argc - 1) {
	    case 1:
		if (oklen(argc,av)) {
		    rl = sncpy(rbuf,rlen,av[1]) ;
		    sncpylc(fbuf,rlen,av[1]) ;
		}
		break ;
	    case 2:
		if (oklen(argc,av)) {
		    rl = sncpy(rbuf,rlen,av[1],av[2]) ;
		    sncpylc(fbuf,rlen,av[1],av[2]) ;
		}
		break ;
	    case 3:
		if (oklen(argc,av)) {
		    rl = sncpy(rbuf,rlen,av[1],av[2],av[3]) ;
		    sncpylc(fbuf,rlen,av[1],av[2],av[3]) ;
		}
		break ;
	    case 4:
		if (oklen(argc,av)) {
		    rl = sncpy(rbuf,rlen,av[1],av[2],av[3],av[4]) ;
		    sncpylc(fbuf,rlen,av[1],av[2],av[3],av[4]) ;
		}
		break ;
	    } /* end switch */
	    if (rbuf[0]) {
	        printf("rl=%d rbuf=»%s«\n",rl,rbuf) ;
	        printf("rl=%d fbuf=»%s«\n",rl,fbuf) ;
	    } else {
	        printf("rl=%d overflow\n",rl) ;
		rs = SR_BADE ;
	    } /* end if */
	return rs ;
} /* end subroutine (proc1) */

local int proc2(int argc,con mainv argv) noex {
    	cint		al_max = 4 ;
    	cint		al_min = 16 ;
    	int		rs = SR_OK ;
	int rl = 0 ;
	int minl = 0 ;
	int maxl = 0 ;
	char rbuf[rlen + 1] = {} ;
	char minbuf[flen + 1] = {} ;
	char maxbuf[flen + 1] = {} ;
	for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
	    cchar *ap = argv[ai] ;
	    {
	        rs = snadd(rbuf,rlen,rl,ap) ;
	        rl += rs ;
	    } 
	    if (rs >= 0) {
		cint al = lenstr(ap) ;
	        rs = snadd(minbuf,flen,minl,ap,min(al,al_max)) ;
	        minl += rs ;
	    } /* end if (ok) */
	    if (rs >= 0) {
	        rs = snadd(maxbuf,flen,maxl,ap,al_min) ;
	        maxl += rs ;
	    } /* end if (ok) */
	    if (rs < 0) break ;
	} /* end for */
	if (rs >= 0) {
	        printf("proc2:   rl=%d   rbuf=»%s«\n",rl,rbuf) ;
	        printf("proc2: minl=%d minbuf=»%s«\n",minl,minbuf) ;
	        printf("proc2: maxl=%d maxbuf=»%s«\n",maxl,maxbuf) ;
	} else {
	        printf("proc2: bad rs=%d\n",rs) ;
	}
	return rs ;
} /* end subroutine (proc2) */


