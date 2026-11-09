/* testbasename_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test |sfbasename(3uc)| */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testbasebane

	Description:
	This tests the |strbasename(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD |FILE| */
#include	<cstring>		/* CSTD */
#include	<new>			/* C++STD placement-new */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */
#include	<libf.h>		/* LIBF */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import ureserve ;			/* |sf{x}(3u)| */

/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif


/* imported namespaces */

using libu::strwcpy ;			/* subroutine */
using libu::rmeol ;			/* subroutine */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cint		maxlinelen = LINEBUFLEN ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cnothrow	nt{} ;
    	FILE		*fp = stdin ;
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	int		llen = maxlinelen ;
	if (char *lbuf = new(nt) char[llen + 1]) {
	    int		blen = maxlinelen ;
	    if (char *bbuf = new(nt) char[blen + 1]) {
	        while ((rs = freadln(fp,lbuf,llen)) > 0) {
		    if (cint ll = rmeol(lbuf,rs) ; ll > 0) {
		        cchar	*cp ;
			lbuf[ll] = eos ;
		        if (int cl ; (cl = sfcontent(lbuf,rs,&cp)) > 0) {
		            cchar	*bp ;
	    	            if (int bl ; (bl = sfbasename(cp,cl,&bp)) >= 0) {
			        strwcpy(bbuf,bp,bl) ;
	                        printf("%-40s => %s\n",lbuf,bbuf) ;
		            }
		        } /* end if (sfcontent) */
		    } /* end if (rmeol) */
		    if (rs < 0) break ;
	        } /* end while */
	        delete [] bbuf ;
	    } /* end if (m-a-f) */
	    delete [] lbuf ;
	} /* end if (m-a-f) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = EX_DATAERR ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


