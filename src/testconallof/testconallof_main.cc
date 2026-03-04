/* testconallof_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |conallof(3uc)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG */

#include	"conallof.h"


int main(int,mainv,mainv) {
	int		rs ;
	cchar		*ans[3] = { "NO", "YES" } ;
	cchar		*sp = "this is ( a comment )" ;

	if ((rs = conallof(sp,-1,"hn")) >= 0) {
	    if (rs < 2) {
	    printf("%s\n",ans[rs]) ;
	    }
	}

	if ((rs = conallof(sp,-1,"hwn")) >= 0) {
	    if (rs < 2) {
	    printf("%s\n",ans[rs]) ;
	    }
	}

}
/* end subroutine (main) */


