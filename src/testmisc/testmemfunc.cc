/* testmemfunc SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

namespace {
    struct member ;
    typedef void (member::*member_m)() ;
    struct member {
	member_m	m ;
	void printer() {
	    printf("printer\n") ;
	} ;
	void co() {
	    (this->*m)() ;
	} ;
	member() {
	    m = &member::printer ;
	} ;
    } ; /* end struct (member) */
} /* end */

int main() {
	member	mem ;
	mem.co() ;
} /* end subroutine (main) */


