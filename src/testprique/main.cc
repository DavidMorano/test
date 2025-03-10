/* main SUPPORT (testprique) */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* test the PRIQUE object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |EXIT_{xx}| */
#include	<cstdio>
#include	<iostream>
#include	<new>			/* |nothrow(3c++)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<localmisc.h>

import prique ;


/* local defines */

#define	NENTS		1000

#ifndef	eol
#define	eol		'\n'
#endif


/* imported namespaces */

using std::nullptr_t ;			/* type */
using std::cerr ;			/* variable */
using std::cout ;			/* variable */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct prique_ent {
	time_t		val ;
    } ;
}

typedef prique<prique_ent>	priobj ;


/* forward references */

static int ents_load(prique_ent *) noex ;
static int ents_ins(prique_ent *,priobj *) noex ;
static int ents_present(prique_ent *,priobj *) noex ;
static int ents_get(prique_ent *,priobj *) noex ;
static int ents_have(prique_ent *,prique_ent *) noex ;
static int ents_cents(prique_ent *,priobj *) noex ;
static int ents_enum(prique_ent *,priobj *) noex ;
static int ents_rem(prique_ent *,priobj *) noex ;
static int ents_czero(prique_ent *,priobj *) noex ;


/* local variables */

typedef int (*ents_f)(prique_ent *,priobj *) noex ;

#ifdef	COMMENT
constexpr ents_f	funcs[] = {
	ents_ins,
	ents_present,
	ents_get,
	ents_cents,
	ents_enum,
	ents_rem,
	ents_czero
} ;
#else /* COMMENT */
constexpr ents_f	funcs[] = {
	ents_ins
} ;
#endif /* COMMENT */
constexpr int		nents = NENTS ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cnullptr	np{} ;
	prique_ent	*ents ;
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	cerr << "ent\n" ;
	if ((ents = new(nothrow) prique_ent[nents]) != np) {
	    if ((rs = ents_load(ents)) >= 0) {
	        prique<prique_ent>	t ;
	        if ((rs = t.start) >= 0) {
		    for (cauto &f : funcs) {
			rs = f(ents,&t) ;
			if (rs < 0) break ;
		    } /* end for */
	            rs1 = t.finish ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (prique) */
	    } /* end if (ents_load) */
	    delete [] ents ;
	} /* end if (m-a-f) */
	cerr << "exiting rs=" << rs << '\n' ;
	if (rs < 0) ex = EXIT_FAILURE ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

static int ents_load(prique_ent *ents) noex {
	custime		sti = time(nullptr) ;
	int		rs = SR_OK ;
	cerr << "ents_load: ent" << eol ;
	{
	    uint	us = uint(sti & INT_MAX) ;
	    srand(us) ;
	}
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    ents[i].val = rand() ;
	} /* end for */
	cerr << "ents_load: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_load) */

static int ents_ins(prique_ent *ents,priobj *tp) noex {
	int		rs = SR_OK ;
	cerr << "ents_ins: ent" << eol ;
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    rs = tp->ins(ents+i) ;
	} /* end for */
	cerr << "ents_ins: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_ins) */

#ifdef	COMMENT

static int ents_present(prique_ent *ents,priobj *tp) noex {
	int		rs = SR_OK ;
	cerr << "ents_present: ent" << eol ;
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    cvoid	*addr = ents[i].addr ;
	    rs = tp->present(addr) ;
	} /* end for */
	cerr << "ents_present: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_present) */

static int ents_get(prique_ent *ents,priobj *tp) noex {
	int		rs = SR_OK ;
	cerr << "ents_get: ent" << eol ;
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    prique_ent	e ;
	    cvoid	*addr = ents[i].addr ;
	    if ((rs = tp->get(addr,&e)) >= 0) {
		rs = ents_have(ents,&e) ;
	    }
	} /* end for */
	cerr << "ents_get: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_get) */

static int ents_have(prique_ent *ents,prique_ent *ep) noex {
	int		rs = SR_OK ;
	bool		f = false ;
	for (int i = 0 ; (!f) && (i < nents) ; i += 1) {
	    if (ents[i].addr == ep->addr) {
		f = (ents[i].asz == ep->asz) ;
	    }
	} /* end for */
	if (!f) rs = SR_NOTFOUND ;
	return rs ;
}
/* end subroutine (ents_have) */

static int ents_rem(prique_ent *ents,priobj *tp) noex {
	int		rs = SR_OK ;
	cerr << "ents_rem: ent" << eol ;
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    cvoid	*addr = ents[i].addr ;
	    rs = tp->rem(addr) ;
	} /* end for */
	cerr << "ents_rem: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_get) */

static int ents_cents(prique_ent *,priobj *tp) noex {
	int		rs ;
	if ((rs = tp->count) >= 0) {
	    cint	c = rs ;
	    rs = SR_BADFMT ;
	    if (c == nents) {
		rs = SR_OK ;
	    }
	}
	return rs ;
}
/* end subroutine (ents_cents) */

static int ents_enum(prique_ent *ents,priobj *tp) noex {
	int		rs ;
	int		rs1 ;
	prique_cur	cur ;
	cerr << "ents_enum: ent" << eol ;
	if ((rs = tp->curbegin(&cur)) >= 0) {
	    prique_ent		e ;
	    while ((rs = tp->curenum(&cur,&e)) > 0) {
		rs = ents_have(ents,&e) ;
		if (rs < 0) break ;
	    } /* end while */
	    rs1 = tp->curend(&cur) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (prique-cur) */
	cerr << "ents_enum: ret rs=" << rs << eol ;
	return rs ;
}

static int ents_czero(prique_ent *,priobj *tp) noex {
	int		rs ;
	if ((rs = tp->count) >= 0) {
	    cint	c = rs ;
	    rs = SR_BADFMT ;
	    if (c == 0) {
		rs = SR_OK ;
	    }
	}
	return rs ;
}
/* end subroutine (ents_czero) */

#endif /* COMMENT */


