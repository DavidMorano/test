/* testattach SUPPORT (testattach) */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>

#include	"defs.h"
#include	"config.h"


#ifndef	MKCHAR
#define	MKCHAR(ch)	((ch) & UCHAR_MAX)
#endif

extern int	sfcookkey(cchar *,int,cchar **) ;

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugprinthex(cchar *,int,cchar *,int) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


int main(int argc,con mainv argv,con mainv envv) {
	cint	klen = KBUFLEN ;
	cint	wch = MKCHAR('¿') ;
	uint	mo_start = 0 ;
	int	rs ;
	int	cl ;
	cchar	*s = "here %R is %{tz} thing %{} %{junker} end" ;
	cchar	*cp ;
	cchar	*ad = "ad" ;
	cchar	*mnt = "mnt" ;
	char	kbuf[KBUFLEN+1] = { 0 } ;

	(void) argc ;
	(void) argv ;
	(void) envv ;
#if	CF_DEBUG
	if ((cp = getenv(VARDEBUGFNAME)) == NULL) {
	    if ((cp = getenv(VARDEBUGFD1)) == NULL)
	        cp = getenv(VARDEBUGFD2) ;
	}
	if (cp != NULL)
	    debugopen(cp) ;
	debugprintf("main: starting\n") ;
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	if ((rs = u_open(ad,O_RDONLY,0666)) >= 0) {
	    int	dfd = rs ;

#if	CF_DEBUG
	    debugprintf("main: u_open() rs=%d\n",rs) ;
#endif /* CF_DEBUG */

	    if ((rs = uc_fattach(dfd,mnt)) >= 0) {

#if	CF_DEBUG
	    debugprintf("main: uc_fattach() rs=%d\n",rs) ;
#endif /* CF_DEBUG */
		sleep(60) ;
	    }

#if	CF_DEBUG
	    debugprintf("main: uc_fattach rs=%d\n",rs) ;
#endif /* CF_DEBUG */

	    u_close(dfd) ;
	} /* end if (open) */

#if	CF_DEBUG
	    debugprintf("main: exiting rs=%d\n",rs) ;
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


