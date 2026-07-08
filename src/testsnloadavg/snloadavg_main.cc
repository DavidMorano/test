/* snloadavg_main SUPPORT (testsnloadavg) */
/* charset=ISO8859-1 */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */

/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services (RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This little program tests the |snloadavg(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ascii.h>		/* LIBU */
#include	<snx.h>			/* LIBUC */
#include	<cfdecf.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |DEVBUFLEN| */


/* local defines */

#define	DBUFLEN		DECBUFLEN 
#define	NLOOPS		(16*1024*1024)


/* external subroutines */


/* forward references */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	uint	la = 0 ;
	cint	dlen = DBUFLEN ;
	cint	fill = -1 ;
	int	w = -1 ;
	int	p = 3 ;
	char	dbuf[DBUFLEN+1] ;

	la |= (3<<8) ;
	la |= 4 ;
	for (w = -1 ; w < 6 ; w += 1) {
	    for (p = -1 ; p < 4 ; p += 1) {
	        fprintf(stdout,"w=%d p=%d\n",w,p) ;
	        rs = snloadavg(dbuf,dlen,la,w,p,fill) ;
	        fprintf(stdout,"rs=%d s=>%s<\n",rs,dbuf) ;
	    } /* end for */
	} /* end for */

	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */



