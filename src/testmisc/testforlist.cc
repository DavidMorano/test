/* mainforlist SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<cinttypes>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<forward_list>
#include	<vector>
#include	<string>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<localmisc.h>


/* local defines */

#define	VARDEBUGFNAME	"FORLIST_DEBUGFILE"


/* name-spaces */

using namespace std ;


/* external subroutines */

#if	CF_DEBUG
extern "C" int	debugopen(cchar *) ;
extern "C" int	debugprintf(cchar *,...) ;
extern "C" int	debugclose() ;
extern "C" int	strlinelen(cchar *,cchar *,int) ;
#endif


/* external variables */


/* local structures (and methods) */

local int printlist(forward_list<int> &,cchar *) ;
local int printvec(vector<int> &,cchar *) ;

typedef forward_list<int>	ourlist ;


/* forward references */

local int forlist_add(ourlist &,ourlist::iterator &,int) ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv envv) {
	int			rs = SR_OK ;
	cchar			*cp ;
#if	CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#else
	(void) envv ;
#endif /* CF_DEBUG */
	{
	    forward_list<int>	srclist = { 2, 4, 8, 1, 0 	} ;
	    forward_list<int>	lr ;
	    ourlist::iterator	it ;
	    printlist(srclist,"src") ;
	    it = lr.begin() ;
	    for (auto v : srclist) {
		rs = forlist_add(lr,it,v) ;
	    }
	    printlist(lr,"res") ;
	} /* end block */

#if	CF_DEBUG
	debugprintf("main: ret\n") ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif
	return 0 ;
} /* end subroutine (main) */


/* local subroutines */

/* extreme danger: only increment iterator after the insert call */
local int forlist_add(ourlist &ll,ourlist::iterator &it,int v) { 
	int		rs = SR_OK ;
	if (ll.empty()) {
	    ll.push_front(v) ;
	    it = ll.begin() ;
	} else {
	    ll.insert_after(it,v) ; /* danger: only increment iterator after */
	    it++ ;
	}
	return rs ;
} /* end subroutine (forlist_add) */

local int printlist(forward_list<int> &l,cchar *s) {
	int	c = 0 ;
	cout << s ;
	for (auto v : l) {
	    c += 1 ;
	    cout << " " << v ;
	}
	cout << endl ;
	return c ;
} /* end subroutine (printlist) */

local int printvec(vector<int> &l,cchar *s) {
	int	c = 0 ;
	for (cauto v : l) {
	    c += 1 ;
	    cout << " " << v ;
	}
	cout << endl ;
	return c ;
} /* end subroutine (printvec) */


