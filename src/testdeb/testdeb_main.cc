/* testdeb_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |debugptinf(3debug)| subroutine and some friends */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_PRINT	0		/* normal print */
#define	CF_TESTHEX	0		/* test |mkhex(3u)| */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Description:
	This program test the EB module.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<deb.hh>		/* LIBU |DEBPRINTF(3u)| */
#include	<dprint.hh>		/* LIBU ¦DPRINT(3u)| */

#include	"mkhex.h"		/* *local* */

#pragma		GCC dependency		"mod/deb.ccm"

import deb ;

#define	DEBFN		"testdeb.deb"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif
#ifndef	CF_PRINT
#define	CF_PRINT	1		/* normal print */
#endif
#ifndef	CF_TESTHEX
#define	CF_TESTHEX	0		/* test |mkhex(3u)| */
#endif

using libu::strdcpy ;			/* subroutine */

local int testmkhex() noex ;

cbool			f_debug		= CF_DEBUG ;
cbool			f_print		= CF_PRINT ;
cbool			f_testhex	= CF_TESTHEX ;

int main(int argc,con mainv argv,con mainv envv) {
    	cint		slen = 4 ;
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	int		c = 0 ; /* return-value */
	(void) argc ;
	(void) argv ;
	(void) envv ;
	DEBOPEN(DEBFN) ;
	DEBPRINTF("ent slen=%d\n",slen) ;
	if_constexpr (f_testhex) {
	    if (rs >= 0) {
	        rs = testmkhex() ;
	    } /* end if (ok) */
	} /* end if_constexpr (f_testhex) */
	if (rs >= 0) {
	    char sbuf[slen + 1] = {} ;
	    rs = DEBPRINTHEX(-1,sbuf,slen) ;
	    c += rs ;
	    if_constexpr (f_print) {
		printf("deb=%d\n",rs) ;
	    }
	    if (rs >= 0) {
	        strdcpy(sbuf,slen,"1234") ;
	        rs = DEBPRINTHEX(-1,sbuf,slen) ;
		c += rs ;
	    if_constexpr (f_print) {
		printf("deb=%d\n",rs) ;
	    }
	    } /* end if (ok) */
	    if (rs >= 0) rs = c ;
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int testmkhex() noex {
    	cint		rlen = 8 ;
    	int		rs = SR_OK ;
	int		rl = 0 ; /* return-value */
	{
	    char rbuf[rlen + 1] ;
	    if (rs >= 0) ylikely {
	        rs = mkhexstr(rbuf,rlen,"1234") ;
	        rl += rs ;
	        DPRINTF("REG mkhexstr() rs=%d\n",rs) ;
	        DPRINTF("REG rbuf=%s\n",rbuf) ;
	    } /* end if */
	    if (rs >= 0) ylikely {
	        rs = mkhexstr(rbuf,rlen,"12345") ;
	        DPRINTF("OVF mkhexstr() rs=%d\n",rs) ;
	        DPRINTF("OVF rbuf=%s\n",rbuf) ;
		if (rs == SR_OVERFLOW) {
		    rs = SR_OK ;
		}
	    } /* end if */
	} /* end block */
	return (rs >= 0) ? rl : rs ;
} /* end subroutine (procmkhex) */


