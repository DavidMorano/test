/* testdirname_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif


/* external subroutines */

extern int	fgetline(FILE *,char *,int) ;
extern int	sfshrink(cchar *,int,cchar **) ;
extern int	sfbasename(cchar *,int,cchar **) ;
extern int	sfdirname(cchar *,int,cchar **) ;

extern char	*strwcpy(char *,cchar *,int) ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	cint		llen = LINEBUFLEN ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		sl, cl, dl ;
	int		len ;

	cchar	*pp ;

	char	lbuf[LINEBUFLEN + 1] ;
	char	dirbuf[LINEBUFLEN + 1] ;
	char	*sp ;
	char	*cp ;
	char	*dp ;


	fprintf(stdout,"arg0=%s\n",argv[0]) ;

	pp = getexecname() ;

	if (pp) {
		fprintf(stdout,"execname=%s\n",pp) ;
	}
	while ((len = fgetln(stdin,lbuf,llen)) > 0) {

	    sl = sfshrink(lbuf,len,&sp) ;

	    if (sl > 0) {

	        sp[sl] = '\0' ;

	    cl = sfdirname(sp,sl,&cp) ;

		dp = dirbuf ;
		dl = cl ;
	        strwcpy(dirbuf,cp,cl) ;

	        fprintf(stdout,"%-40s => %s (%d)\n",sp,dp,dl) ;

	    }

	} /* end while */
	return ex ;
} /* end subroutine (main) */


