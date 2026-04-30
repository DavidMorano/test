/* testpathclean_main SUPPORT */

/* test the |pathclean(3)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUGS		1	/* non-switchable debug print-outs */
#define	CF_DMALLOCSHUTDOWN	0	/* already handled by 'exit(3c)' */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/******************************************************************************

  	Description:
	This little subroutine tests something! :-)

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<csignal>
#include	<cstddef>
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<bfile.h>
#include	<field.h>
#include	<paramfile.h>
#include	<sfx.h>
#include	<timestr.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
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


/* exported variables */


/* exported subrouines */

int main(int argc,con mainv argv,con mainv envv) {
	paramfile	params ;
	bfile	infile, *ifp = &infile ;
	bfile	outfile, *ofp = &outfile ;
	time_t	daytime ;
	int	rs, i, n ;
	int	len, sl, cl ;
	int	fd_debug = -1 ;
	char	linebuf[LINEBUFLEN + 1] ;
	char	pathbuf[MAXPATHLEN + 1] ;
	char	timebuf[TIMEBUFLEN + 1] ;
	char	*sp, *cp, *vp ;

	if ((cp = getenv(VARDEBUGFD1)) == nullptr) {
	    cp = getenv(VARDEBUGFD2) ;
	}

	if ((cp != nullptr) &&
	    (cfdeci(cp,-1,&fd_debug) >= 0))
	    debugsetfd(fd_debug) ;


#if	CF_DEBUGS
	debugprintf("main: program entered\n") ;
#endif

	bopen(ofp,BFILE_STDOUT,"dwct",0666) ;

	bopen(ifp,BFILE_STDIN,"dr",0666) ;

	bprintf(ofp,"CLEANPATH subroutine test program\n") ;

/* loop stuff */

	forever {
	    daytime = time(nullptr) ;

	    bprintf(ofp,"path> ") ;

	    bflush(ofp) ;

	    rs = breadln(ifp,linebuf,LINEBUFLEN) ;

	    len = rs ;
	    if (rs <= 0)
	        break ;

	    if (linebuf[len - 1] == '\n')
	        len -= 1 ;

	    linebuf[len] = '\0' ;
	    sl = sfshrink(linebuf,len,&sp) ;

	    sp[sl] = '\0' ;

	bprintf(ofp,"before> %s\n",sp) ;

		rs = pathclean(pathbuf,sp,sl) ;

#if	CF_DEBUGS
	debugprintf("main: pathclean() rs=%d pathbuf=%t\n",rs,pathbuf,rs) ;
#endif

	bprintf(ofp,"after rs=%d> %s\n",rs,pathbuf) ;

		if (rs < 0)
			break ;

	} /* end while */

	bprintf(ofp,"\n") ;

	bclose(ifp) ;

	bclose(ofp) ;

#if	CF_DEBUGS
	            debugprintf("main: ret\n") ;
#endif

#if	defined(DMALLOC) && CF_DMALLOCSHUTDOWN
	debugprintf("main: dmalloc_shutdown()\n") ;
	dmalloc_shutdown() ;
#endif

	return EX_OK ;
}
/* end subroutine (main) */



