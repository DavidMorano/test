/* testoptional SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the variaous system case-insensitive comparisons against my own */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-06-21, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

 	Description:
	Test the C++17 |optional(3c++)| object.

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<optional>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usys.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

using std::optional ;			/* type */
using std::make_optional ;		/* subroutine */
using std::cout ;			/* variable */
using std::nullopt ;			/* constant */


struct thing {
    	ccharp	keyp ;
	ccharp	valp ;
} ; /* end struct */

constexpr thing		ents[] = {
	{ "one",	"oner"	},
	{ "two",	"twoer"	},
} ; /* end array */

typedef optional<thing>	opting ;

local con thing *sthing(ccharp k) noex {
    	con thing	*resp = nullptr ;
    	for (cauto &e : ents) {
	    if (cmpstr(e.keyp,k) == 0) {
		resp = &e ;
		break ;
	    }
	} /* end for */
	return resp ;
} /* end subroutine (sthing) */

local void testoptional() noex ;

int main(int,con mainv,con mainv) {
	if (con thing *resp = sthing("two")) {
	    printf("found k=%s v=%s\n",resp->keyp,resp->valp) ;
	} /* end if */
	testoptional() ;
} /* end subroutine (main) */


/* local subroutine */

local opting searcher(ccharp k) noex {
    	opting		res ;
	bool		f = false ;
    	for (cauto &e : ents) {
	    if ((f = (cmpstr(e.keyp,k) == 0))) {
		res = make_optional<thing>(e) ;
		break ;
	    }
	} /* end for */
	return (f) ? res : nullopt ;
} /* end subroutine (searcher) */

local void testoptional() noex {
    if (opting res = searcher("two")) {
	ccharp kp = res->keyp ;
	ccharp vp = res->valp ;
	printf("found k=%s v=%s\n",kp,vp) ;
    } /* end if */
} /* end subroutine */


