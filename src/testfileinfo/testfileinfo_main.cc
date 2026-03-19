/* testfileinfo_main USPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test getting file information */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testfileinfo

	Description:
	Tes getitng file information.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int	putinfo(int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (rs >= 0) {
	    rs = putinfo(0) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (rs >= 0) {
	    rs = putinfo(1) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (rs >= 0) {
	    rs = putinfo(2) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int putinfo(int fd) noex {
	int		rs ;
	if (ustat sb ; (rs = fstat(fd,&sb)) >= 0) {
	    printf("FD=%d\n",fd) ;
	    printf(" inode=%d\n",sb.st_ino) ;
	    printf(" dev=%08x\n",sb.st_dev) ;
	    printf(" rdev=%08x\n",sb.st_rdev) ;
	} /* end if (stat) */
	return rs ;
} /* end subroutine (printinfo) */


