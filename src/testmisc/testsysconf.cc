/* testsysconf SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test if |printf(3c)| can print out ISO-Latin1 characters */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
  	Test the |sysconf(3c)| standard C-library call.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

int main(int,mainv,mainv) {
    	long v = sysconf(_SC_CLK_TCK) ;
	printf("hz=%ld\n",v) ;
} /* end subroutine (main) */


