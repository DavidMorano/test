/* testcotd SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<fcntl.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>
#include	"testcotd.h"

#ifndef	FD_STDOUT
#define	FD_STDOUT	1
#endif

/* external subroutines */

#if	CF_DEBUG
extern "C" int	debugopen(cchar *) ;
extern "C" int	debugprintf(cchar *,...) ;
extern "C" int	debugclose() ;
extern "C" int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,cchar **argv,cchar **envv) {
	cint	ofd = FD_STDOUT ;
	int		rs ;
	cchar	*fn = "local§cotd" ;
	cchar	*cp ;

#if	CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	if ((argc > 1) && (argv[1] != '\0')) fn = argv[1] ;

	if ((rs = uc_open(fn,O_RDONLY,0666)) >= 0) {
		cint	llen = LINEBUFLEN ;
		int		fd = rs ;
		char		lbuf[LINEBUFLEN+1] ;
		while ((rs = u_read(fd,lbuf,llen)) > 0) {
		    int	ll = rs ;
		    rs = u_write(ofd,lbuf,ll) ;
		    if (rs < 0) break ;
		} /* end while */
		u_close(fd) ;
	} /* end if (open) */

	fprintf(stderr,"main: ret rs=%d\n",rs) ;

#if	CF_DEBUG
	debugprintf("main: exiting rs=%d\n",rs) ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


