/* testutmpacc_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test the |utmpacc(3u)| facility */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<utmpacc.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |TIMEBUFLEN| */
#include	<libdebug.h>		/* LIBEBUG */


/* local defines */

#define	VARDEBUGFNAME	"TESTUTMPACC_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif


/* imported namespaces */

using libuc::mem ;


/* local typedefs */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		rs1 ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	(void) np ;
	(void) rs1 ;

#if	CF_DEBUG
	{
	    if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
		printf("debugfile=%s\n",cp) ;
	        rs = debugopen(cp) ;
	        printf("main: debugopen() rs=%d\n",rs) ;
	        DEBUGPRINTF("starting\n") ;
	    }
	}
#endif /* CF_DEBUG */

#ifdef	COMMENT

	if (rs >= 0) {
	    time_t	bt ;
	    if ((rs = utmpacc_boottime(&bt)) >= 0) {
	        char	timebuf[TIMEBUFLEN+1] ;
	        timestr_logz(bt,timebuf) ;
	        printf("bt=%s\n",timebuf) ;
	    }
	}

#if	CF_DEBUG
	DEBUGPRINTF("utmpacc_boottime() rs=%d\n",rs) ;
#endif

	if (rs >= 0) {
	    if ((rs = utmpacc_runlevel()) >= 0) {
	        printf("runlevel=%c\n",rs) ;
	    }
	}

#if	CF_DEBUG
	DEBUGPRINTF("utmpacc_runlevel() rs=%d\n",rs) ;
#endif

	if (rs >= 0) {
	    if ((rs = utmpacc_users(0)) >= 0) {
	        printf("nusers=%d\n",rs) ;
	    }
	}

#if	CF_DEBUG
	DEBUGPRINTF("utmpacc_users() rs=%d\n",rs) ;
#endif

	if (rs >= 0) {
	    if ((rs = utmpacc_entbuflen) >= 0) {
		cint uelen = rs ;
	        if (char *uebuf ; (rs = mem.mall(rs,&uebuf)) >= 0) {
	            UTMPACCENT	ue ;
	            if ((rs = utmpacc_entsid(&ue,uebuf,uelen,-1)) >= 0) {
	                printf("sid=%d\n",ue.sid) ;
	                printf("name=%s\n",ue.user) ;
	                printf("line=%s\n",ue.line) ;
	                printf("host=%s\n",ue.host) ;
	            } /* end if (utmpacc_entsid) */
		    rs1 = mem.free(uebuf) ;
		    if (rs >= 0) rs = rs1 ;;
	        } /* end if (m-a-f) */
	    } /* end if (utmpacc_entbuflen) */
	} /* end if (ok) */

#if	CF_DEBUG
	DEBUGPRINTF("utmpacc_ent() rs=%d\n",rs) ;
	DEBUGPRINTF("out rs=%d\n",rs) ;
#endif

#endif /* COMMENT */

#if	CF_DEBUG
	debugclose() ;
#endif

}
/* end subroutine (main) */


