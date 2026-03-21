/* testreade_main SUPPORT (testreade) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test |uc_reade(3uc)| */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Name:
	testreade

	Description:
	Test the |uc_reade(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>		/* |fprintf(3c)| + |stdout| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<ureade.h>
#include	<getfdfile.h>		/* |FD_STDIN| */
#include	<stdfnames.h>
#include	<funcodes.h>
#include	<rmx.h>			/* |rmeol(3uc)| */
#include	<localmisc.h>		/* |COLUMNS| */
#include	<libf.h>		/* LIBF */
#include	<libdebug.h>		/* LIBDEBUG */
#include	<dprintf.hh>		/* debugging */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif

#define	READ_CNT	10

#define	TO_READ		5


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

static FILE	*ofp = stdout ;

cbool		f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	cint		fd_in = FD_STDIN ;
    	cint		llen = LINEBUFLEN ;
	cint		to = TO_READ ;
	cint		opts = FM_TIMED ;
	cint		mcnt = READ_CNT ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	char		lbuf[LINEBUFLEN + 1] = {} ;
	DPRINTF("ent\n") ;
	for (int cnt = 0 ; (rs >= 0) && (cnt < mcnt) ; cnt += 1) {
	    lbuf[0] = '\0' ;
	    rs = u_reade(fd_in,lbuf,llen,to,opts) ;
	    cint len = rs ;
	    DPRINTF("reade() rs=%d\n",rs) ;
	    if (rs > COLUMNS) break ;
	    if (rs < 0) break ;
	    if (len == 0) break ;
	    {
	        if (cint pl = rmeol(lbuf,len) ; pl >= 0) {
		    lbuf[pl] = '\0' ;
		}
	        rs = fprintf(ofp,"data=>%s<\n",lbuf) ;
	    } /* end block */
	    if (rs < 0) break ;
	} /* end for */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


