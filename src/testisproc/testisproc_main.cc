/* testisproc_main SUPORT (testisproc) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	1		/* compile-time debugging */
#define	CF_WAITPID	0		/* use 'u_waitpid(2u)' */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<spawnproc.h>
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"config.h"
#include	"defs.h"


/* local defines */

#define	PROG_SLEEP	"/usr/bin/sleep"

#define	NSLEEP_CHILD	2
#define	NSLEEP_PARENT	3


/* external subroutines */

extern int	isproc(int) ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(argc,con mainv argv,con mainv envv) {
	pid_t	pid ;
	int	rs = SR_OK ;
	int	rs1 ;
	int	cl ;
	int	nsleep = NSLEEP_PARENT ;
	int	cstat ;
	int	f = FALSE ;

	char	*cp ;

#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	pid = -1 ;

	if (argc > 1) {

		int	iw ;


		rs = cfdeci(argv[1],-1,&iw) ;
		pid = (pid_t) iw ;
		if (rs < 0)
			goto badargval ;

	} /* end if */

	if (pid < 0) {
		SPAWNPROC	ps ;
		char	*av[4] ;
		char	digbuf[DIGBUFLEN + 1] ;


		ctdeci(digbuf,DIGBUFLEN,NSLEEP_CHILD) ;

		memset(&ps,0,sizeof(SPAWNPROC)) ;

		av[0] = PROG_SLEEP ;
		av[1] = digbuf ;
		av[2] = NULL ;

		rs = spawnproc(&ps,PROG_SLEEP,av,NULL) ;
		pid = rs ;
	} /* end if */

	if (rs < 0)
	    goto ret1 ;

	fprintf(stdout,"\npid=%u before\n",pid) ;

	rs1 = u_kill(pid,0) ;
	fprintf(stdout,"u_kill() pid=%u rs1=%d\n",
		(uint) pid,rs1) ;

	rs1 = u_getpgid(pid) ;
	fprintf(stdout,"u_getpgid() pid=%u rs1=%d\n",
		(uint) pid,rs1) ;

	f = isproc(pid) ;
	fprintf(stdout,"isproc() pid=%u is %s\n",
		(uint) pid,((f) ? "there" : "not there")) ;

	if (nsleep > 0)
		sleep(nsleep) ;

	fprintf(stdout,"\npid=%u after sleep exit\n",pid) ;

	rs1 = u_kill(pid,0) ;
	fprintf(stdout,"u_kill() pid=%u rs1=%d\n",
		(uint) pid,rs1) ;

	rs1 = u_getpgid(pid) ;
	fprintf(stdout,"u_getpgid() pid=%u rs1=%d\n",
		(uint) pid,rs1) ;

	f = isproc(pid) ;
	fprintf(stdout,"isproc() pid=%u is %s\n",
		(uint) pid,((f) ? "there" : "not there")) ;

	u_waitpid(pid,&cstat,0) ;

	msleep(500) ;

	fprintf(stdout,"\npid=%u after sleep waited for\n",pid) ;

	rs1 = u_kill(pid,0) ;
	fprintf(stdout,"u_kill() pid=%u rs1=%d\n",
		(uint) pid,rs1) ;

	rs1 = u_getpgid(pid) ;
	fprintf(stdout,"u_getpgid() pid=%u rs1=%d\n",
		(uint) pid,rs1) ;

	f = isproc(pid) ;
	fprintf(stdout,"isproc() pid=%u is %s\n",
		(uint) pid,((f) ? "there" : "not there")) ;

ret1:
	fclose(stdout) ;

ret0:

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

	return 0 ;

/* bad stuff */
badargval:
	fprintf(stdout,"invalid PID specified\n") ;

	goto ret1 ;

}
/* end subroutine (main) */



