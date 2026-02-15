/* testfilelinker_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |u_mkdirs(3u)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>		/* |u_mkdirs(3u)| */
#include	<filelinker.hh>
#include	<localmisc.h>
#include	<dprintf.h>		/* debugging */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

cbool		f_debug = true ;

int main(int argc,mainv argv,mainv) {
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 1) {
	    if (filelinker fo ; (rs = fo.start) >= 0) {
		if ((rs = fo.load(argv + 1)) >= 0) {
		    cchar *fn = "testinput.txt" ;
		    if (ustat sb ; (rs = u_stat(fn,&sb)) >= 0) {
		        rs = fo.link(&sb,fn) ;
			DPRINTF("fo.link() rs=%d\n",rs) ;
		    }
		} /* end if (load) */
		rs1 = fo.finish ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (filelinker) */
	} /* end block */
	DPRINTF("done rs=%d\n",rs) ;
	if ((rs < 0) && (ex == EXIT_SUCCESS)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


