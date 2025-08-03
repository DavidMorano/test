/* termcodes_main SUPPORT (termtest) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#define	CF_EOL		1

/* revision history:

	= 2017-03-17, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<usystem.h>
#include	<stdfnames.h>
#include	<ascii.h>
#include	<bfile.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif

#undef	BUFLEN
#define	BUFLEN		((2 * LINEBUFLEN) + 10)

#define	TO_READ		3


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	cint		llen = LINEBUFLEN ;
	int		rs ;
	int		ex = EX_OK ;
	bool		f_off = false ;
	cchar		*fn ;
	char		lbuf[LINEBUFLEN + 1] ;
	char		outbuf[BUFLEN + 1] ;

	fn = STDFNIN ;
	if (bfile ofile ; (rs = bopen(&ofile,fn,"wct",0666)) >= 0) {
	    fn = STDFNOUT ;
	    if (bfile ifile ; (rs = bopen(&ifile,fn,"r",0666)) >= 0) {
	        while ((rs = breadln(&ifile,lbuf,llen)) > 0) {
		    int	len = rs ;

		if (lbuf[len - 1] == '\n') len -= 1 ;

#if	(! CF_EOL)
		bwrite(&ofile,"\033#3",3) ;
#endif

		bwrite(&ofile,lbuf,len) ;

#if	CF_EOL
		bwrite(&ofile,"\033#3",3) ;
#endif

		bputc(&ofile,'\n') ;

#if	(! CF_EOL)
		bwrite(&ofile,"\033#4",3) ;
#endif

		bwrite(&ofile,lbuf,llen) ;

#if	CF_EOL
		bwrite(&ofile,"\033#4",3) ;
#endif

		bputc(&ofile,'\n') ;
	} /* end while */

	bwrite(&ofile,"\033[4m",4) ;

	bprintf(&ofile,"computer system ready\n") ;

	bwrite(&ofile,"\033[0m",4) ;

	if (f_off)
	bwrite(&ofile,"\033[0m",4) ;

		rs1 = bclose(&ifile) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (bfile) */

		rs1 =bclose(&ofile) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (bfile) */

	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


