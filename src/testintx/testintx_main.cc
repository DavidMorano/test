/* testintx_main SUPPORT (Test-Intx) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test the INTX object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_SZOF		0		/* size-of */
#define	CF_CARRY	0		/* carry-out */

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
#include	<dprintf.hh>

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/uintx.ccm"

import libutil ;			/* |lenstr(3u)| */
import uintx ;

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif
#ifndef	CF_SZOF
#define	CF_SZOF		0
#endif
#ifndef	CF_CARRY
#define	CF_CARRY	0
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

local int	test_carry() noex ;
local int	test1() noex ;
local int	test_cast() noex ;
local int	test_values() noex ;


/* local variables */

cint		fd_err		= FD_STDERR ;
cbool		f_debug		= CF_DEBUG ;
cbool		f_szof		= CF_SZOF ;
cbool		f_carry		= CF_CARRY ;


/* exported variables */


/* exported subroutines */

template <typename T> int printvar(T vv) noex {
    	cint olen = LINEBUFLEN ;
    	cint usz = szof(ulong) ;
    	cint nb = (szof(ulong) * CHAR_BIT) ;
	cint sz = szof(T) ;
	int		rs = SR_NOMEM ;
	DPRINTF("ent\n") ;
	if (char *obuf = new(nothrow) char [olen + 1] ; obuf) {
	    int ol{} ;
	    for (int i = 0 ; i < (sz / usz) ; i += 1) {
	        ulong b = ulongconv(vv) ;
	DPRINTF("loop-top\n") ;
		ol = snprintf(obuf,olen,"%02d %016lX",i,b) ;
	        rs = u_write(fd_err,obuf,ol) ;
	        vv <<= nb ;
	DPRINTF("loop-bot\n") ;
		if (rs < 0) break ;
	    } /* end for */
	    delete [] obuf ;
	    obuf = nullptr ;
	} /* end if (m-a-f) */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (printvar) */

int main(int,mainv,mainv) {
    	looksz		thing{} ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if_constexpr (f_szof) {
	    	printf("szof(thing)=%d\n",szof(thing)) ;
	    	printf("thing.a=%d\n",thing.a) ;
	    	printf("thing.b=%d\n",thing.b) ;
	}
	if_constexpr (f_carry) if (rs >= 0) {
	    rs = test_carry() ;

	} /* end if */
	if (rs >= 0) {
	    rs = test1() ;
	}
	if (rs >= 0) {
	    rs = test_cast() ;
	}
	if (rs >= 0) {
	    rs = test_values() ;
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

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

local int test1() noex {
    	uint256_t	a = 0x21 ;
	int		rs = SR_OK ;
	{
	    rs = printvar(a) ;
	}
	return rs ;
} /* end subroutine (test1) */

local int test_cast() noex {
    	uint256_t	a = 0x21 ;
	int		rs = SR_OK ;
	{
	    cint vv = int(a) ;
	    printf("cast=%d\n",vv) ;
	}
	return rs ;
} /* end subroutine (test_cast) */

constexpr int		values[] = {
    -1, -2, 3, 4
} ; /* end array */

local int test_values() noex {
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	for (cauto &e : values) {
	    uint256_t vx = e ;
	    {
	        cint vv = int(vx) ;
	        printf("cast=%d\n",vv) ;
	        rs = printvar(vx) ;
	    }
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_cast) */


