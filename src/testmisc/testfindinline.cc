/* testfindinline SUPPORT (Test-Finf-InLine) */
/* charset=ISO8859-1 */
/* lang=C89 */

/* test the |findinline(3dam)| subroutine */
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
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<getx.h>
#include	<bfile.h>
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"findinline.h"

#define	VARDEBUGFNAME	"TESTFINDINLINE_DEBUGFILE"

int main(int argc,con mainv argv,con mainv envv) noex {
	findinline	fi ;
	bfile	ofile, *ofp = &ofile ;
	bfile	ifile, *ifp = &ifile ;
	cchar	*ofname = nullptr ;
	cchar	*ifname = nullptr ;
	cchar	*sp ;

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs ;
	int	rs1 ;
	int	sl ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	if ((ofname == nullptr) || (ofname[0] == '\0') || (ofname[0] == '-'))
		ofname = BFILE_STDOUT ;

	if ((rs = bopen(ofp,ofname,"wct",0666)) >= 0) {

#ifdef	COMMENT
	if (argv != nullptr) {
	    int	ai ;
	    for (ai = 1 ; (ai < argc) && (argv[ai] != nullptr) ; ai += 1) {


#if	CF_DEBUG
	        debugprintf("main: findinline() rs=%d\n",rs) ;
#endif

	    } /* end for */
	} /* end if (arguments) */
#endif /* COMMENT */

	if ((ifname == nullptr) || (ifname[0] == '\0') || (ifname[0] == '-')) {
		ifname = BFILE_STDIN ;
	}

	if ((rs = bopen(ifp,ifname,"r",0666)) >= 0) {
	    findinline	fi ;
	    cint	llen = LINEBUFLEN ;
	    int		len ;
	    cchar	*fmt ;
	    char	lbuf[LINEBUFLEN+1] ;
	    while ((rs = breadln(ifp,lbuf,llen)) > 0) {
		len = rs ;

		bprintln(ofp,lbuf,len) ;

		if ((sl = findinline(&fi,lbuf,len)) > 0) {
		    fmt = "» sl=%u k=%r v=>%r<\n" ;
		    bprintf(ofp,fmt,sl,fi.kp,fi.kl,fi.vp,fi.vl) ;
		}

#if	CF_DEBUG
	        debugprintf("main: findinline() rs=%d\n",sl) ;
#endif

	    } /* end while */
	    bclose(ifp) ;
	} /* end if (infile-open) */

	    bclose(ofp) ;
	} /* end if (outfile-open) */

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


