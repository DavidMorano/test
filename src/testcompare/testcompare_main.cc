/* testcompare_main SUPPORT (testcompare) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test pogram */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 2020-09-10, David A­D­ Morano
	This subroutine was originally written to facilitate
	testing of software writen for RightCore Network Services.

*/

/* Copyright © 2020 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testcompare

	Description:
	This is a small test of the three­way-comparison operator
	(in C++).  Yes, I have been using it for some time now
	(since early C++20) but I want to test some other related
	things.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<compare>		/* C++STD */
#include	<stringview>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<strnul.hh>		/* LIBU */
#include	<intceil.h>		/* LIBU */
#include	<timeval.hh>		/* LIBU */
#include	<ucmpx.h>		/* LIBU */
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

using proc_f = int (*)() noex ;


/* external subroutines */


/* external variables */


/* local structures */

struct casecmp {
    	timeval	v1, v2 ;
	int	rc ;
} ; /* end sstruct (testcase) */


/* forward references */

local int cmpval(const ordcmp_weak &ro) noex {
    	int rc = 0 ;
	if (ro != 0) {
	    rc = (ro > 0) ? +1 : -1 ;
	}
    	return rc ;
} /* end subroutine (cmpval) */

local bool badrb(bool,int) noex ;
local bool badrc(int,int) noex ;

local int proc1() noex ;
local int proc2() noex ;
local int proc3() noex ;


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

constexpr casecmp	cmps[] = {
    { { 3, 4 }, { 3, 3 }, +1 },
    { { 3, 4 }, { 3, 5 }, -1 },
    { { 3, 4 }, { 3, 4 }, +0 },
    { { 3, 4 }, { 2, 6 }, +1 },
    { { 2, 4 }, { 3, 6 }, -1 },
    { { 0, 4 }, { 0, 6 }, -1 },
    { { 0, 6 }, { 0, 4 }, +1 },
    { { 0, 6 }, { 6, 4 }, -1 },
} ; /* end array (cmps) */

cint			tlen	= TIMEBUFLEN ;
cbool			f_debug = CF_DEBUG ;

constexpr proc_f	procs[] = {
    	&proc1,
    	&proc2,
    	&proc3
} ; /* end array */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	DPRINTF("ent\n") ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	if (rs >= 0) {
	    int c = 0 ;
	    for (cauto &fun : procs) {
	        rs = fun() ;
		c += rs ;
		if (rs < 0) break ;
	    } /* end for */
	    if (rs >= 0) rs = c ;
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DPRINTF("ret rs=%d ex=%u\n",rs,ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int proc1() noex {
    	int		rs = SR_OK ;
	    int c = 0 ;
	    int rc ;
	DPRINTF("ent\n") ;
	    for (cauto &e : cmps) {
		cauto v1 = e.v1 ;
		cauto v2 = e.v2 ;
		if (cauto ro = (v1 <=> v2) ; (rc = cmpval(ro)) != e.rc) {
		    printf("bad c=%d cmp.rc=%d e.rc=%d\n",c,rc,e.rc) ;
		    printf("lt=%u\n",(ro == typeof(ro)::less)) ;
		    printf("eq=%u\n",(ro == typeof(ro)::equivalent)) ;
		    printf("gt=%u\n",(ro == typeof(ro)::greater)) ;
		    rs = SR_BADE ;
		} /* end if (cmp) */
		c += 1 ;
		if (rs < 0) break ;
	    } /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (proc1) */

local int proc2() noex {
    	int		rs = SR_OK ;
	    int c = 0 ;
	DPRINTF("ent\n") ;
	    for (cauto &e : cmps) {
		cauto v1 = e.v1 ;
		cauto v2 = e.v2 ;
		if (cauto rb = (v1 > v2) ; badrb(rb,e.rc)) {
		    printf("bad c=%d rb=%u e.rc=%d\n",c,rb,e.rc) ;
		    rs = SR_BADE ;
		} /* end if (cmp) */
		c += 1 ;
		if (rs < 0) break ;
	    } /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (proc2) */

local int proc3() noex {
    	int		rs = SR_OK ;
	int c = 0 ;
	DPRINTF("ent\n") ;
	for (cauto &e : cmps) {
	    cauto v1 = e.v1 ;
	    cauto v2 = e.v2 ;
	    if (int rc = cmptimeval(&v1,&v2) ; badrc(rc,e.rc)) {
		printf("bad c=%d rc=%d e.rc=%d\n",c,rc,e.rc) ;
		rs = SR_BADE ;
	    } /* end if (cmp) */
	    c += 1 ;
	    if (rs < 0) break ;
	} /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (proc3) */

local bool badrb(bool rb,int rc) noex {
	return (rb) ? (rc <= 0) : (rc > 0) ;
} /* end subroutine (badrb) */

local bool badrc(int rc,int erc) noex {
    	bool fbad = false ;
	if (rc > 0) {
	    fbad = (erc <= 0) ;
	} else if (rc < 0) {
	    fbad = (erc > 0) ;
	} else {
	    fbad = (erc != 0) ;
	}
	return fbad ;
} /* end subroutine (badrc) */


