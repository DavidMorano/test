/* testobjaddr SUPPORT */
/* lang=C++98 */

/* show object addresses */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This program shows (prints out) object addresess.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<string>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<set>
#include	<string>
#include	<iostream>
#include	<usystem.h>
#include	<localmisc.h>


/* local defines */


/* imported namespaces */

using namespace		std ;		/* yes, we want punishment! */


/* external subroutines */


/* local structures */

struct Base {
	string	id ;
	Base(cchar *s) : id(s) {
	    cout << "Base___::ctor " << id << eol ;
	} ;
	virtual ~Base() {
	    cout << "Base___::dtor " << id << eol  ;
	} ;
	virtual void print() {
	    cout << "Base___::print " << id << eol ;
	} ;
} ;

struct Inter {
	string	id ;
	Inter(cchar *s) : id(s) {
	    cout << "Inter__::ctor " << id << eol ;
	} ;
	virtual ~Inter() {
	    cout << "Inter__::dtor " << id << eol  ;
	} ;
	virtual void print() {
	    cout << "Inter__::print " << id << eol ;
	} ;
} ;

struct Derived : Inter, Base {
	string	id ;
	Derived(cchar *s) : Base(s), Inter(s), id(s) {
	    cout << "Derived::ctor " << id << eol ;
	} ;
	~Derived() {
	    cout << "Derived::dtor " << id << eol ;
	} ;
	void print() {
	    cout << "Derived::print " << id << eol ;
	} ;
} ;


/* forward references */

static void sub1() ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	Base	*bp = new Derived("a") ;
	cout << bp << eol ;
	{
	    void	*vp ;
	    Derived *dp = static_cast<Derived *>(bp) ;
	    vp = bp ;
	    cout << bp << " " << vp << eol ;
	    vp = dp ;
	    cout << dp << " " << vp << eol ;
	    bp->print() ;
	    dp->print() ;
	}
	sub1() ;
	Derived *dp = static_cast<Derived *>(bp) ;
	delete dp ;
}
/* end subroutine (main) */

static void sub1() {
	Derived	*dp = new Derived("b") ;
	cout << "sub1 " << dp << eol ;
	{
	    Base	*bp = dp ;
	    void	*vp ;
	    vp = bp ;
	    cout << "sub1 " << bp << " " << vp << eol ;
	    vp = dp ;
	    cout << "sub1 " << dp << " " << vp << eol ;
	    bp->print() ;
	    dp->print() ;
	}
	delete dp ;
}


