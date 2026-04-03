/* testlimits SUPPORT (testlimits) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |hostequiv(3dam)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2026-03-30, David A-D- Morano
	I just saw that there are tests for the GNU GLIB version
	of their various |strto{x}(3c)| subroutines.  I thought
	that it was high time (after all of these years) to see
	if my own versions of these subroutines (specifically
	my look-alikes for |strtol(3c)| and |strtoul(3c)|) can
	pass those tests.

*/

/* Copyright © 2026 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testlimits

	Description:

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdint>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usysflag.h>		/* |usysflag(3u)| */
#include	<stdintx.h>
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		c = 0 ;
	{
	    int	b = 10 ;
	    int	mi = INT_MIN ;
	    printf("mini=%d\n",mi) ;
	    printf("mini÷b=%d\n",(mi % b)) ;
	    uint inter = uint(- (INT_MIN + INT_MAX)) ;
	    uint what = (inter + INT_MAX) ;
	    printf("inter=%d what=%u\n",inter,what) ;
	    {
		cint b = 10 ;
		int cutoff ;
		int cutlim ;
		int imax = INT_MAX ;
		int imin = INT_MIN ;
	    printf("imax=%d imin=%d\n",imax,imin) ;
	        cutoff = imin / b ;
		cutlim = int(imin % b) ;
	    printf("cutoff=%d cutlim=%d\n",cutoff,cutlim) ;
	        if (cutlim > 0) {
		    cutlim -= b ;
		    cutoff += 1 ;
	            printf("adjusted-cutoff=%d\n",cutoff) ;
	            printf("adjusted-cutlim=%d\n",cutlim) ;
		}
		cutlim = (- cutlim) ;
	        printf("negated-cutlim=%d\n",cutlim) ;
	    }
	}
	printf("ret tests rs=%d c=%d\n",rs,c) ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


