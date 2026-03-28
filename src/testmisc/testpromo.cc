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

  	Name:
	testpromo

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

int main(int,mainv,mainv) {
    	uint	uv ;
	{
	    schar a = -3 ;
	    uv = a ;
	    printf("uv=%08X\n",uv) ;
	}
	{
	    short a = -3 ;
	    uv = a ;
	    printf("uv=%08X\n",uv) ;
	}
	{
	    int a = -3 ;
	    {
		ulong uv = a ;
	        printf("uv=%016lX\n",uv) ;
	    }
	}
	{
	    cbool f1 = bool(4) ;
	    cbool f2 = bool(-5) ;
	    printf("f1=%u\n",uint(f1)) ;
	    printf("f2=%u\n",uint(f2)) ;
	}
} /* end subroutine (main) */


