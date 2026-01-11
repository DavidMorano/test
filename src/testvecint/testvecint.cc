/* testnvecint SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* test the VECINT Object */
/* version %I% last-modified %G% */


/* revision history:

	= 2010-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2010 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:testvecint

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
#include	<vecint.h>		/* <- under test */
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

static const int	vals[] = { 3, 7, 19, 12, 43 } ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	cint		vn = 0 ;
	cint		vo = 0 ;
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	if (vecint vi ; (rs = vecint_start(&vi,vn,vo)) >= 0) {
	    cint	n = nelem(vals) ;
	    if ((rs = vecint_addlist(&vi,vals,n)) >= 0) {
		if ((rs = vecint_assign(&vi,8,71)) >= 0) {
	            int		v ;
	            for (int i = 0 ; vecint_getval(&vi,i,&v) >= 0 ; i += 1) {
		        cout << " " << v ;
	            }
	            cout << eol ;
	        } /* end if (vecint_assign) */
	    } /* end if (vecint_addlist) */
	    rs1 = vecint_finish(&vi) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (vecint) */
	if (rs < 0) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


