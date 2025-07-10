/* fsdirtree_main SUPPORT (testfsdirtree) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* generic (pretty much) front end program subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-09-01, David A­D­ Morano
	This subroutine was borrowed and modified from previous
	generic front-end 'main' subroutines!

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*****************************************************************************

  	Name:
	fsdirtree_main

	Description:
	This subroutine forms the front-end part of a generic PCS
	type of program.  This front-end is used in a variety of
	PCS programs.  This subroutine was originally part of the
	Personal Communications Services (PCS) package but can also
	be used independently from it.  Historically, this was
	developed as part of an effort to maintain high function
	(and reliable) email communications in the face of increasingly
	draconian security restrictions imposed on the computers
	in the DEFINITY development organization.

*****************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<new>			/* |nothrow(3c++)| */
#include	<usystem.h>
#include	<fsdirtree.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */


/* imported namespaces */

using std::nullptr_t ;
using std::nothrow ;


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	int	rs = SR_OK ;
	int	rs1 ;
	int	ex = EX_INFO ;
	(void) rs1 ;

	if (rs < 0) ex = EX_DATAERR ;
	return ex ;
}
/* end subrouine (main) */


