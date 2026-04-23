/* testsigned_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test signedness */
/* version %I% last-modified %G% */

#define	CF_INTEGRALTYPE		1

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int sub(int) ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	int		siw ;
	uint		uiw ;
	char		ch = char(0xff) ;
	signed char	sch = schar(0xff) ;
	uchar		uch = char(0xff) ;

#if	CF_INTEGRALTYPE
	siw = (sch & 0xff) ;
#endif

	{
	siw = ch ;
	uiw = ch ;
	printf("default  siw=%08x uiw=%08x\n",siw,uiw) ;
	}
	{
	siw = sch ;
	uiw = sch ;
	printf("signed   siw=%08x uiw=%08x\n",siw,uiw) ;
	}
	{
	siw = uch ;
	uiw = uch ;
	printf("unsigned siw=%08x uiw=%08x\n",siw,uiw) ;
	}
	/* coerced */
	{
	uch = sch ;
	siw = uch ;
	uiw = uch ;
	printf("coerced  siw=%08x uiw=%08x\n",siw,uiw) ;
	}
	/* switch test */
	switch ((int) uch) {
	case 0xFF:
		printf("switched on FF\n") ;
		break ;
	default:
		printf("switched on DEFAULT\n") ;
		break ;
	} /* end switch */
	/* subroutine test */
	sub(uch) ;
	/* combination */
	{
	siw = uch | 0 ;
	uiw = uch | 0 ;
	printf("combination	siw=%08x uiw=%08x\n",siw,uiw) ;
	}
	{
	    cint m = int(UCHAR_MAX) ;
	    cint n = -5 ;
	    cchar *fmt = 
		"%02X %02X %u\n" ;
	    for (int i = 0 ; i > n ; i -= 1) {
		if (i < 0) {
		    printf(fmt,((i+1)&m),(i&m),uint((i+1) > i)) ;
		}
	    } /* end for */
	}
}
/* end subroutine (main) */


/* local subroutines */

local int sub(int uiw) {
	printf("subroutine	uiw=%08x\n",uiw) ;
	return 0 ;
}
/* end subroutine (sub) */


