/* testnewobj SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>

#include	"newobj.h"

extern char	*strwcpy(char *,cchar *,int) ;

int main()
{
	cint	n = 26 ;
	int		rs = SR_OK ;
	cchar	*s = "hello world!" ;
	char		*a ;

	if ((a = newobj(char,(n+1))) != NULL) {
	    strwcpy(a,s,n) ;
	    printf("p=%p a=%s\n",a,a) ;
	    uc_free(a) ;
	} else
	    rs = SR_NOMEM ;

	printf("rs=%d\n",rs) ;

	return 0 ;
} /* end subroutine (main) */


