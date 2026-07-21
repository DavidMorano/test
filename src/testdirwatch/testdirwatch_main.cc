/* testdirwatch_main SUPPORT (testdirwatch) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* directory watching testing */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	1

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/******************************************************************************

  	Description:
	This program tests the DW object.

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<dirent.h>		/* OISUX® */
#include	<ftw.h>			/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<csignal>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<exitcodes.h>		/* LUBU */
#include	<localmisc.h>		/* LUBU */
#include	<bfile.h>		/* LIBB */

#include	"config.h"
#include	"defs.h"
#include	"dw.h"



/* local defines */

#define	NLOOPS		100
#define	SLEEPTIME	3


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	DW		dir ;
	DW_CUR	cur ;
	bfile		outfile, *ofp = &outfile ;
	int	ex = EX_INFO ;
	int	rs, rs1, i, j, len ;
	int	fd_debug ;
	int	cl ;

	char	buf[MAXPATHLEN + 1] ;
	char	*cp, *cp1, *cp2 ;
	char	*dirname ;
	char	*pr = NULL ;
	char	*progname ;


	if ((cp = getenv(VARDEBUGFD1)) == NULL)
	    cp = getenv(VARDEBUGFD2) ;

	if ((cp != NULL) &&
	    (cfdeci(cp,-1,&fd_debug) >= 0))
	    debugsetfd(fd_debug) ;


	progname = argv[0] ;
	if (bopen(ofp,BFILE_STDOUT,"wct",0666) >= 0)
	    bcontrol(ofp,BC_LINEBUF,0) ;


#if	CF_DEBUGS
	debugprintf("main: entered\n") ;
#endif


	if ((argc >= 2) && (argv[1] != NULL))
	    dirname = argv[1] ;

	    else
	    dirname = "q" ;

#if	CF_DEBUGS
	debugprintf("main: dirname=%s\n",dirname) ;
#endif


	rs = dw_start(&dir,dirname) ;

#if	CF_DEBUGS
	debugprintf("main: dw_start() rs=%d\n",rs) ;
#endif

	if (rs >= 0) {

	    DW_ENT	e ;

	    time_t	daytime ;

	    int		jid ;


	    for (i = 0 ; i < NLOOPS ; i += 1) {

	        sleep(SLEEPTIME) ;

	        daytime = time(NULL) ;

	        if (dw_check(&dir,daytime) > 0) {

	            dw_curbegin(&dir,&cur) ;

	            while (TRUE) {

	                rs1 = dw_enumcheckable(&dir,&cur,&e) ;

#if	CF_DEBUGS
	debugprintf("main: dw_enumcheckable() rs=%d\n",rs1) ;
#endif

	                jid = rs1 ;
	                if (rs1 < 0) break ;

	                bprintf(ofp,"checkable jid=%d %s\n",
	                    jid,e.name) ;

	            } /* end while */

	            dw_curend(&dir,&cur) ;

	        } /* end if */

	    } /* end while */

	    dw_finish(&dir) ;

	} else
	    bprintf(ofp,"couldn't initialize (%d)\n",rs) ;


	ex = EX_OK ;


done:

#if	CF_DEBUGS
	debugprintf("main: return ex=%d\n",ex) ;
#endif

	bclose(ofp) ;

	return ex ;
}
/* end subroutine (main) */



/* LOCAL SUBROUTINES */




