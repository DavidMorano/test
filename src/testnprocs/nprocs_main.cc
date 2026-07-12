/* nprocs_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test getting the number of processes currently on the system */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>		/* POSIX */
#include	<sys/stat.h>		/* POSIX */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usys.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* imported namespaces */

using libu::matstr ;			/* subroutine */


/* local typedefs */


/* local variables */

constexpr cpcchar	names[] = {
    	"all",
	"system",
	"user",
	"session",
	nullptr
} ; /* end arrat */


/* exported variables */


/* exported subroutines */

local int lister(int w) noex {
    	int	rs ;
	if ((rs = usys::usys_nprocs(w)) >= 0) {
	    printf("nprocs=%d\n",rs) ;
	}
	return rs ;
} /* end subroutine (lister) */

int main(int argc,con mainv argv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	int		w = 0 ;
	if (argc > 1) {
	    for (int ai = 1 ; ai < argc ; ai += 1) {
	        if (cchar *ap = argv[ai] ; ap[0]) {
	    	    if (cint mi = matstr(names,ap) ; mi >= 0) {
			rs = lister(mi) ;
		    } /* end if (matstr) */
		} /* end if (non-empty) */
	    } /* end for */
	} else {
	    rs = lister(w) ;
	} /* end if */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    printf("error rs=%d\n",rs) ;
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


