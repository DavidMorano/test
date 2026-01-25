/* testcharconv SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>
#include	<cfdec.h>
#include	<cfchars.h>
#include	<ctdec.h>
#include	<ctchars.h>


/* local defines */


/* name spaces */

using namespace std ;


/* forward references */


/* local variables */

constexpr cpcchar	nums[] = {
	"2",
	"11",
	"10",
	"16",
	"21675",
	"1836482",
	"1398795416",
	nullptr
} ; /* end array */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	FILE		*ofp = stdout ;
	cint		linelen = LINEBUFLEN ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		rs1 [[maybe_unused]] ;
	cchar		*w ;
	char		linebuf[LINEBUFLEN+1] ;
	for (int i = 0 ; (rs >= 0) && ((w = nums[i])) ; i += 1) {
	    fprintf(ofp,"w=%s\n",w) ;
	    if (int v ; (rs = cfdeci(w,-1,&v)) >= 0) {
		if ((rs = ctdeci(linebuf,linelen,v)) >= 0) {
		    cout << linebuf ;
		}
	    } /* end if (cfdec) */
	} /* end for */
	if (rs < 0) ex = EXIT_FAILURE ;
	return ex ;
}
/* end subroutine (main) */


