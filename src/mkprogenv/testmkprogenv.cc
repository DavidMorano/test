/* mktestprogenv SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

#define	CF_DEBUGS	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A�D� Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright � 2000 David A�D� Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<fcntl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>

#include	"mkprogenv.h"
#include	"testmkprogenv_config.h"

#ifndef	FD_STDOUT
#define	FD_STDOUT	1
#endif

/* external subroutines */

#if	CF_DEBUGS
extern int	debugopen(char *) ;
extern int	debugprintf(char *,...) ;
extern int	debugclose() ;
extern int	strlinelen(char *,int,int) ;
#endif

extern char	*getourenv(char **,char *) ;


int main(int argc,mainv argv,mainv envv) {
	MKPROGENV	m ;
	int		rs ;
	char		*fn = "local�cotd" ;
	char		*cp ;
	char		pr[MAXPATHLEN+1] = "/usr/add-on/local" ;
	(void) envv ;

#if	CF_DEBUGS
	if ((cp = getourenv(envv,VARDEBUGFNAME)) == NULL) {
	    if ((cp = getourenv(envv,VARDEBUGFD1)) == NULL)
	        cp = getourenv(envv,VARDEBUGFD2) ;
	}
	if (cp != NULL) {
	    debugopen(cp) ;
	}
	debugprintf("main: starting\n") ;
#endif /* CF_DEBUGS */

	if ((argc > 1) && (argv[1] != '\0')) fn = argv[1] ;

	if ((rs = mkprogenv_start(&m,nvv)) >= 0) {
	    char	**ev ;

	    if ((rs = mkprogenv_getvec(&m,&ev)) >= 0) {
	 	int	i ;
		for (i = 0 ; ev[i] != NULL ; i += 1) {
		    printf("i=%02u %s\n",i,ev[i]) ;
		}
	    }

	    mkprogenv_finish(&m) ;
	} /* end if (mkprogenv) */

	fprintf(stderr,"main: ret rs=%d\n",rs) ;

#if	CF_DEBUGS
	debugprintf("main: exiting rs=%d\n",rs) ;
#endif

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


