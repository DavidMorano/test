/* testxdr_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written to facilitate
	testing of software writen for RightCore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/************************************************************************

  	Description:
	This program tests the XDR facility often used in RPC.

***************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<rpc/types.h>		/* POSIX® */
#include	<rpc/xdr.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<termios.h>		/* POSIX® */
#include	<csignal>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<field.h>		/* LIBUC */
#include	<strx.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<bfile.h>		/* LIBB */

#include	"config.h"
#include	"defs.h"


/* local defines */

#define	O_SRVFLAGS	(O_RDONLY | O_CREAT | O_NONBLOCK)


/* external subroutines */


/* external variables */


/* forward references */

extern "C" {
    local void		int_alarm() noex ;
    local void		int_signal() noex ;
}


/* gloabal variables */

int		f_alarm ;
int		f_signal ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	bfile		input, *ifp = &input ;
	bfile		output, *ofp = &output ;
	bfile		error, *efp = &error ;
	XDR		xb ;
	termios		ots, nts ;
	sigaction	sigs ;
	sigset_t		signalmask ;
	long		lw ;
	int		len, lenr, rs ;
	int		i, j ;
	int		iw ;
	int		err_fd ;

	char	*progname ;
	char	tmpbuf[100] ;
	char	xbuf[BUFLEN + 1] ;
	char	*bp ;
	char	*cp ;


	if (((cp = getenv("ERROR_FD")) != nullptr) &&
	    (cfdeci(cp,-1,&err_fd) >= 0)) {
	    debugsetfd(err_fd) ;
	}

	progname = strbasename(argv[0]) ;

	if (bopen(efp,BFILE_STDERR,"dwca",0664) >= 0) {
	    bcontrol(efp,BC_LINEBUF,0) ;
	}

	f_signal = false ;
	f_alarm = false ;

/* do something */

	bopen(ofp,BFILE_STDOUT,"dwct",0666) ;


	xdrmem_create(&xb,xbuf,BUFLEN,XDR_ENCODE) ;

	lw = 0x01020304 ;
	xdr_long(&xb,&lw) ;

	iw = 0x0102 ;
	xdr_int(&xb,&iw) ;

#ifdef	COMMENT
	(void) xdr_control(&xb,XDR_GET_BYTES_AVAIL,&lenr) ;

	len = BUFLEN - lenr ;

#else
	len = xdr_getpos(&xb) ;
#endif

#if	CF_DEBUG
	debugprintf("main: len=%d\n",len) ;
#endif

	bwrite(ofp,xbuf,len) ;

	xdr_destroy(&xb) ;


	bclose(ofp) ;


done:
	bclose(efp) ;

	return ES_OK ;

badret:
	bclose(efp) ;

	return ES_BADARG ;

badin:
	bprintf(efp,"%s: could not open input, rs=%d\n",
	    progname,rs) ;

	goto badret ;

badout:
	bprintf(efp,"%s: could not open output, rs=%d\n",
	    progname,rs) ;

	goto badret ;

} /* end subroutine (main) */

void int_alarm(int sig) noex {
    	(void) sig ;
	f_alarm = true ;
} /* end subroutine */

void int_signal(int sig) noex {
	(void) sig ;
	f_signal = true ;
} /* end subroutine */


