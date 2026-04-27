/* testgetrandom SUPPORT */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test the |getrandom(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/random.h>
#include	<cstddef>
#include	<cstdlib>
#include	<cstdarg>
#include	<cstdio>
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usupport.h>		/* |cfdec(3u)| */
#include	<getx.h>		/* |getourenv(3uc)| */
#include	<mkchar.h>
#include	<exitcodes.h>
#include	<localmisc.h>		/* |COLUMNS| */
#include	<dprint.hh>		/* |DPRINTF(3u)| */


/* local defines */

#define	RBUFLEN		20

#define	VARCOLUMNS	"COLUMNS"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif


/* imported namespaces */

using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using libu::cfdec ;			/* subroutine */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cbool		f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		cols = COLUMNS ;
	DPRINTF("ent\n") ;
#if	(COMMENT == 0)
	DPRINTF("not-comment\n") ;
#endif
	if (cchar *cp ; (cp = getourenv(envv,VARCOLUMNS)) != np) {
	     if (int v ; (rs = cfdec(cp,-1,&v)) >= 0) {
	         cols = v ;
	     }
	}
	if (rs >= 0) {
	    cint	rlen = RBUFLEN ;
	    char	rbuf[RBUFLEN+1] ;
	    DPRINTF("random> \n") ;
	    if (int rc ; (rc = getrandom(rbuf,rlen,0)) > 0) {
		cint	rl = min(rc,(cols/3)) ;
		for (int i = 0 ; i < rl ; i += 1) {
		    cint ch = MKCHAR(rbuf[i]) ;
	    	    DPRINTR(" %02x",ch) ;
		} /* end for */
		DPRINTR("\n") ;
	    } /* end if */
	} /* end if (arguments) */
	if (rs < 0) DPRINTF("failure (%d)\n",rs) ;
}
/* end subroutine (main) */


/* local subroutines */


