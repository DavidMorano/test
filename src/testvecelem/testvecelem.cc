/* testnvecelem SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test the VECINT Object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debuging switch */

/* revision history:

	= 2010-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2010 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:testvecelem

	Description:
	This code tests the use of the VECINT object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cinttypes>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstring>
#include	<new>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<getfdfile.h>		/* |FD_{x}| */
#include	<vecelem.h>		/* <- under test */
#include	<exitcodes.h>
#include	<localmisc.h>
#include	<debprintf.h>

#pragma		GCC dependency		"mod/debug.ccm"

import debug ;

/* local defines */


/* name-spaces */

using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures */

struct elem {
    	int		a ;
	int		b ;
} ;


/* forward references */


/* local variables */

constexpr elem		elems[] = {
    { 1	,2 },
    { 3	,4 },
    { 5	,6 },
    { 0	,0 }
} ; /* end array (elems) */

cbool		f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	constexpr int	dfd = (f_debug) ? FD_STDERR : -1 ;
    	constexpr int	esz = szof(elem) ;
	cint		vn = 0 ;
	cint		vo = 0 ;
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	debfd(dfd) ;
	DEBPRINTF("ent\n") ;
	if (vecelem vi ; (rs = vecelem_start(&vi,esz,vn,vo)) >= 0) {
	    cint ne = nelem(elems) ;
	    DEBPRINTF("-> addlist\n") ;
	    if ((rs = vecelem_addlist(&vi,elems,ne)) >= 0) {
	        DEBPRINTF("-> count\n") ;
		if ((rs = vecelem_count(&vi)) >= 0) {
	            elem *ep ;
		    DEBPRINTF("count=%d\n",rs) ;
	            for (int i = 0 ; vecelem_get(&vi,i,&ep) >= 0 ; i += 1) {
		        cout << " " << ep->a << " " << ep->b ;
	            }
	            cout << eol ;
		} /* end if (vecelem_count) */
	    } /* end if (vecelem_addlist) */
	        DEBPRINTF("cur rs=%d\n",rs) ;
	    rs1 = vecelem_finish(&vi) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (vecelem) */
	DEBPRINTF("exit rs=%d\n",rs) ;
	if (rs < 0) {
	    DEBPRINTF("error rs=",rs) ;
	    ex = EXIT_FAILURE ;
	}
	DEBPRINTF("ret ex=%d\n",ex) ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


