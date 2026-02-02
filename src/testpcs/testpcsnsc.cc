/* testpcsnsc SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#define	CF_DEBUGS	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory allocations */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstring>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>

#include	"pcsnsc.h"


#define	VARDEBUGFNAME	"TESTPCS_DEBUGFILE"
#define	VARDEBUGFD1	"TESTPCS_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#ifndef	VARPRLOCAL
#define	VARPRLOCAL	"PCS"
#endif

#define	PRLOCAL		"/usr/add-on/pcs"
#define	TO_PCS		10

/* external subroutines */

#if	CF_DEBUGS
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
extern int	debugprinthexblock(cchar *,int,const void *,int) ;
#endif


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) noex {
	PCSNSC		mc ;
	FILE		*ofp = stdout ;
	int		rs ;
	int		rs1 ;
	int		to = TO_PCS ;
	cchar	*pr ;

#if	CF_DEBUGS
	{
	    cchar		*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	        rs = debugopen(cp) ;
	        debugprintf("main: starting DFD=%d\n",rs) ;
	    }
	}
#endif /* CF_DEBUGS */

	if ((pr = getenv(VARPRLOCAL)) == nullptr) {
	    pr = PRLOCAL ;
	}

/* object, program-root, req-filename, time-out */

	if ((rs = pcsnsc_open(&mc,pr,nullptr,to)) >= 0) {
	    fprintf(ofp,"main: pcsnsc_open() rs=%d\n",rs) ;
	    if ((rs = pcsnsc_status(&mc)) >= 0) {
		cint	w = pcsnsreq_pcsname ;
		cint	rlen = REALNAMELEN ;
		cchar		*un = "dam" ;
		char		rbuf[REALNAMELEN+1] ;
#if	CF_DEBUGS
	debugprintf("main: pcsnsc_getval() un=%s w=%u\n",un,w) ;
#endif
		if ((rs = pcsnsc_getval(&mc,rbuf,rlen,un,w)) >= 0) {
#if	CF_DEBUGS
	debugprintf("main: pcsnsc_getval() rs=%d r=>%s<\n",rs,rbuf) ;
#endif
	    	    fprintf(ofp,"main: n=>%s<\n",rbuf) ;
		}
	    }
	    fprintf(ofp,"main: pcsnsc_status() rs=%d\n",rs) ;
	    rs1 = pcsnsc_close(&mc) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (pcsnsc) */

#if	CF_DEBUGS
	debugprintf("main: ret rs=%d\n",rs) ;
#endif

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


