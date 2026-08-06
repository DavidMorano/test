/* testdecltype_main SUPPORT (testdecltype) */
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
	testdecltype

	Description:
	This is the front-end to make the various SHELL (KSH)
	built-in commands into stand-alone programs.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD |strchr(3c)| */
#include	<string_view>		/* C++STD */
#include	<type_traits>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfdec(3u)| */
#include	<usyscalls.h>		/* LIBU */
#include	<intceil.h>		/* LIBU */
#include	<strkeycmp.h>		/* LIBU */
#include	<matkeystr.h>		/* LIBU */
#include	<strnul.hh>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |COLUMNS| + |DECBUFLEN| */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */


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

local typeof(auto) retval() noex {
    cint	val = 42 ;
    return (val+1) ;
} /* end subroutine */


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

cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	DPRINTF("ent\n") ;
	if (rs >= 0) {
	    cauto val = retval() ;
	    (void) val ;
	    assert_static(std::is_same_v<typeof(val),cint>) ;
	} /* end if (ok) */
	{
	    int *ap = nullptr ;
	    {
		decltype(*ap) v = rs ;
		(void) v ;
	    }
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	}
	DPRINTF("ret rs=%d ex=%u\n",rs,ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


