/* main (testucopen) */

/* program to test the 'uc_open(3uc)' subroutine */


#define	CF_DEBUGS	1		/* compile-time debugging */
#define	CF_DEBUG	0		/* run-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory allocations */


/* revision history:

	= 1998-02-01, David A­D­ Morano

	This subroutine was originally written to do some testing
	on the BIO package.


*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is a test program for the 'uc_open(3uc)' subroutine.


*******************************************************************************/


#include	<envstandards.h>	/* ordered first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstdlib>
#include	<ctype.h>

#include	<usystem.h>
#include	<bfile.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif


/* external subroutines */

#if	CF_DEBUGS || CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugprinthex(cchar *,int,cchar *,int) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* external variables */


/* forward references */

local int procfile(struct proginfo *,bfile *,cchar *) ;


/* exported subroutines */


int main(argc,argv,envv)
int		argc ;
cchar	*argv[] ;
cchar	*envv[] ;
{
	struct proginfo	pi, *pip = &pi ;

	bfile	errfile, *efp = &errfile ;
	bfile	outfile, *ofp = &outfile ;

#if	(CF_DEBUGS || CF_DEBUG) && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs = SR_OK ;
	int	pan = 0 ;
	int	i ;
	int	argl, aol ;
	int	ex = EX_INFO ;
	int	f_usage = FALSE ;

	cchar	*progname, *argp, *aop ;
	cchar	*efname = NULL ;
	cchar	*ofname = NULL ;
	cchar	*cp ;


#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getenv(VARDEBUGFNAME)) == NULL) {
	    if ((cp = getenv(VARDEBUGFD1)) == NULL)
	        cp = getenv(VARDEBUGFD2) ;
	}
	if (cp != NULL)
	    debugopen(cp) ;
	debugprintf("main: starting\n") ;
#endif /* CF_DEBUGS */

#if	(CF_DEBUGS || CF_DEBUG) && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	progname = argv[0] ;

	if (efname == NULL) efname = getenv(VAREFNAME) ;
	if (efname == NULL) efname = BFILE_STDERR ;

	if (bopen(efp,efname,"dwca",0666) >= 0)
	    bcontrol(efp,BC_LINEBUF,0) ;

	if (ofname == NULL) ofname = BFILE_STDOUT ;

	if ((rs = bopen(ofp,ofname,"wct",0666)) >= 0) {
	    int		ai = 1 ;
	    cchar	*fname ;

	    if (argc > 1) {
		for (ai = 1 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
		    fname = argv[ai] ;

		    pan += 1 ;
		    rs = procfile(pip,ofp,fname) ;

		    if (rs < 0) break ;
		} /* end while */
	    } /* end if (arguments) */

	    if ((rs >= 0) && (pan == 0)) {
		    fname = STDFNIN ;
		    rs = procfile(pip,ofp,fname) ;
	    }

	    bclose(ofp) ;
	} /* end if (file-open) */

done:
	ex = (rs >= 0) ? EX_OK : EX_DATAERR ;

retearly:
	bclose(efp) ;

ret0:

#if	(CF_DEBUGS || CF_DEBUG) && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


local int procfile(struct proginfo *pip,bfile *ofp,cchar *fname)
{
	cint	of = O_RDONLY ;
	int	rs ;
	int	wlen = 0 ;

#if	CF_DEBUGS
	debugprintf("procfile: fname=%s\n",fname) ;
#endif

	if ((strcmp(fname,STDFNIN) == 0) || (fname[0] == '-'))
	    fname = "/dev/stdin" ;

	if ((rs = uc_open(fname,of,0666)) >= 0) {
	    cint	to = -1 ;
	    cint	ro = 0 ;
	    cint	llen = LINEBUFLEN ;
	    int		len ;
	    char	lbuf[LINEBUFLEN+1] ;
	    int	fd = rs ;

	    while ((rs = uc_readlnto(fd,lbuf,llen,to)) > 0) {
		len = rs ;

#if	CF_DEBUGS
		debugprintf("procfile: l=>%t<\n",
		    lbuf,strlinelen(lbuf,len,50)) ;
#endif

		rs = bwrite(ofp,lbuf,len) ;
		wlen += rs ;

		if (rs < 0) break ;
	    } /* end while */

	    u_close(fd) ;
	} /* end if (file-open) */

#if	CF_DEBUGS
	debugprintf("procfile: ret rs=%d wlen=%u\n",rs,wlen) ;
#endif

	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (procfile) */


