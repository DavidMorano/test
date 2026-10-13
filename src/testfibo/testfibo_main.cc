/* testfibo_main support (testfibo) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* the some subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-09-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This program calculates and prints out the first few Finonacci
	numbers.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */

#define	NN	20


/* external subroutines */

extern longlong_t	fibonacci(unsigned int) noex ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	for (int i = 0 ; i < NN ; i += 1) {
	    culonglong	res = fibonacci(i) ;
	    ulong pv = ulongconv(res) ;
	    printf(" %lu",pv) ;
	} /* end for */
}
/* end subroutine (main) */


