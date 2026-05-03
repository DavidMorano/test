/* testconstinit SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* just a little test (of constant initialization) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	testconstinit

	Description:

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

#include	"systypenames.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */

ccharp		systypename[systypename_overlast + 1] ;


namespace {
    struct systyper {
	constexpr systyper() noex {
       	systypename[systypename_darwin]		= "Darwin" ;
	systypename[systypename_linux]		= "Linux" ;
	systypename[systypename_sysv]		= "SysV" ;
	systypename[systypename_overlast]	= nullptr ;
	} ;
    } ; /* end struct (systyper) */
} /* end namespace */


/* forward references */


/* local variables */

const systyper	systype_data ;


/* exported variables */


/* local subroutines */


