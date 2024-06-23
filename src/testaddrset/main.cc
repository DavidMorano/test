/* main SUPPORT (testaddrset) */
/* lang=C++20 */

/* test the ADDRSET object */
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
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	"addrset.hh"


/* local defines */

#define	NENTS		1000

#ifndef	eol
#define	eol		'\n'
#endif


/* imported namespaces */

using namespace	std ;


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int ents_load(addrset_ent *) noex ;
static int ents_ins(addrset_ent *,addrset *) noex ;
static int ents_present(addrset_ent *,addrset *) noex ;
static int ents_get(addrset_ent *,addrset *) noex ;
static int ents_have(addrset_ent *,addrset_ent *) noex ;
static int ents_rem(addrset_ent *,addrset *) noex ;


/* local variables */

constexpr int		nents = NENTS ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	addrset_ent	*ents ;
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	cerr << "ent\n" ;
	if ((ents = new(nothrow) addrset_ent[nents + 1]) != nullptr) {
	    if ((rs = ents_load(ents)) >= 0) {
	        addrset	t ;
	        if ((rs = t.start) >= 0) {
		    if ((rs = ents_ins(ents,&t)) >= 0) {
			if ((rs = ents_present(ents,&t)) >= 0) {
			    if ((rs = ents_get(ents,&t)) >= 0) {
				if ((rs = t.count) >= 0) {
				    cint	c = rs ;
				    rs = SR_BADFMT ;
				    if (c == nents) {
					rs = ents_rem(ents,&t) ;
				    }
				}
			    } /* end if (ents_get) */
			} /* end if (ents_present) */
		    } /* end if (ents_ins) */
	            rs1 = t.finish ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (addrset) */
	    } /* end if (ents_load) */
	    delete [] ents ;
	} /* end if (m-a-f) */
	cerr << "exiting rs=" << rs << '\n' ;
	if (rs < 0) ex = EXIT_FAILURE ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

static int ents_load(addrset_ent *ents) noex {
	custime		sti = time(nullptr) ;
	size_t		sz ;
	int		rs = SR_OK ;
	cerr << "ents_load: ent" << eol ;
	{
	    uint	us = uint(sti & INT_MAX) ;
	    srand(us) ;
	}
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    cvoid	*addr = cast_reinterpret<voidp>(i+1) ;
	    int		rn = rand() ;
	    sz = size_t(rn % 100000) + 1 ;
	    ents[i].addr = addr ;
	    ents[i].asize = sz ;
	} /* end for */
	cerr << "ents_load: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_load) */

static int ents_ins(addrset_ent *ents,addrset *tp) noex {
	int		rs = SR_OK ;
	cerr << "ents_ins: ent" << eol ;
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    cvoid	*addr = ents[i].addr ;
	    csize	asize = ents[i].asize ;
	    rs = tp->ins(addr,asize) ;
	} /* end for */
	cerr << "ents_ins: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_ins) */

static int ents_present(addrset_ent *ents,addrset *tp) noex {
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

static int ents_get(addrset_ent *ents,addrset *tp) noex {
	int		rs = SR_OK ;
	cerr << "ents_get: ent" << eol ;
	for (int i = 0 ; (rs >= 0) && (i < nents) ; i += 1) {
	    addrset_ent	e ;
	    cvoid	*addr = ents[i].addr ;
	    if ((rs = tp->get(addr,&e)) >= 0) {
		rs = ents_have(ents,&e) ;
	    }
	} /* end for */
	cerr << "ents_get: ret rs=" << rs << eol ;
	return rs ;
}
/* end subroutine (ents_get) */

static int ents_have(addrset_ent *ents,addrset_ent *ep) noex {
	int		rs = SR_OK ;
	bool		f = false ;
	for (int i = 0 ; (!f) && (i < nents) ; i += 1) {
	    if (ents[i].addr == ep->addr) {
		f = (ents[i].asize == ep->asize) ;
	    }
	} /* end for */
	if (!f) rs = SR_NOTFOUND ;
	return rs ;
}
/* end subroutine (ents_have) */

static int ents_rem(addrset_ent *ents,addrset *tp) noex {
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


