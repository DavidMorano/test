/* teststrncmp SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/time.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<cstring>		/* |strncmp(3c)| */
#include	<cthex.h>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

int main(int argc,mainv,mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	{
	    int		rc ;
	    cchar	*s2 = "goodbye-apple" ;
	    cchar	*sp = "goodbye-" ;
	    int		sl = lenstr(sp) ;
	    {
	        rc = strncmp(s2,sp,sl) ;
	        printf("strncmp: rc=%d\n",rc) ;
	    }
	    {
	        rc = strcmp(s2,sp) ;
	        printf("strcmp: rc=%d rc=\\x%02X\n",rc,rc) ;
	    }
	    {
	        rc = strncmp(s2,sp,20) ;
	        printf("strncmp: rc=%d\n",rc) ;
	    }
	} /* end block */
	if ((rs < 0) && (ex == EXIT_SUCCESS)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


