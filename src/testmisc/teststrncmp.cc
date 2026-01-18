/* teststrncmp */
/* lang=C99 */

#define	CF_DEBUGS	1

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/time.h>
#include	<cstdio>
#include	<cthex.h>
#include	<usystem.h>

#ifndef	DIGBUFLEN
#define	DIGBUFLEN	40
#endif

#define	VARDEBUGFNAME	"TESTSTRNCMP_DEBUGFILE"


#if	CF_DEBUGS
extern int	debugopen(const char *) ;
extern int	debugprintf(const char *,...) ;
extern int	debugclose() ;
extern int	strlinelen(const char *,int,int) ;
#endif


int main(int argc,mainv argv,mainv envv) {
	int		rs = SR_OK ;
	int		sl = 0 ;
	int		f = FALSE ;
	cchar		*sp = "goodbye-hello" ;
	cchar		*cp ;
	cchar		*s2 = "hellox" ;

#if	CF_DEBUGS
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	f = (strncmp(s2,sp,sl) == 0) ;

	printf("strncmp: f=%u\n",f) ;

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


