/* testutmpacc_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test the |utmpacc(3u)| facility */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_UCSTREAM	0		/* compile-time debugging */

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
#include	<filer.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<rmx.h>			/* LIBUC */
#include	<localmisc.h>		/* LIBU |TIMEBUFLEN| */
#include	<libdebug.h>		/* LIBDEBUG */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/ucstream.ccm"

import libutil ;			/* |lenstr(3u)| */
import ucstream ;

/* local defines */

#define	VARDEBUGFNAME	"TESTUTMPACC_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif
#ifndef	CF_UCSTREAM
#define	CF_UCSTREAM	0		/* compile-time debugging */
#endif


/* imported namespaces */

using libuc::mem ;


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int	main_ucstream	() noex ;
local int	main_sid	(char *,int) noex ;
local int	main_list	(char *,int) noex ;


/* local variables */

cbool		f_debug		= CF_DEBUG ;
cbool		f_ucstream	= CF_UCSTREAM ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		rs1 ;
	(void) argc ;
	(void) argv ;
	(void) envv ;
	(void) rs1 ;
	(void) np ;

#if	CF_DEBUG
	{
	    if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	        if ((rs = debugopen(cp)) >= 0) {
	        DEBUGPRINTF("starting\n") ;
		}
	    } /* end if (getoutenv) */
	}
#endif /* CF_DEBUG */

#if	CF_DEBUG
	DEBUGPRINTF("test rs=%d »no-trailer«",rs) ;
	DEBUGPRINTF("test rs=%d »trailer«\n",rs) ;
	DEBUGPRINTF("test rs=%d s=>%s<",rs,"Hello world!") ;
#endif

	if_constexpr (f_ucstream) {
	    if (rs >= 0) {
	        rs = main_ucstream() ;
	        DEBUGPRINTF("ucstream rs=%d",rs) ;
	    } /* end if (ok) */
	} /* end if_constexpr (f_ucstream) */

	if (rs >= 0) {
	    if (time_t bt ; (rs = utmpacc_boottime(&bt)) >= 0) {
	        char	timebuf[TIMEBUFLEN+1] ;
	        timestr_logz(bt,timebuf) ;
	        printf("bt=%s\n",timebuf) ;
	    }
	}

#if	CF_DEBUG
	DEBUGPRINTF("utmpacc_boottime() rs=%d »trailer«\n",rs) ;
#endif

	if (rs >= 0) {
	    if ((rs = utmpacc_runlevel()) >= 0) {
	        printf("runlevel=>%c< (%d)\n",rs,rs) ;
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
		    if (rs >= 0) {
		        rs = main_sid(uebuf,uelen) ;
		    }
		    if (rs >= 0) {
		        rs = main_list(uebuf,uelen) ;
		    }
		    rs1 = mem.free(uebuf) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (m-a-f) */
	    } /* end if (utmpacc_entbuflen) */
	} /* end if (ok) */

#if	CF_DEBUG
	DEBUGPRINTF("ret rs=%d\n",rs) ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

}
/* end subroutine (main) */


/* local subroutines */

local int main_ucstream() noex {
    	int		rs ;
	int		rs1 ;
	int		len = 0 ; /* return-value */
	cchar		*fn = "/etc/networks" ;
	if (char *lbuf ; (rs = mem.ml(&lbuf)) >= 0) {
	    cint llen = rs ;
	    if (ucstream fs ; (rs = fs.open(fn)) >= 0) {
		while ((rs = fs.readln(lbuf,llen)) > 0) {
		    cint ll = rmeol(lbuf,rs) ;
		    {
			lbuf[ll] = '\0' ;
			printf("ln> %s <\n",lbuf) ;
		    }
		    if (rs < 0) break ;
		} /* end while */
	        rs1 = fs.close ;
	        if (rs >= 0) rs = rs1 ;
		DEBUGPRINTF("fs.cose() rs=%d\n",rs) ;
	    } /* end if (ucstream) */
	    rs1 = mem.free(lbuf) ;
	    if (rs >= 0) rs = rs1 ;;
	} /* end if (m-a-f) */
	DEBUGPRINTF("ret rs=%d len\n",rs,len) ;
	return (rs >= 0) ? len : rs ;
} /* end subroutine (main_ucstream) */

local int main_sid(char *uebuf,int uelen) noex {
    	int		rs ;
	utmpacc_ent	ue ;
	if ((rs = utmpacc_entsid(&ue,uebuf,uelen,-1)) >= 0) {
	    printf("sident -----\n") ;
	    printf("sident type=%hu\n",ue.type ) ;
	    printf("sident sid =%d\n",ue.sid) ;
	    printf("sident id  =%s\n",ue.id) ;
	    printf("sident user=%s\n",ue.user) ;
	    printf("sident line=%s\n",ue.line) ;
	    printf("sident host=%s\n",ue.host) ;
	} /* end if (utmpacc_sident) */
	return rs ;
} /* end subroutine (main_sid) */

local int main_list(char *uebuf,int uelen) noex {
    	int		rs ;
	int		rs1 ;
	DEBUGPRINTF("ent\n") ;
	if (utmpacc_cur cur ; (rs = utmpacc_curbegin(&cur)) >= 0) {
	    utmpacc_ent	ue ;
	    DEBUGPRINTF("curbegin() rs=%d\n",rs) ;
	    while ((rs = utmpacc_curenum(&cur,&ue,uebuf,uelen)) > 0) {
	        printf("listent -----\n") ;
	        printf("listent type=%hu\n",ue.type ) ;
	        printf("listent sid =%d\n",ue.sid) ;
	        printf("listent id  =%s\n",ue.id) ;
	        printf("listent user=%s\n",ue.user) ;
	        printf("listent line=%s\n",ue.line) ;
	        printf("listent host=%s\n",ue.host) ;
	    } /* end while (utmpacc_curenum) */
	    DEBUGPRINTF("while-out rs=%d\n",rs) ;
	    rs1 = utmpacc_curend(&cur) ;
	    if (rs >= 0) rs = rs1 ;
	    DEBUGPRINTF("curend() rs=%d\n",rs) ;
	} /* end if (utmpacc-cur) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (main_list) */


