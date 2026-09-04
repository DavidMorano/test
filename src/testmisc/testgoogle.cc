/* testgoogle SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


consteval int addone(int v) {
    	return v + 1 ;
} /* end */

consteval int testone() {
    	constexpr int a[] = { 1, 2, 3 } ;
	int sum = 0 ;
	for (int i = 0 ; i < 3 ; i += 1) {
	    sum += addone(a[i]) ;
	}
	return sum ;
} /* end */

int main() {
	    constexpr int val = testone() ;
	    printf("sum=%d\n",val) ;
} /* end */


