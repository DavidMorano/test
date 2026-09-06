/* testconfigvars_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the CONFIGVARS object */
/* version %I% last-modified %G% */

#define	CF_DEBUG		1	/* non-switchable debug print-outs */
#define	CF_DMALLOCSHUTDOWN	0	/* already handled by |exit(3c)| */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/******************************************************************************

  	Description:
	This little subroutine tests the CONFIGVARS object.

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<csignal>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<field.h>		/* LIBUC */
#include	<vecitem.h>		/* LIBUC */
#include	<sfx.h>			/* LIBUC */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<bfile.h>		/* LIBB */

#include	"configvars.h"


/* local defines */

#ifndef	CONFFNAME
#define	CONFFNAME	"conf"
#endif

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif

#ifndef	CF_DEBUG
#define	CF_DEBUG	1	/* non-switchable debug print-outs */
#endif


/* external subroutines */


/* external variables */


/* local variables */

constexpr char		tterms[] = {
	        0x00, 0x1B, 0x00, 0x00,
	        0x01, 0x10, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00
} ; /* end array */

constexpr char		dterms[] = {
	        0x00, 0x1B, 0x00, 0x00,
	        0x01, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00,
	        0x00, 0x00, 0x00, 0x00
} ; /* end array */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
	bfile	infile, *ifp = &infile ;
	bfile	outfile, *ofp = &outfile ;
	CONFIGVARS	cvs ;
	vecitem		errs ;
	field		f ;
	time_t	daytime ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int	i, n ;
	int	len, sl, cl ;
	int	fd_debug = -1 ;
	cchar	*sp, *cp, *vp ;
	char	linebuf[LINEBUFLEN + 1] ;
	char	timebuf[TIMEBUFLEN + 1] ;

	if ((cp = getenv(VARDEBUGFD1)) == nullptr) {
	    cp = getenv(VARDEBUGFD2) ;
	}

	if ((cp != nullptr) &&
	    (cfdeci(cp,-1,&fd_debug) >= 0)) {
	    debugsetfd(fd_debug) ;
	}


#if	CF_DEBUG
	DEBUGPRINTF("starting\n") ;
#endif

	bopen(ifp,BFILE_STDIN,"dr",0666) ;


	bopen(ofp,BFILE_STDOUT,"dwct",0666) ;

	bprintf(ofp,"CONFIGVARS object test program\n") ;


/* initial stuff */

	vecitem_start(&errs,10,0) ;

	if ((argc > 1) && (argv[1] != nullptr)) {
	    cp = argv[1] ;
	} else {
	    cp = CONFFNAME ;
	}

	    rs = configvars_open(&cvs,cp,&errs) ;

#if	CF_DEBUG
	DEBUGPRINTF("configvars_open() rs=%d\n",rs) ;
#endif

	{



	} /* end block */


#ifdef	COMMENT

/* loop stuff */

	while (TRUE) {

	    u_time(&daytime) ;

	    bprintf(ofp,"query name> ") ;

	    bflush(ofp) ;

	    len = breadln(ifp,linebuf,LINEBUFLEN) ;

	    if (len <= 0)
	        break ;

	    if (linebuf[len - 1] == '\n')
	        len -= 1 ;

	    linebuf[len] = '\0' ;
	    sl = sfshrink(linebuf,len,&sp) ;

	    sp[sl] = '\0' ;

/* check on the parameter file */

	    configvars_check(&cvs,daytime,&errs) ;

/* process the current query */

	    if (len > 0) {

	        paramfile_cur	cur ;


	        configvars_curbegin(&cvs,&cur) ;

	        for (i = 0 ; TRUE ; i += 1) {

	            rs = configvars_fetch(&cvs,sp,&cur,&vp) ;

#if	CF_DEBUG
	            DEBUGPRINTF("configvars_fetch() rs=%d\n",rs) ;
#endif

	            if (rs < 0)
	                break ;

	            bprintf(ofp,"%i value=>%s<\n",i,vp) ;

	        } /* end for */

	        configvars_curend(&cvs,&cur) ;

	    } /* end if (had a non-zero length query) */

	} /* end while */

#endif /* COMMENT */

	bprintf(ofp,"\n") ;


#if	CF_DEBUG
	            DEBUGPRINTF("configvars_close()\n") ;
#endif

	configvars_close(&cvs) ;

#if	CF_DEBUG
	            DEBUGPRINTF("vecitem_finish()\n") ;
#endif

	vecitem_finish(&errs) ;


#if	CF_DEBUG
	            DEBUGPRINTF("bclose(ofp)\n") ;
#endif

	bclose(ofp) ;

#if	CF_DEBUG
	            DEBUGPRINTF("bclose(ifp)\n") ;
#endif

	bclose(ifp) ;

#if	CF_DEBUG
	            DEBUGPRINTF("ret\n") ;
#endif

#if	defined(DMALLOC) && CF_DMALLOCSHUTDOWN
	DEBUGPRINTF("dmalloc_shutdown()\n") ;
	dmalloc_shutdown() ;
#endif

	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


