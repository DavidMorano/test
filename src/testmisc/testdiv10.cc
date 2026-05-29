/* tesdiv10 SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test constant division by 10 */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This is test code for seeing how the compiler handles a
	constant division.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>		/* CSTD */
#include	<cstddef>		/* CSTD |nullptr_t| */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfdec(3u)| */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

#ifdef	COMMENT
constexpr uint	nums[] = { 
    2U, 11U, 10U, 16U, 21675U, 1836482U, 1398795416U
} ;
#endif /* COMMENT */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv) {
	int	ex = EXIT_SUCCESS ;
	int	rs = SR_OK ;
	if (argc > 1) {
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *ap = argv[ai] ; ap[0]) {
	    	    errno = 0 ;
		    if (cuint num = atoui(ap) ; num > 0) {
	                con uint	q = (num / 10) ;
	                printf("num=%10u q=%10u\n",num,q) ;
		    } /* end if (atoui) */
		    if (errno) rs = (neg errno) ;
		} /* end if (non-empry) */
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    fprintf(stderr,"error rs=%d\n",rs) ;
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


