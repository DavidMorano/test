/* testintx_main SUPPORT (Test-Intx) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test the INTX object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_DIVS		1		/* divisions of */
#define	CF_DIVSHORT	1		/* short-division */
#define	CF_SZOF		0		/* size-of */
#define	CF_CARRY	0		/* carry-out */
#define	CF_PRVAR	0		/* prvar */
#define	CF_CAST		0		/* cast */
#define	CF_VALUES	0		/* values */
#define	CF_SHIFT	0		/* shift */
#define	CF_MULTIPLY	1		/* multiply */
#define	CF_MULTIPLIER	1		/* multiplier */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<new>			/* |nothrow| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<iostream>
#include	<iomanip>
#include	<syncstream>		/* |osyncstream(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usupport.h>
#include	<usysutility.hh>	/* |snprintf(3u)| */
#include	<getfdfile.h>
#include	<localmisc.h>
#include	<libf.h>		/* LIBF */
#include	<dprintf.hh>		/* debugging */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import intext ;				/* |uint256_t| */
import testint ;			/* |uint256_t| */
import loadvals ;			/* |loadval()| */
import arithsteps ;


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif
#ifndef	CF_DIVS
#define	CF_DIVS		0
#endif
#ifndef	CF_SZOF
#define	CF_SZOF		0
#endif
#ifndef	CF_CARRY
#define	CF_CARRY	0
#endif
#ifndef	CF_CAST
#define	CF_CAST		0		/* cast */
#endif
#ifndef	CF_PRVAR
#define	CF_PRVAR	0		/* prvar */
#endif
#ifndef	CF_SHIFT
#define	CF_SHIFT	0		/* shift */
#endif
#ifndef	CF_VALUES
#define	CF_VALUES	0		/* values */
#endif
#ifndef	CF_MULTIPLIER
#define	CF_MULTIPLIER	1		/* multiplier */
#endif


/* local namespaces */

using libu::snprintf ;			/* subroutine */
using std::cout ;			/* variable */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct looksz {
    	inline static cint 	a = 1 ;
	int		b ;
} ;


/* forward references */

local int	test_divs() noex ;
local int	test_divshort() noex ;
local int	test_carry() noex ;
local int	test_prvar() noex ;
local int	test_cast() noex ;
local int	test_values() noex ;
local int	test_shift() noex ;
local int	test_multiply() noex ;

#if	CF_MULTIPLIER
local int	test_multiplier() noex ;
#endif /* CF_MULTIPLIER */


/* local variables */

cint		fd_err		= FD_STDERR ;
cbool		f_debug		= CF_DEBUG ;
cbool		f_divs		= CF_DIVS ;
cbool		f_divshort	= CF_DIVSHORT ;
cbool		f_szof		= CF_SZOF ;
cbool		f_carry		= CF_CARRY ;
cbool		f_prvar		= CF_PRVAR ;
cbool		f_cast		= CF_CAST ;
cbool		f_values	= CF_VALUES ;
cbool		f_shift		= CF_SHIFT ;
cbool		f_multiply	= CF_MULTIPLY ;
cbool		f_multiplier	= CF_MULTIPLIER ;


/* exported variables */


/* exported subroutines */

template <typename T> local int printvar(T vv) noex {
    	cint olen = LINEBUFLEN ;
    	cint usz = szof(ulong) ;
    	cint nb = (szof(ulong) * CHAR_BIT) ;
	cint sz = szof(T) ;
	int		rs = SR_NOMEM ;
	(void) vv ;
	(void) olen ;
	(void) usz ;
	(void) sz ;
	(void) nb ;
	if (char *obuf = new(nothrow) char [olen + 1] ; obuf) {
	    cchar *fmt = "%02d %016lX-%016lX" ;
	    ulong lo ;
	    ulong hi ;
	    for (int i = 0 ; i < (sz / usz / 2) ; i += 1) {
	        lo = ulongconv(vv) ;
	        vv >>= nb ;
	        hi = ulongconv(vv) ;
	        vv >>= nb ;
		if ((rs = snprintf(obuf,olen,fmt,i,hi,lo)) >= 0) {
	            rs = printf("prvar: %s\n",obuf) ;
		}
		if (rs < 0) break ;
	    } /* end for */
	    delete [] obuf ;
	    obuf = nullptr ;
	} /* end if (m-a-f) */
	return rs ;
} /* end subroutine (printvar) */

int mainsub(int,mainv,mainv) noex {
    	static cchar *	varhome = getenv("HOME") ;
    	looksz		thing{} ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	if (varhome) {
	    	printf("HOME=%s\n",varhome) ;
	}
	if_constexpr (f_szof) {
	    	printf("szof(thing)=%d\n",szof(thing)) ;
	    	printf("thing.a=%d\n",thing.a) ;
	    	printf("thing.b=%d\n",thing.b) ;
	}
	if_constexpr (f_carry) if (rs >= 0) {
	    rs = test_carry() ;
	} /* end if */
	if_constexpr (f_divs) if (rs >= 0) {
	    rs = test_divs() ;
	} /* end if */
	if_constexpr (f_divshort) if (rs >= 0) {
	    rs = test_divshort() ;
	} /* end if */
	if (rs >= 0) {
	    if_constexpr (f_prvar) {
	        rs = test_prvar() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_cast) {
	        rs = test_cast() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_values) {
	        rs = test_values() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_shift) {
	        rs = test_shift() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_multiply) {
	        rs = test_multiply() ;
	    }
	}
#if	CF_MULTIPLIER
	if (rs >= 0) {
	    if_constexpr (f_multiplier) {
	        rs = test_multiplier() ;
	    }
	}
#endif /* CF_MULTIPLIER */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	DPRINTF("ent ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (mainsub) */

int main(int argc,mainv argv,mainv envv) {
    	cnothrow	nt{} ;
    	cint		sl = MINSIGSTKSZ +  SIGSTKSZ ;
    	int		ex = EXIT_FAILURE ;
	int		rs ;
	int		rs1 ;
	if (char *sp = new(nt) char [sl] ; sp) {
	    stack_t stk{} ;
	    stk.ss_sp = sp ;
	    stk.ss_size = sl ;
            stk.ss_flags = 0 ;
	    if ((rs = u_sigaltstack(&stk,nullptr)) >= 0) {
	        {
                    ex = mainsub(argc,argv,envv) ;
	        }
                stk.ss_flags = SS_DISABLE ;
	        rs1 = u_sigaltstack(&stk,nullptr) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if u_sigaltstack) */
	    delete [] sp ;
	    sp = nullptr ;
	} /* end if (m-a-f) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

constexpr int	dds[] = { 0xFF, 0x01, 0x10 } ;

struct divs_stat {
    int		rem ;
    int		quo ;
    int		div ;
} ;

local int test_divs() noex {
    	divs_stat	stat = {} ;
    	int		rs = SR_OK ;
	int		remax{} ;
	int		quo{} ;
	int		rem{} ;
	for (cauto &e : dds) {
	    for (int d = 1 ; d < (UCHAR_MAX + 1) ; ++d) {
		quo = e / d ;
		rem = e % d ;
		if (rem > remax) {
		    remax = rem ;
		    stat.rem = rem ;
		    stat.quo = quo ;
		    stat.div = d ;
		}
	    } /* end for */
	} /* end for */
	printf("remax=%d\n",remax) ;
	printf("stat quo=%d rem=%d div=%d\n",stat.quo,stat.rem,stat.div) ;
	{
	    divs_stat ds{} ;
	    for (int d = 1 ; d < (UCHAR_MAX + 1) ; ++d) {
		int end = ((232 * 256) + 255) ;
	        div_t	res = div(end,d) ;
		if (res.rem > ds.rem) {
		    ds.rem = res.rem ;
		    ds.quo = res.quot ;
		    ds.div = d ;
		}
	    } /* end for */
	    printf("ds quo=%d rem=%d div=%d\n",ds.quo,ds.rem,ds.div) ;
	} /* end block */
	return rs ;
} /* end subroutine (test_divs) */

local int test_divshort() noex {
    	cint		n = 4 ;
	const uint	dividend = 713991273 ;
    	uchar		dd[4] ;
    	uchar		q[4] = {} ;
    	int		rs = SR_OK ;
	uint		quo0{}, quo1{} ;
	uchar		rem0{}, rem1{} ;
	DPRINTF("ent\n") ;
	for (int i = 1 ; i < (UCHAR_MAX + 1) ; ++i) {
	    uchar d = uchar(i) ;
	    loadval(n,dd,dividend) ;
    	    rem0 = vdivshort(n,q,dd,d) ;
	    mkv(&quo0,q) ;
	    quo1 = dividend / d ;
	    rem1 = uchar(dividend % d) ;
	    if ((quo0 != quo1) || (rem0 != rem1)) {
	        printf("mismatch\n") ;
	        printf("%u quo=%d rem=%d\n",d,quo0,rem0) ;
	        printf("%u quo=%d rem=%d\n",d,quo1,rem1) ;
		rs = SR_BADFMT ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_divshort) */

local int test_carry() noex {
    	int		rs = SR_OK ;
	    uint	r, co ;
	    cchar	*fmt = 
	    	        "%02x %02x = %02x + %02x %02x\n" ;
	    printf("co  r    j    i ci\n") ;
	    for (uint ci = 0 ; ci < 2 ; ci += 1) {
	        for (uint i = 0 ; i < 4 ; i += 1) {
	            for (uint j = 0 ; j < 4 ; j += 1) {
		        r = j + i + ci ;
		        co = (r >> 2) ;
	    	        printf(fmt,co,(r & 3),j,i,ci) ;
		    }
	        }
	    }
	return rs ;
} /* end subroutine (test_carry) */

local int test_prvar() noex {
    	uint256_t	a = 0x21 ;
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	{
	    rs = printvar(a) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_prvar) */

local int test_cast() noex {
    	uint256_t	a = 0x21 ;
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	{
	    cint vv = int(a) ;
	    printf("cast=%d\n",vv) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_cast) */

constexpr int		values[] = {
    -2, 3
} ; /* end array */

local int test_values() noex {
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	for (cauto &e : values) {
	    uint256_t	vx = e ;
	    {
	        cint vv = int(vx) ;
	        printf("cast=%d\n",vv) ;
	        rs = printvar(vx) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_values) */

local int test_shift() noex {
	int		rs = SR_OK ;
	uint256_t	v = 3 ;
	DPRINTF("ent\n") ;
	v <<= (128 + 20) ;
	for (int i = 0 ; i < 8 ; i += 1) {
	    {
	        rs = printvar(v) ;
		v = v.ashr(20) | uint256_t(0) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_shift) */

local int test_multiply() noex {
	int		rs = SR_OK ;
	uint256_t	m = (16 * 5) ;
	uint256_t	v = 0x0303 ;
	DPRINTF("ent\n") ;
	for (int i = 0 ; i < 8 ; i += 1) {
	    {
	        rs = printvar(v) ;
		v = v * m ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_multiply) */

#if	CF_MULTIPLIER
local int test_multiplier() noex {
    	int		rs = SR_OK ;
	utest64_t	m = (16 * 5) ;
	utest64_t	v = 0x0303 ;
	ulong		vcheck = 0x0303 ;
	DPRINTF("ent\n") ;
	for (int i = 0 ; i < 8 ; i += 1) {
	    {
		culong pv = v ;
	        printf("a=%018lx\n",pv) ;
		rs = (pv != vcheck) ? SR_BADFMT : 0 ;
		v = v * m ;
		vcheck *= (16 * 5)  ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_multiplier) */
#endif /* CF_MULTIPLIER */


