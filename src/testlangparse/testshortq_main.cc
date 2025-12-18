/* testshortq_main SUPPORT (testshortq) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the SHORTQ object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debug */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

	= 2025-11-03, David A-D- Morano
	I am updating this to the latest API of the SHORTQ object.

*/

/* Copyright © 1998,2025 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Description:
	I test the SHORTQ object.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |atoi(3c)| */
#include	<cstdarg>
#include	<cstdio>		/* |printf(3c)| */
#include	<iostream>
#include	<string>
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<new>			/* placement-new */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<getfdfile.h>		/* |FD_STDERR| */
#include	<ccfile.hh>
#include	<strnul.hh>
#include	<six.h>			/* |sichr(3uc)| */
#include	<sfx.h>			/* |sfchr(3uc)| */
#include	<rmx.h>			/* |rmeol(3uc)| */
#include	<ascii.h>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |eol| + |MAXLINELEN| */
#include	<debprintf.h>		/* |DEBPRINTF| */

#include	<shortq.h>

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency	"mod/debug.ccm"

import libutil ;			/* |getlenstr(3u)| */
import debug ;

/* local defines */

#ifndef	MAXLINELEN
#define	MAXLINELEN	100
#endif


/* imported namespaces */

using std::string ;			/* type */
using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* local typedefs */


/* external subroutines */


/* exported variables */


/* local structures */


/* forward references */

local int procfile(shortq *,cchar *) noex ;
local int procln(shortq *,cchar *,int) noex ;
local int procout(shortq *,int) noex ;

template<typename T> local int rmeol(T *sp,int µsl) noex {
    	int		rl = -1 ;
	if (int sl ; (sl = getlen(sp,µsl)) > 0) {
	    auto isend = [] (T ch) noex -> bool {
		return ((ch == CH_NL) || (ch == '_')) ;
	    } ;
	    while ((sl > 0) && isend(sp[sl - 1])) {
		sl -= 1 ;
	    }
	    rl = sl ;
	} /* end if (non-null) */
    	return rl ;
} /* end subroutine-template (rmeol) */

template<typename T> local int sichr(T *sp,int µsl,int chs) noex {
    	int		rl = -1 ;
	bool		f = false ;
	if (int sl ; (sl = getlen(sp,µsl)) >= 0) {
	    for (rl = 0 ; rl < sl ; rl += 1) {
		f = (sp[rl] != chs) ;
		if (! f) break ;
	    } /* end for */
	} /* end if (non-null) */
    	return (f) ? rl : -1 ;
} /* end subroutine-template (sichr) */


/* local variables */

cchar		pn[] = "test" ;
cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
    	constexpr int	dfd = (f_debug) ? FD_STDERR : -1 ;
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	int		rs1 ;
	debfd(dfd) ;
	DEBPRINTF("ent\n") ;
	if (argc > 1) {
	    DEBPRINTF("argc=%d\n",argc) ;
	    if (shortq pa ; (rs = pa.start) >= 0) ylikely {
	        for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		    cchar	*fn = argv[ai] ;
		    rs = procfile(&pa,fn) ;
		    if (rs < 0) break ;
	        } /* end for */
	        rs1 = pa.finish ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (shortq) */
	} /* end if (arguments) */
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	DEBPRINTF("ret rs=%d\n",rs) ;
	DEBPRINTF("exit ex=%d\n",ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procfile(shortq *lpp,cchar *fn) noex {
    	cnothrow	nt{} ;
    	cnullptr	np{} ;
	cint		llen = LINEBUFLEN ;
    	int		rs = SR_FAULT ;
	int		rs1 ;
	int		wlen = 0 ;
	if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) ylikely {
	    if (ccfile rf ; (rs = rf.open(fn,"r",0)) >= 0) ylikely {
		while ((rs = rf.readln(lbuf,llen)) > 0) {
		    if ((rs = procln(lpp,lbuf,rs)) > 0) {
			rs = procout(lpp,llen) ;
			wlen += rs ;
		    }
		    if (rs < 0) break ;
		} /* end while */
		rs1 = rf.close ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (ccfile) */
	    delete [] lbuf ;
	} /* end if (new-char) */
	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (procfile) */

local int procln(shortq *lpp,cchar *lp,int ll) noex {
    	int		rs ;
	int		c = 0 ;
	if ((rs = getlenstr(lp,ll)) > 0) {
	    cint sl = rs ;
	    for (int i = 0 ; (rs >= 0) && (i < sl) ; i += 1) {
		short sw = (lp[i] & UCHAR_MAX) ;
	        rs = lpp->ins(sw) ;
	        c += rs ;
	    } /* end if */
	} /* end if (getlenstr) */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (procln) */

local int pro(short *sbp,int sbl) noex {
    	int		rs = SR_OK ;
	int		wlen = 0 ;
	DEBPRINTF("ent sbl=%d\n",sbl) ;
	{
	    cint ll = rmeol(sbp,sbl) ;
	    for (int i = 0 ; i < ll ; i += 1) {
		char chc = char(sbp[i]) ;
		cout << chc ;
		wlen += 1 ;
	    } /* end for */
	    cout << eol ;
	} /* end block */
	DEBPRINTF("ret rs=%d wlen=%d\n",rs,wlen) ;
	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (pro) */

local int procout(shortq *lpp,int slen) noex {
    	cnullptr	np{} ;
    	cnothrow	nt{} ;
	cint		chs = CH_NL ;
    	int		rs = SR_OK ;
	int		wlen = 0 ;
	DEBPRINTF("ent\n") ;
	if (short *sbuf ; (sbuf = new(nt) short [slen + 1]) != np) {
	    while ((rs = lpp->remread(sbuf,slen)) > 0) {
		int	sl = rs ;
		short	*sp = sbuf ;
		DEBPRINTF("read rs=%d\n",rs) ;
		for (int si ; (si = sichr(sp,sl,chs)) >= 0 ; ) {
		    {
		        rs = pro(sp,si) ;
		        wlen += rs ;
		    }
		    sp += (si + 1) ;
		    sl -= (si + 1) ;
		    if (rs < 0) break ;
		} /* end for */
		if ((rs >= 0) && (sl > 0)) {
		        rs = pro(sp,sl) ;
		        wlen += rs ;
		} /* end if */
		if (rs < 0) break ;
	    } /* end while */
	    delete [] sbuf ;
	} /* end if (new-short) */
	DEBPRINTF("ret rs=%d\n",rs) ;
	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (procout) */


