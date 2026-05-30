/* testbfile_main SUPPORT (testbfile) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* program to test the 'bfile(3b)' subroutine library */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* run-time debugging */

/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written to do some testing
	on the BFILE package.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This is a test program for the 'uc_open(3uc)' subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX */
#include	<sys/param.h>		/* POSIX */
#include	<sys/stat.h>		/* POSIX */
#include	<unistd.h>		/* POSIX */
#include	<fcntl.h>		/* POSIX */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<stdfnames.h>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<bfile.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */


/* local defines */

#define	VARDEBUGFNAME	"TESTBFILE_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* run-time debugging */
#endif


/* imported namespaces */

using libuc::mem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structues */

namespace {
    struct procer {
	mainv		argv ;
	char		*lbuf ;
	int		argc ;
	int		llen ;
	procer(int c,con mainv v) noex : argc(c), argv(v) { } ;
	operator int () noex ;
	int procout() noex ;
	int procfile(bfile *,cchar *) noex ;
    } ; /* end struct (procer) */
} /* end namespace */


/* forward references */


/* local variables */

cpcchar			ofname		= STDFNOUT ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		ex = EX_INFO ;
	DEBUGPRINTF("ent\n") ;
	fprintf(stderr,"ent\n") ;
	(void) envv ;
	if_constexpr (f_debug) {
	    if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	        if ((rs = debugopen(cp)) >= 0) {
	        DEBUGPRINTF("starting\n") ;
		fprintf(stderr,"debugging=%d\n",rs) ;
		}
	    } /* end if (getoutenv) */
	} /* end if_constexpr (f_debug) */
	if ((rs >= 0) && (argc > 1)) {
	    if (procer po(argc,argv) ; (rs = po) >= 0) {
		DEBUGPRINTF("procer rs=%d\n",rs) ;
		ex = EX_OK ;
	    }
	} /* end if (arguments) */
	if (((ex == EX_OK) || (ex == EX_INFO)) && (rs < 0)) {
	    DEBUGPRINTF("-> mapex rs=%d\n",rs) ;
	    ex = mapex(np,rs) ;
	} /* end if */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE() ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

procer::operator int () noex {
    	int		rs ;
	int		rs1 ;
	int		wlen = 0 ; /* return-value */
	if ((rs = mem.ml(&lbuf)) >= 0) {
	    llen = rs ;
	    {
	        rs = procout() ;
		wlen += rs ;
	    }
	    rs1 = mem.free(lbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (bfile) */
	return (rs >= 0) ? wlen : rs ;
} /* end method (procer::operator) */

int procer::procout() noex {
    	int		rs ;
	int		rs1 ;
	int		wlen = 0 ;
	if (bfile bout ; (rs = bout.open(ofname,"wct",0666)) >= 0) {
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cc *fname = argv[ai] ; fname[0]) {
		    rs = procfile(&bout,fname) ;
		    wlen += rs ;
		}
		if (rs < 0) break ;
	    } /* end for */
	    rs1 = bout.close ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (bfile) */
	return (rs >= 0) ? wlen : rs ;
} /* end method (procer::procout) */

int procer::procfile(bfile *ofp,cchar *fname) noex {
	int		rs ;
	int		rs1 ;
	int		wlen = 0 ;
	DEBUGPRINTF("ent fname=%s\n",fname) ;
	if (bfile bin ; (rs = bin.open(fname,"r",0666)) >= 0) {
	    DEBUGPRINTF("bopen() rs=%d\n",rs) ;
	    while ((rs = bin.read(lbuf,llen)) > 0) {
		cint len = rs ;
	        DEBUGPRINTF("bread() rs=%d\n",rs) ;
		if_constexpr (f_debug) {
		    lbuf[len] = '\0' ;
		    DEBUGPRINTF("l=>%s<\n",lbuf) ;
		}
		{
	            DEBUGPRINTF("bwrite()\n",rs) ;
		    rs = ofp->write(lbuf,len) ;
	            DEBUGPRINTF("bwrite() rs=%d\n",rs) ;
		    wlen += rs ;
		}
		if (rs < 0) break ;
	    } /* end while */
	    DEBUGPRINTF("while-out rs=%d wlen=%u\n",rs,wlen) ;
	    rs1 = bin.close ;
	    DEBUGPRINTF("bclose() rs=%d\n",rs1) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (bfile) */
	DEBUGPRINTF("ret rs=%d wlen=%u\n",rs,wlen) ;
	return (rs >= 0) ? wlen : rs ;
} /* end method (procer::procfile) */


