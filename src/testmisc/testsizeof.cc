/* testsizeof SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test getting the size of various types (using |sizeof()|) */
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
#include	<cstdarg>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct somer {
	template<typename ... Ts>void print(Ts ... ts) noex {
	    cint na = sizeof ... (Ts) ;
	    printf("na=%d\n",na) ;
	} ; /* end method */
    } ; /* end struct (some) */
} /* end namespace */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;
	if (rs >= 0) {
	    csize sz = sizeof(nlink_t) ;
	    printf("nlink_t=%lu\n",sz) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    csize sz = sizeof(pthread_t) ;
	    printf("pthread_t=%lu\n",sz) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    somer	some ;
	    some.print(1,2) ;
	} /* end if */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


