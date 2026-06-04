/* testenvmk_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |envmk(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<unistd.h>		/* POSIX */
#include	<fcntl.h>		/* POSIX */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"envmk.h"
#include	"testenvmk_config.h"


/* local defines */

#ifndef	FD_STDOUT
#define	FD_STDOUT	1
#endif

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* exported variables */


/* external subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	[[maybe_unused]] cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
	int		rs1 ;
	[[maybe_unused]] cchar		*fn = "testenvmk_envfile.txt" ;
	fprintf(stderr,"main: ent\n") ;

#if	CF_DEBUG
	if (cchar *cp{} ; rs >= 0) {
	    fprintf(stderr,"main: get1\n") ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) == np) {
	        fprintf(stderr,"main: get2\n") ;
	        if ((cp = getourenv(envv,VARDEBUGFD1)) == np) {
	            fprintf(stderr,"main: get3\n") ;
	            cp = getourenv(envv,VARDEBUGFD2) ;
	        }
	    }
	    if (cp) {
	        fprintf(stderr,"main: debugpen\n") ;
	        rs = debugopen(cp) ;
	        DEBUGPRINTF("starting\n") ;
	        fprintf(stderr,"main: debugpen() rs=%d\n",rs) ;
	    } /* end if (ok) */
	} /* end if (possible debugging) */
#endif /* CF_DEBUG */

	if ((argc > 1) && argv[1][0]) {
	    fn = argv[1] ;
	}

	if (rs >= 0) {
	    if (envmk m ; (rs = envmk_start(&m,envv)) >= 0) {
	        DEBUGPRINTF("envmk-start() rs=%d\n",rs) ;
	        if (mainv ev ; (rs = envmk_getvec(&m,&ev)) >= 0) {
	            DEBUGPRINTF("envmk-getvec() rs=%d\n",rs) ;
		    for (int i = 0 ; ev[i] ; i += 1) {
		        printf("i=%02u %s\n",i,ev[i]) ;
		    } /* end for */
	        } /* end if (envmk_getvec) */
	        DEBUGPRINTF("envmk-getvec-out rs=%d\n",rs) ;
	        rs1 = envmk_finish(&m) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (envmk) */
	    DEBUGPRINTF("envmk-out rs=%d\n",rs) ;
	} /* end if (ok) */

	DEBUGPRINTF("ret rs=%d\n",rs) ;

	DEBUGCLOSE() ;
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = EX_DATAERR ;
	}
	fprintf(stderr,"main: ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
}
/* end subroutine (main) */


