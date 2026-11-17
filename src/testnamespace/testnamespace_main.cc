/* testnamespace_nain SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test C++ namespace lookup */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	Test some aspects of the C++ namespace lookup rules.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */


/* local namespaces */

using std::cout ;


/* local typedefs */


/* external subroutines */

namespace nsext {
    extern void extone() noex ;
    extern void exttwo() noex ;
}


/* external variables */


/* local structures */


/* forward references */

local void subone() {
    cout << "outer::subone" << eol ;
}

namespace nsone {
    local void subone() noex ;
    local void subtwo() noex ;
    local inline void subthree() noex {
	subone() ;
    }
} /* end namespace (nsone) */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	if (rs >= 0) {
	    subone() ;
	}
	if (rs >= 0) {
	    using nsone::subone ;
	    subone() ;
	} /* end if (ok) */
	if (rs >= 0) {
	    using nsone::subtwo ;
	    subtwo() ;
	} /* end if (ok) */
	if (rs >= 0) {
	    using nsone::subthree ;
	    subthree() ;
	} /* end if (ok) */
	if (rs >= 0) {
	    using nsext::extone ;
	    extone() ;
	} /* end if (ok) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

namespace nsone {
    local void subone() noex {
	cout << "inner::subone\n" ;
    } 
    local void subtwo() noex {
	subone() ;
    } 
} /* end namespace (nsone) */


