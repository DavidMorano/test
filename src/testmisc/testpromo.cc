/* testpromo SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test integer promotion */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
  	Test the integer promotion.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<bit>			/* |popcount(3c++)| */
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

using std::popcount ;

local int sub(uint uv) noex {
    	return popcount(uv) ;
}

constexpr int	vals[] = {
    	1, 3, 4, 9, -3
} ;

int main(int,mainv,mainv) {
    	for (cauto &v : vals) {
    	    cint n = sub(v) ;
	    printf("v=%d\tn=%d\n",v,n) ;
	} /* end for */
} /* end subroutine (main) */


