/* testconversion SUPPOER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/
/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol| */

using std::cout ;			/* variable */

local void procsize(int v) {
    cout << "v=" << v << eol ;
} /* end subroutine */

int main(int,con mainv,con mainv) {
    const size_t large_size = 5000 ;
    procsize(large_size) ;
} /* end subroutine (main) */


