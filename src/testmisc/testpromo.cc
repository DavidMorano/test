/* testpromo SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test integer promotion */
/* version %I% last-modified %G% */

#define	CF_EXTERN	0		/* try an external subroutine */
#define	CF_DOWNSIZE	0		/* test type-down-sizing */

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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<bit>			/* C++STD |popcount(3c++)| */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#ifndef	CF_DOWNSIZE
#define	CF_DOWNSIZE	0		/* test type-down-sizing */
#endif

#if	CF_EXTERN
extern void exsub(int) noex ;
#endif /* CF_EXTERN */

local void promosub(int v) noex {
	printf("v=%d\n",v) ;
} /* end subroutine */

cbool		f_downsize		= CF_DOWNSIZE ;

int main(int,con mainv,con mainv) {
    	uint	uv ;
	{
	    schar a = -3 ;
	    uv = a ;
	    printf("uv=%08X\n",uv) ;
	} /* end */
	{
	    short a = -3 ;
	    uv = a ;
	    printf("uv=%08X\n",uv) ;
	} /* end */
	{
	    int a = -3 ;
	    {
		ulong uv = a ;
	        printf("uv=%016lX\n",uv) ;
	    }
	} /* end */
	{
	    cbool f1 = bool(4) ;
	    cbool f2 = bool(-5) ;
	    printf("f1=%u\n",uint(f1)) ;
	    printf("f2=%u\n",uint(f2)) ;
	}
	if_constexpr (f_downsize) {
	    size_t dsize = 42 ;
	    promosub(dsize) ;		/* <- should give compiler warning! */
	} /* end block */
#if	CF_EXTERN
	{
	    size_t dsize = 42 ;
	    exsub(dsize) ;		/* <- should give compiler warning! */
	} /* end */
#endif /* CF_EXTERN */
} /* end subroutine (main) */


