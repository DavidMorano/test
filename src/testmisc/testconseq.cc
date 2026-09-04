/* testconseq SUPPORT (testconseq) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* non-switchable debug print-outs */
#define	CF_BLANKS	0
#define	CF_SD		0		/* use status display */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<termstr.h>
#include	<sbuf.h>
#include	<localmisc.h>

#include	"config.h"


#define	DBUFLEN	200
#define	NBUFLEN	40

extern int	termconseq(char *,int,int,int,int,int,int) ;

#if	CF_DEBUG
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugprinthexblock(cchar *,int,const void *,int) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif



int main(int argc,con mainv argv,con mainv envv) {
	SBUF	b ;

	cint	dlen = DBUFLEN ;
	cint	nlen = NBUFLEN ;
	int	rs ;
	int	dl ;
	int	nl ;
	char	dbuf[DBUFLEN+1] ;
	char	nbuf[NBUFLEN+1] ;


#if	CF_DEBUG 
	{
	    cchar	*cp ;
	if ((cp = getourenv(envv,VARDEBUGFNAME)) == NULL) {
	    if ((cp = getourenv(envv,VARDEBUGFD1)) == NULL)
	        cp = getourenv(envv,VARDEBUGFD2) ;
	}
	if (cp != NULL)
	    debugopen(cp) ;
	debugprintf("main: starting\n") ;
	}
#endif /* CF_DEBUG */


	if ((rs = sbuf_start(&b,dbuf,dlen)) >= 0) {

	sbuf_strw(&b,TERMSTR_VCURS,-1) ; /* save cursor */

#if	CF_SD
	sbuf_strw(&b,TERMSTR_S_SD,-1) ; /* set status-display mode */
#endif /* CF_SD */

	sbuf_chr(&b,'\r') ;

	sbuf_strw(&b,"xxx",-1) ;

#if	CF_BLANKS
	nl = sncpy1(nbuf,nlen,"     ") ;
#else
	rs = termconseq(nbuf,nlen,'X',4,-1,-1,-1) ;
	nl = rs ;
#endif /* CF_BLANKS */

	fprintf(stderr,"main: termconseq() rs=%d\n",rs) ;

	sbuf_strw(&b,nbuf,nl) ;

#if	CF_SD
	sbuf_strw(&b,TERMSTR_R_SD,-1) ; /* restore status-display mode */
#endif /* CF_SD */

	sbuf_strw(&b,TERMSTR_VCURR,-1) ; /* restore cursor */

	    dl = sbuf_finish(&b) ;
	    if (rs >= 0) rs = dl ;
	} /* end if */

	fprintf(stderr,"main: sbuf rs=%d dl=%d\n",rs,dl) ;
#if	CF_DEBUG
	debugprinthexblock("main",80,dbuf,dl) ;
#endif

	if (rs >= 0) {
	    rs = u_write(1,dbuf,dl) ;
	}

#if	CF_DEBUG
	debugclose() ;
#endif

	return 0 ;
} /* end subroutine (main) */


