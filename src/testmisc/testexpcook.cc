/* testexpcookie (testexpcook) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"expcook.h"

#include	"defs.h"
#include	"config.h"


#ifndef	MKCHAR
#define	MKCHAR(ch)	((ch) & UCHAR_MAX)
#endif

extern int	sfcookkey(char *,int,char **) ;


struct cookpair {
	char	*k ;
	char	*v ;
} ;

static const struct cookpair	pairs[] = {
	{ "R", "/usr/add-on/pcs" },
	{ "N", "nodename" },
	{ "U", "username" },
	{ "tz", "time-zone" },
	{ "hwserial", "hardware-serial" },
	{ NULL, NULL }
} ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	EXPCOOK		ec ;
	EXPCOOK_CUR	cur ;

	cint	klen = KBUFLEN ;
	cint	wch = MKCHAR('¿') ;

#if	CF_DEBUG && CF_DEBUGMALL
	uint	mo_start = 0 ;
#endif

	int	rs ;
	int	cl ;

	char	*s = "here %R is %{tz} thing %{} %{junker} end" ;
	char	*cp ;

	char	kbuf[KBUFLEN+1] = { 0 } ;


#if	CF_DEBUG
	if ((cp = getenv(VARDEBUGFNAME)) == NULL) {
	    if ((cp = getenv(VARDEBUGFD1)) == NULL)
	        cp = getenv(VARDEBUGFD2) ;
	}
	if (cp != NULL)
	    debugopen(cp) ;
	debugprintf("main: starting\n") ;
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	cl = sfcookkey(s,-1,&cp) ;

	printf("cl=%d cp={%p}\n",cl,cp) ;

	if (cl >= 0)
	strdcpy1w(kbuf,klen,cp,cl) ;

	printf("k=%s\n",kbuf) ;

/* start in */

	if ((rs = expcook_start(&ec)) >= 0) {
	    int		i ;
	    char	*k, *v ;

	    for (i = 0 ; (rs >= 0) && (pairs[i].k != NULL) ; i += 1) {
		k = pairs[i].k ;
		v = pairs[i].v ;
		rs = expcook_add(&ec,k,v,-1) ;
	    }

	    if (rs >= 0) {
		if ((rs = expcook_curbegin(&ec,&cur)) >= 0) {
		    cint	rlen = VBUFLEN ;
		    char	rbuf[VBUFLEN+1] ;
	    	    int		rl ;
	            while ((rl = expcook_curenum(&ec,&cur,rbuf,rlen)) >= 0) {

			printf("pair> %s\n",rbuf) ;

		    } /* end while */
		    expcook_curend(&ec,&cur) ;
		} /* end if (cursor) */
	    } /* end if */

	    if (rs >= 0) {
		cint	rlen = VBUFLEN ;
		char		rbuf[VBUFLEN+1] ;
		if ((rs = expcook_exp(&ec,wch,rbuf,rlen,s,-1)) >= 0) {

		    printf("exp> %s\n",rbuf) ;

		} /* end if (expand) */
	    } /* end if (substitutions) */

	    expcook_finish(&ec) ;
	} /* end if (expandcookie) */

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


