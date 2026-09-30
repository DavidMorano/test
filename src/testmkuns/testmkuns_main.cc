/* testmkuns_main SUPPORT */
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

/*******************************************************************************

	Description:
	I test the |mkuns| template.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<typetraits>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

import mkuns ;

/* local defines */


/* local namespaces */

using std::cout ;			/* variable */
using std::is_same_v ;			/* ?? */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct SInt128 { /* ... */ } ;
struct UInt128 { /* ... */ } ;

    template <> struct mkuns<SInt128> {
        using type = UInt128 ;
    } ; /* end struct (mkuns) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    assert_static(is_same_v<mkuns_t<int>,uint>) ;
    assert_static(is_same_v<mkuns_t<SInt128>,UInt128>) ;
    cout << "ret ok\n" ;
} /* end subrutine (main) */


