/* testvirtual SUPPORT (Test-Virtualization) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test object virtualization */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* |getpid(2)| */
#include	<libproc.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<syncstream>		/* |osyncstream(3c++)| */
#include	<thread>
#include	<mutex>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>


#ifndef	eol
#define	eol	'\n'
#endif

using std::cout ;			/* variable */
using std::cerr ;			/* variable */

struct base {
	void setname(cchar *n) noex {
	    name = n ;
	} ;
	base() noex {
	    cout << "base-" << name << "-construct\n" ;
	} ;
    	base(cchar *n) noex : name(n) {
	    cout << "base-" << name << "-construct\n" ;
	} ;
	virtual int hello() noex {
	    cout << "base-" << name << "-hello\n" ;
	    return 0 ;
	} ;
	virtual destruct base() {
	    cout << "base-" << name << "-destruct\n" ;
	} ;
    private:
    	cchar	*name = "unknown" ;
} ;

struct derived : base {
    	derived(cchar *n) noex : base(n), name(n) {
	    cout << "derived-" << name << "-construct\n" ;
	} ;
	int hello() noex override {
	    cout << "derived-" << name << "-hello\n" ;
	    return 1 ;
	} ;
	destruct derived() {
	    cout << "derived-" << name << "-destruct\n" ;
	} ;
    private:
    	cchar	*name = "unset" ;
} ;

int main(int argc,mainv,mainv) {
    	int		ex = 0 ;
	int		rs = 0 ;
	derived		dev("a") ;
	derived		other("b") ;
	cerr << "main-ent\n" ;
	rs = dev.hello() ;
	cout << "dev-rs=" << rs << eol ;
	if (argc > 1) {
	    base *bp = &other ;
	    rs = bp->hello() ;
	    cout << "dev-rs=" << rs << eol ;
	}
	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


