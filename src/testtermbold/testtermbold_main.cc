/* termtermbold SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test term stuff */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1988-02-02, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Name:
	testermbold

	Description:
	Test getting bold rendition on a (ANSI) terminal.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<termstr.h>		/* LIBUC */
#include	<stdfnames.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<bfile.h>		/* LIBB */


/* local defines */

#define		TIME_ON		2
#define		TIME_OFF	2
#define		NLOOPS		2

#ifndef	VARDEBUGFNAME
#define VARDEBUGFNAME		"TESTTERMBOLD_DEBUGFILE"
#endif

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* local variables */

cint		dlen		= MAXPATHLEN ;
cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv envv) {
	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	if_constexpr (f_debug) {
	    if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
		fprintf(stderr,"debugfile=%s\n",cp) ;
	        if ((rs = DEBUGOPEN(cp)) >= 0) {
	        DEBUGPRINTF("starting\n") ;
		}
		fprintf(stderr,"debugging=%d\n",rs) ;
	    } /* end if (getoutenv) */
	} /* end if_constexpr (f_debug) */
	DEBUGPRINTF("ent\n") ;
	if (bfile bout ; (rs = bout.open(STDFNOUT,"wct",0666)) >= 0) {
	    bout.printf("%s",TERMSTR_NORM) ;
	    bout.flush() ;
	    sleep(TIME_OFF) ;
	    for (int i = 0 ; i < NLOOPS ; i += 1) {
	        char	dbuf[dlen + 1] ;
	        char	*bp ;
		DEBUGPRINTF("loop=%d\n",i) ;
		bp = dbuf ;

		bp += sprintf(bp, 
		"%s%s%s\033[14;40H%s",
		TERMSTR_SAVE,TERMSTR_BOLD,TERMSTR_BLINK,TERMSTR_EL) ;

		bp += sprintf(bp, 
		"\033[15;40H%s",
		TERMSTR_EL) ;

		bp += sprintf(bp, 
		"\033[16;40H          can you see this%s",
		TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[17;40H          yes I can but%s",TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[18;40H          do I want to%s",TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[19;40H          today or tomorrow%s",TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[20;40H          I love you tomorrow%s",TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[21;40H          we're always a day%s",TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[22;40H          away, away from home%s",
		TERMSTR_EL) ;

		bp += sprintf(bp,
		"\033[23;40H          and away a day%s%s",
		TERMSTR_EL,TERMSTR_RESTORE) ;

		if ((rs = bout.write(dbuf,intconv(bp - dbuf))) >= 0) {
		    DEBUGPRINTF("bflush\n") ;
		    rs = bout.flush ;
		    sleep(TIME_ON) ;
		}
		DEBUGPRINTF("loop rs=%d\n",rs) ;
		if (rs < 0) break ;
	    } /* end for */
	    rs1 = bout.close ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (bfile) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


