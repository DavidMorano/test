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
#include	<functional>		/* |hash(3c++)| */
#include	<iostream>
#include	<new>			/* |nothrow(3c++)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<localmisc.h>

import prique ;


/* local defines */

#define	NENTS		10

#ifndef	eol
#define	eol		'\n'
#endif


/* imported namespaces */

using std::nullptr_t ;			/* type */
using std::hash ;			/* type */
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
	bool operator > (const prique_ent &o) const noex {
	    return (val > o.val) ;
	} ;
	bool operator < (const prique_ent &o) const noex {
	    return (val < o.val) ;
	} ;
	bool operator == (const prique_ent &o) const noex {
	    return (val == o.val) ;
	} ;
    } ;
}

namespace std {
    template<> struct hash<prique_ent> {
        size_t operator () (const prique_ent &e) const noex {
	    return e.val ;
        } ;
    } ;
}

typedef prique<prique_ent>	priobj ;


/* forward references */

static int ents_load(prique_ent *) noex ;
static int ents_ins(prique_ent *,priobj *) noex ;
static int ents_cents(prique_ent *,priobj *) noex ;
static int ents_rem(prique_ent *,priobj *) noex ;
static int ents_czero(prique_ent *,priobj *) noex ;


/* local variables */

typedef int (*ents_f)(prique_ent *,priobj *) noex ;

constexpr ents_f	funcs[] = {
	ents_ins,
	ents_cents,
	ents_rem,
	ents_czero
} ;

constexpr int		nents = NENTS ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cnullptr	np{} ;
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	cerr << "ent\n" ;
	if (prique_ent *ents ; (ents = new(nothrow) prique_ent[nents]) != np) {
	    if ((rs = ents_load(ents)) >= 0) {
	        prique<prique_ent>	t ;
	        if ((rs = t.start) >= 0) {
		    for (cauto &f : funcs) {
			rs = f(ents,&t) ;
			cerr << "main: loop rs= " << rs << eol ;
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

static int ents_cents(prique_ent *,priobj *tp) noex {
	int		rs ;
	if ((rs = tp->count) >= 0) {
	    cint	c = rs ;
	    rs = SR_BADFMT ;
	    if (c == nents) {
		rs = SR_OK ;
	    }
	}
	cerr << "ents_cents: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_cents) */

static int ents_rem(prique_ent *ents,priobj *tp) noex {
    	cint		rsn = SR_NOENT ;
	int		rs = SR_OK ;
	int		rs1 ;
	(void) ents ;
	cerr << "ents_rem: ent" << eol ;
	for (prique_ent e ; (rs1 = tp->rem(&e)) >= 0 ; ) {
	    cerr << "ents_rem: val= " << e.val << eol ;
	} /* end for */
	if ((rs >= 0) && (rs1 != rsn)) rs = rs1 ;
	cerr << "ents_rem: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_rem) */

static int ents_czero(prique_ent *,priobj *tp) noex {
	int		rs ;
	if ((rs = tp->count) >= 0) {
	    cint	c = rs ;
	    rs = SR_BADFMT ;
	    if (c == 0) {
		rs = SR_OK ;
	    }
	}
	cerr << "ents_czero: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_czero) */


