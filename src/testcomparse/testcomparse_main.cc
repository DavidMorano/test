/* testcomparse_main SUPPORT  */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the COMPARSE object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"comparse.h"


#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

#define	VARDEBUGFNAME	"TESTCOMPARSE_DEBUGFILE"


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	comparse	coms ;
	cint		hlen = MAXPATHLEN ;
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	cchar		*sp = "this is ( a comment )" ;
	char		hbuf[MAXPATHLEN+1] ;

#if	CF_DEBUG
	{
	    if (cc *cp ; (cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	        debugopen(cp) ;
	        debugprintf("main: starting\n") ;
	    }
	}
#endif /* CF_DEBUG */

	if ((rs = comparse_start(&coms,sp,-1)) >= 0) {
	    cchar	*vp, *cp ;
	    int		vl, cl ;

	    rs = comparse_getval(&coms,&vp) ;
	    vl = rs ;
	    printf("getval() rs=%d\n",rs) ;
	    printf("getval() v=>%s<\n",vp) ;

	    if (rs >= 0) {
	    rs = comparse_getcom(&coms,&cp) ;
	    cl = rs ;
	    printf("getcom() rs=%d\n",rs) ;
	    printf("getcom() c=>%s<\n",cp) ;
	    } /* end if (ok) */

	    rs1 = comparse_finish(&coms) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (comparse) */

#if	CF_DEBUG
	debugclose() ;
#endif

	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */

