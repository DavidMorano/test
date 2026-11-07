/* testmemo SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* tes the |memo(3u)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<strnul.hh>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<mkpathx.h>		/* LIBUC */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"memo.hh"

using std::cout ;			/* variable */

int main(int,con mainv,con mainv) {
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	char *pbuf ;
	if (memo mbuf ; (rs = mbuf.mp(&pbuf)) >= 0) {
	    {
		rs = mkpath(pbuf,"hello","there") ;
		printf("mkpath rs=%d pbuf=%s\n",rs,pbuf) ;
	    }
	    rs1 = mbuf.free(pbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (memo) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


