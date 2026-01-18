/* main SUPPORT (testspawnproc) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#define	CF_DEBUG	0		/* run-time debugging */
#define	CF_DEBUGS	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */
#define	CF_DEFENVV	1		/* establish a default environment */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Synopsis:
	$ testspawnproc.x <program> [<arg(s)>]

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstring>
#include	<usystem.h>
#include	<bfile.h>
#include	<envhelp.h>
#include	<strx.h>
#include	<localmisc.h>

#include	"defs.h"
#include	"config.h"
#include	"spawnproc.h"


#ifndef	VARLOCAL
#define	VARLOCAL	"LOCAL"
#endif

#ifndef	VARDEBUGFNAME
#define	VARDEBUGFNAME	"TESTSPAWNER_DEBUGFILE"
#endif

#ifndef	MKCHAR
#define	MKCHAR(ch)	((ch) & UCHAR_MAX)
#endif


#if	CF_DEBUGS
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugprinthex(cchar *,int,cchar *,int) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
static int	debugexit(int) ;
#endif /* CF_DEBUGS */


/* forward references */

static int proglog(cchar *,bfile *,int) ;


/* local variables */

static cchar	*envbads[] = {
	"_",
	"_A0",
	"_EF",
	"A__z",
	"RANDOM",
	"TERM",
	"TERMDEV",
	"TMOUT",
	"PWD",
	NULL
} ;

static cchar	*envgoods[] = {
	"PATH",
	"UNIQUE",
	"TERM",
	NULL
} ;


/* exported subroutines */


int main(int argc,cchar **argv,cchar **envv)
{
	bfile		efile, *efp = &efile ;

#if	CF_DEBUGS && CF_DEBUGMALL
	uint		mo_start = 0 ;
#endif

	int		rs ;
	int		rs1 ;
	cchar	*pn ;
	cchar	*efname = NULL ;
	cchar	*cp ;

#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

#if	CF_DEBUGS && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	if ((efname == NULL) || (efname[0] == '-')) efname = BFILE_STDERR ;

	if ((rs = bopen(efp,efname,"wct",0666)) >= 0) {
	    if ((argv != NULL) && (argc > 1) && (argv[1][0] != '\0')) {
		SPAWNPROC	ps ;
		int		i ;
		cchar		*pfn = argv[1] ;
		cchar		**av = (argv+1) ;
		memset(&ps,0,sizeof(SPAWNPROC)) ;
	            ps.opts |= SPAWNPROC_OSETPGRP ;
	            for (i = 0 ; i < 3 ; i += 1) {
			if (i != 2) {
			    ps.fd[i] = FD_STDOUT ;
	                    ps.disp[i] = SPAWNPROC_DDUP ;
			} else {
	                    ps.disp[i] = SPAWNPROC_DINHERIT ;
			}
	            } /* end for */

	            if ((rs = spawnproc(&ps,pfn,av,envv)) >= 0) {
			const pid_t	pid = rs ;
			int		cs ;
			rs = u_waitpid(pid,&cs,0) ;
		    }

#if	CF_DEBUGS
	debugprintf("main: spawnproc() rs=%d\n",rs) ;
#endif /* CF_DEBUGS */

	    } /* end if (non-zero arguments) */
	    bclose(efp) ;
	} /* end if (standard-error) */

#if	CF_DEBUGS
	debugprintf("main: exiting rs=%d\n",rs) ;
#endif /* CF_DEBUGS */

#if	CF_DEBUGS && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


/* local subroutines */


static int proglog(cchar *pn,bfile *efp,int cs)
{
	int		rs = SR_OK ;

	    if (WIFEXITED(cs)) {
		int	ex = WEXITSTATUS(cs) ;
		bprintf(efp,"%s: program exited normally ex=%u\n",pn,ex) ;
	    } else if (WIFSIGNALED(cs)) {
		int	sig = WTERMSIG(cs) ;
		cchar	*ss ;
		char		sigbuf[20+1] ;
		if ((ss = strabbrsig(sig)) == NULL) {
		     ctdeci(sigbuf,20,sig) ;
		     ss = sigbuf ;
		}
		bprintf(efp,"%s: program exited w/ sig=%s\n",pn,ss) ;
	    } else {
		bprintf(efp,"%s: program exited weirdly cs=\\x%08x\n",pn,cs) ;
	    }

	return rs ;
}
/* end subroutine (proglog) */


#if	CF_DEBUGS
static int debugexit(int cs)
{
	int	rs = SR_OK ;
	    if (WIFEXITED(cs)) {
		int	ex = WEXITSTATUS(cs) ;
		debugprintf("main: program exited normally ex=%u\n",ex) ;
	    } else if (WIFSIGNALED(cs)) {
		int	sig = WTERMSIG(cs) ;
		cchar	*ss ;
		char		sigbuf[20+1] ;
		if ((ss = strabbrsig(sig)) == NULL) {
		     ctdeci(sigbuf,20,sig) ;
		     ss = sigbuf ;
		}
		debugprintf("main: program exited w/ sig=%s\n",ss) ;
	    } else {
		debugprintf("main: program exited weirdly cs=\\x%08x\n",cs) ;
	    }
	return rs ;
}
/* end subroutine (debugexit) */
#endif /* CF_DEBUGS */


