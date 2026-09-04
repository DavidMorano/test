/* testgethost SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* get the |uc_gethostbyname(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<uclibmem.h>
#include	<ucgetx.h>
#include	<hostent.h>
#include	<localmisc.h>
#include	<dprint.hh>


/* local defines */


/* imported namespaces */

using libuc::libmem ;			/* variable */


/* local typedefs */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 0) {
	    if (char *hebuf ; (rs = lm_ho(&hebuf)) >= 0) {
	        HOSTENT	he ;
	        cint	helen = rs ;
	        for (int ai = 1 ; ai < argc ; ai += 1) {
	            cchar	*name = argv[ai] ;
	            if (name[0]) {
	                rs = uc_gethostbyname(&he,hebuf,helen,name) ;
		        printf("get n=%s rs=%d \n",name,rs) ;
	            }
	        } /* end for */
		rs1 = lm_free(hebuf) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (memory-allocation) */
	} /* end if (positive) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


