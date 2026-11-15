/* testcharconv SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	Convert a sequence of numbers to their digital character
	(in decimal) representation.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol| */
#include	<cfdec.h>		/* LIBUC */
#include	<cfchars.h>		/* LIBUC */
#include	<ctdec.h>		/* LIBUC */
#include	<ctchars.h>		/* LIBUC */


/* local defines */


/* name spaces */

using namespace std ;


/* forward references */


/* local variables */

constexpr cpcchar	nums[] = {
	"2",
	"11",
	"10",
	"16",
	"21675",
	"1836482",
	"1398795416",
	nullptr
} ; /* end array */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	cint		llen = LINEBUFLEN ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	cchar		*w ;
	char		lbuf[LINEBUFLEN+1] ;
	for (int i = 0 ; (rs >= 0) && ((w = nums[i])) ; i += 1) {
	    cout << "w=" << w << " " ;
	    if (int v ; (rs = cfdec(w,-1,&v)) >= 0) {
		if ((rs = ctdec(lbuf,llen,v)) >= 0) {
		    cout << lbuf << eol ;
		}
	    } /* end if (cfdec) */
	} /* end for */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


