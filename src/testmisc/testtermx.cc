/* testterm_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test term stuff */
/* version %I% last-modified %G% */


/* revision history:

	= 1988-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<termstr.h>


/* local defines */

#define		TIME_ON		2
#define		TIME_OFF	2


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	long	clock ;
	int	len, j ;
	char	*bp, dbuf[1000] ;

	printf("%s",TERMSTR_NORM) ;
	fflush(stdout) ;

	sleep(TIME_OFF) ;

	while (1) {

		bp = dbuf ;

		bp += sprintf(bp, 
		"%s\033[14;40H%s",
		TERMSTR_SAVE,TERMSTR_EL) ;

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

#ifdef	COMMENT
		j = 0 ;
		while (j < (bp - dbuf)) {

		for (int i = 0 ; i < 16 ; i += 1) {
			printf(" %02X",dbuf[j++] & 0xFF) ;
		} /* end for */

		printf("\n") ;

		} ;

		fflush(stdout) ;
#endif

		write(1L,dbuf,bp - dbuf) ;

		sleep(TIME_ON) ;
	} /* end while */
} /* end subrutine (main) */


