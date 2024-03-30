/* testmapblock SUPPORT */
/* lang=C++20 */

/* test the object |mapblock(3uc)| */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-03-28, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |EXIT_SUCCESS| */
#include	<string>
#include	<unordered_map>
#include	<iostream>
#include	<localmisc.h>

#include	"singlist.hh"
#include	"mapblock.hh"


using namespace std ;

static constexpr pair<int,string> tdata[] = {
	{ 1, "one" },
	{ 2, "two" },
	{ 3, "three" }
} ;

/* forward references */

static int	main_list() noex ;
static int	main_umap() noex ;
static int	main_mapblock() noex ;

/* exported subroutines */

int main(int,mainv,mainv) {
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (rs >= 0) {
	    rs = main_list() ;
	}
	if (rs >= 0) {
	    rs = main_umap() ;
	}
	if (rs >= 0) {
	    rs = main_mapblock() ;
	}
	if (rs < 0) ex = EXIT_FAILURE ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

int main_list() noex {
	singlist<string>	lval ;
	int		rs = SR_OK ;
	cerr << "singlist: ent" << eol ;
	    lval += "one" ;
	    lval += "two" ;
	    lval += "three" ;
	    for (const auto &e : lval) {
	       cerr << e << eol ;
	    }
	cerr << "singlist: ret=" << rs << eol ;
	return rs ;
}
/* end subroutine (main_list) */

int main_umap() noex {
	typedef unordered_map<int,string>::iterator	umapit_t ;
	unordered_map<int,string>	uv ;
	int		rs = SR_OK ;
	cerr << "umap: ent" << eol ;
	    for (const auto &e : tdata) {
		cint		k = e.first ;
		const string	&v = e.second ;
		cerr << "ins k=" << k << " v=" << v << eol ;
		if (k <= 0) break ;
		{
		    pair<umapit_t,bool>		r ;
		    r = uv.insert({k,v}) ;
		    if (!r.second) rs = SR_NOMEM ;
		}
		if (rs < 0) break ;
		cerr << "loop" << eol ;
	    } /* end for */
	if (rs >= 0) {
	   cerr << "umap: enumerate" << eol ;
	    for (const auto &e : uv) {
		cint		k = e.first ;
		const string	&v = e.second ;
		cerr << "enum k=" << k << " v=" << v << eol ;
	    }
	} /* end if (enumerate) */
	cerr << "umap: ret=" << rs << eol ;
	return rs ;
}
/* end subroutine (main_umap) */

int main_mapblock() noex {
	mapblock<int,string>	mv ;
	int		rs ;
	int		rs1 ;
	cerr << "mapblock: ent" << eol ;
	if ((rs = mv.start) >= 0) {
	    for (const auto &e : tdata) {
		cint		k = e.first ;
		const string	&s = e.second ;
		cerr << "ins k=" << k << " v=" << s << eol ;
		if (k <= 0) break ;
		rs = mv.ins(k,s) ;
		if (rs < 0) break ;
		cerr << "loop" << eol ;
	    } /* end for */
	    if (rs >= 0) {
	        cerr << "mapblock: enumerate" << eol ;
	        for (const auto &e : mv) {
		    cint		k = e.first ;
		    const string	&s = e.second ;
		    cerr << "enum k=" << k << " v=" << s << eol ;
		} /* end for (enumerate) */
	    } /* end if (enumerate) */
	    rs1 = mv.finish ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (mapblock) */
	cerr << "mapblock: ret=" << rs << eol ;
	return rs ;
}
/* end subroutine (main_mapblock) */


