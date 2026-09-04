/* main (testgetsystypenum) */
/* charset=ISO8859-1 */
/* lang=C++20 */

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
#include	<sys/utsname.h>
#include	<climits>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>

#include	"defs.h"
#include	"config.h"


/* local defines */

#ifndef	MKCHAR
#define	MKCHAR(ch)	((ch) & UCHAR_MAX)
#endif

#ifndef	DIGBUFLEN
#define	DIGBUFLEN	40
#endif


/* external subroutines */

extern int	sfcookkey(cchar *,int,cchar **) ;

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugprinthex(cchar *,int,cchar *,int) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* exported subroutines */


int main(argc,argv,envv)
int		argc ;
cchar	*argv[] ;
cchar	*envv[] ;
{
	struct utsname		u ;

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs ;

	cchar	*cp ;


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

	if ((rs = u_uname(&u)) >= 0) {
	    char	tbuf[MAXNAMELEN+1] = { 0 } ;
	    char	nbuf[DIGBUFLEN+1] = { 0 } ;

	    rs = getsystypenum(tbuf,nbuf,u.sysname,u.release) ;

	    printf("rs=%d t=%s n=%s\n",rs,tbuf,nbuf) ;

	} /* end if (uname) */

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


