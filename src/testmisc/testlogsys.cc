/* testlogsys SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/syslog.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"logsys.h"


int main() {
	LOGSYS		logger, *lp = &logger ;
	cint	fac = LOG_USER ;
	cint	pri = LOG_INFO ;
	int		rs = 0 ;
	int		rs1 ;
	int		opts = 0 ;
	cchar	*logtab = "testlogsys" ;

	if ((rs = logsys_open(lp,fac,logtab,NULL,opts)) >= 0) {
	    cchar	*cp = "hello from the underworld!" ;

	    rs = logsys_printf(lp,pri,cp) ;

	    rs1 = logsys_close(lp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (logsys) */

	return 0 ;
} /* end subroutine (main) */


