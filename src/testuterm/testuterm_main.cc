/* testuterm_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the UTERM object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/******************************************************************************

  	Description:
	Testing of the UTERM object.

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>
#include	<csysbase.h>
#include	<ascii.h>
#include	<exitcodes.h>
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"config.h"
#include	"defs.h"
#include	"uterm.h"


/* local defines */

#ifndef	FD_STDIN
#define	FD_STDIN	0
#endif


/* external subroutines */


/* exported variables */


/* exported subroutines */

int main(argc,con mainv argv,con mainv envv)
	UTERM	ut ;
	int	rs = SR_OK ;
	int	fd ;
	int	to, opts ;
	int	len, c ;
	int	sl ;
	int	ex = EX_INFO ;
	cchar	*cp ;
	char	lbuf[LINEBUFLEN + 1] ;

#if	CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	fd = FD_STDIN ;
	rs = uterm_start(&ut,fd) ;

#if	CF_DEBUG
	debugprintf("main: uterm_start() rs=%d\n",rs) ;
#endif

	if (rs < 0)
		goto done ;

/* try to read something */

	to = 20 ;
	opts = 0 ;
	rs = uterm_reade(&ut,lbuf,LINEBUFLEN,to,opts,NULL,NULL) ;
	len = rs ;

#if	CF_DEBUG
	debugprintf("main: uterm_reade() rs=%d\n",rs) ;
#endif

	if (len > 0) {

	    c = lbuf[len - 1] ;
	    if ((c == CH_ESC) || (c == CH_CSI)) {

#if	CF_DEBUG
	debugprintf("main: escape sequence terminator=\\x%02X\n",c) ;
#endif

		opts = fm_noecho ;
	        rs = uterm_reade(&ut,lbuf,LINEBUFLEN,0,opts,NULL,NULL) ;

#if	CF_DEBUG
	{
	char	hexbuf[HEXBUFLEN + 1] ;
	debugprintf("main: uterm_reade() rs=%d\n",rs) ;
	sl = mkhexstr(hexbuf,HEXBUFLEN,lbuf,rs) ;
	debugprintf("main: buf= %w\n",hexbuf,sl) ;
	}
#endif

	    }
	}

/* get out */

	uterm_finish(&ut) ;

done:
	ex = (rs >= 0) ? EX_OK : EX_DATAERR ;

#if	(CF_DEBUG || CF_DEBUG)
	debugclose() ;
#endif

	return ex ;
}
/* end subroutine (main) */


