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
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>		/* |FILE| */
#include	<cstring>
#include	<new>			/* |nothrow(3c++)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<sfx.h>			/* |sfbasename(3uc)| */
#include	<rmx.h>			/* |rmeol(3uc)| */
#include	<libf.h>		/* |freadln(3f)| */
#include	<strw.h>		/* |strwcpy(3uc)| */
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif


/* imported namespaces */

using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern int	freadln(FILE *,char *,int) noex ;
}


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cnothrow	nt{} ;
    	cnullptr	np{} ;
    	FILE		*fp = stdin ;
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	int		llen = LINEBUFLEN ;
	if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) {
	    int		blen = LINEBUFLEN ;
	    if (char *bbuf ; (bbuf = new(nt) char[blen + 1]) != np) {
	        while ((rs = freadln(fp,lbuf,llen)) > 0) {
		    rs = rmeol(lbuf,rs) ;
		    cchar	*cp ;
		    lbuf[rs] = '\0' ;
		    if (int cl ; (cl = sfcontent(lbuf,rs,&cp)) > 0) {
		        cchar	*bp ;
	    	        if (int bl ; (bl = sfbasename(cp,cl,&bp)) >= 0) {
			    strwcpy(bbuf,bp,bl) ;
	                    printf("%-40s => %s\n",lbuf,bbuf) ;
		        }
		    }
		    if (rs < 0) break ;
	        } /* end while */
	        delete [] bbuf ;
	    } /* end if (m-a-f) */
	    delete [] lbuf ;
	} /* end if (m-a-f) */
	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


