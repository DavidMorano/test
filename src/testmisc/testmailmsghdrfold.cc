/* testmailmsghdrfold SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<cstdlib>
#include	<cstring>
#include	<cstdio>
#include	<usystem.h>
#include	<bfile.h>
#include	<filer.h>
#include	<localmisc.h>		/* |NTABCOLS| */

#include	"mailmsghdrfold.h"

/* local defines */

#define	VARDEBUGFNAME	"TESTMAILMSGHDRFOLD_DEBUGFILE"

#ifndef	MSGCOLS
#define	MSGCOLS		76
#endif

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* forward references */

local int procprinthdrline(FILER *,int,int,int,cchar *,int) ;
local int filer_hdrkey(FILER *,cchar *) ;
local int	filer_printcont(FILER *,int,cchar *,int) ;

/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	filer		ofile, *ofp = &ofile  ;
	cint	mcols = MSGCOLS ;
	cint	hlen = MAXPATHLEN ;
	int	rs ;
	int	wlen = 0 ;
	cchar	*hdr = "references" ;
	cchar	*ifname = BFILE_STDIN ;

	char	hbuf[MAXPATHLEN+1] ;

#if	CF_DEBUG
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL)
	        debugopen(cp) ;
	    debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */

	if ((rs = filer_start(ofp,1,0z,0,0)) >= 0) {
	        bfile	ifile, *ifp = &ifile ;

	        if ((rs = bopen(ifp,ifname,"r",0666)) >= 0) {
	            cint	llen = LINEBUFLEN ;
	            int		len ;
		    int		ll ;
		    int		ln = 0 ;
		    int		indent = 10 ;
		    cchar	*lp ;
	            char	lbuf[LINEBUFLEN+1] ;

	            while ((rs = breadln(ifp,lbuf,llen)) > 0) {
	                len = rs ;
			ln = 0 ;

	                if (lbuf[len-1] == '\n') len -= 1 ;
	                lbuf[len] = '\0' ;

#if	CF_DEBUG
	debugprintf("main: l=>%r<\n",
		lbuf,strlinelen(lbuf,len,50)) ;
#endif
		        rs = filer_hdrkey(ofp,hdr) ;
			wlen += rs ;
			indent = rs ;

#if	CF_DEBUG
	debugprintf("main: filer_hdrkey() rs=%d\n",rs) ;
#endif

			lp = lbuf ;
			ll = len ;
			if (rs >= 0) {
			    rs = procprinthdrline(ofp,mcols,ln,indent,lp,ll) ;
			    wlen += rs ;
			    ln += 1 ;
#if	CF_DEBUG
	debugprintf("main: procprinthdrline() rs=%d\n",rs) ;
#endif

			}

	                if (rs < 0) break ;
	            } /* end while (reading lines) */

	            bclose(ifp) ;
	        } /* end if (file-open) */

	    filer_finish(ofp) ;
	} /* end if (filer) */

#if	CF_DEBUG
	debugprintf("main: done rs=%d\n",rs) ;
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


/* local subroutines */

/* "indent" is initial indent only! */
local int procprinthdrline(fbp,mcols,ln,indent,lp,ll)
FILER		*fbp ;
int		mcols ;
int		ln ;
int		indent ;
cchar	*lp ;
int		ll ;
{
	MAILMSGHDRFOLD	mf ;

	int	rs ;
	int	wlen = 0 ;

	if ((rs = mailmsghdrfold_start(&mf,mcols,ln,lp,ll)) >= 0) {
	    int	i = 0 ;
	    int	nc = (indent + 1) ;
	    int	leader ;
	    int	sl ;
	    cchar	*sp ;

	    while ((sl = mailmsghdrfold_get(&mf,nc,&sp)) > 0) {
	        leader = (i == 0) ? ' ' : '\t' ;
	        rs = filer_printcont(fbp,leader,sp,sl) ;
	        wlen += rs ;
	        if (rs < 0) break ;
	        i += 1 ;
	        nc = NTABCOLS ;
	    } /* end while */

	    if ((rs >= 0) && (i == 0)) {
	        rs = filer_println(fbp,lp,0) ;
	        wlen += rs ;
	    }

	    mailmsghdrfold_finish(&mf) ;
	} /* end if */

	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (procprinthdrline) */

local int filer_hdrkey(filer *fbp,cchar *kname) noex {
	int	rs = SR_OK ;
	int	wlen = 0 ;

	char	buf[2] ;


	if (fbp == NULL)
	    return SR_FAULT ;

	if (kname == NULL)
	    return SR_FAULT ;

	if (kname[0] == '\0')
	    return SR_INVALID ;

	if (rs >= 0) {
	    rs = filer_write(fbp,kname,-1) ;
	    wlen += rs ;
	}

	if (rs >= 0) {
	    buf[0] = ':' ;
	    buf[1] = '\0' ;
	    rs = filer_write(fbp,buf,1) ;
	    wlen += rs ;
	}

	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (filer_hdrkey) */

local int filer_printcont(fbp,leader,sp,sl)
FILER		*fbp ;
int		leader ;
cchar	*sp ;
int		sl ;
{
	int	rs = SR_OK ;
	int	wlen = 0 ;

	char	buf[2] ;


	if (fbp == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (sl < 0) sl = strlen(sp) ;

	if (sl > 0) {

	    if ((rs >= 0) && (leader > 0)) {
	        buf[0] = leader ;
	        buf[1] = '\0' ;
	        rs = filer_write(fbp,buf,1) ;
	        wlen += rs ;
	    }

	    if (rs >= 0) {
	        rs = filer_write(fbp,sp,sl) ;
	        wlen += rs ;
	    }

	    if (rs >= 0) {
	        buf[0] = '\n' ;
	        buf[1] = '\0' ;
	        rs = filer_write(fbp,buf,1) ;
	        wlen += rs ;
	    }

	} /* end if (non-empty value) */

	return (rs >= 0) ? wlen : rs ;
} /* end subroutine (filer_printcont) */


