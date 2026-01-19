/* main SUPPORT (testspawner) */
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
	$ testspawner.x <program> [<arg(s)>]

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
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
#include	"spawner.h"


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
static int	debugexit(cchar *,int) ;
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
	SPAWNER		s ;
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
		ENVHELP		hh ;
		int		size = ((argc+1) * sizeof(cchar **)) ;
		cchar	**defenvv = NULL ;
		cchar	*pfname = argv[1] ;
		cchar	*tp ;
		char		pbuf[MAXPATHLEN+1] ;
		void		*p ;
#if	CF_DEFENVV
		defenvv = envv ;
#endif
		pn = argv[0] ;
		if ((tp = strrchr(pn,'.')) != NULL) {
		    strnwcpy(pbuf,MAXPATHLEN,pn,(tp-pn)) ;
		    pn = pbuf ;
		}
		if ((rs = envhelp_start(&hh,envbads,defenvv)) >= 0) {
		int	i ;
		cchar	**ev ;
		cchar	*kp ;
		for (i = 0 ; envgoods[i] != NULL ; i += 1) {
		    kp = envgoods[i] ;
		    if (envhelp_present(&hh,kp,-1,NULL) == SR_NOTFOUND) {
		        if ((tp = getourenv(envv,kp)) != NULL) {
			    rs = envhelp_envset(&hh,kp,tp,-1) ;
		        }
		    }
		    if (rs < 0) break ;
		} /* end for */
		if (rs >= 0) {
		if ((rs = uc_malloc(size,&p)) >= 0) {
		    int		zl = -1 ;
		    int		ai ;
		    cchar	**av = (cchar **) p ;
		    cchar	*zp = argv[2] ;
		    char	argz[MAXNAMELEN+1] ;
		    if ((argc <= 2) || (zp[0] == '\0') || (zp[0] == '-')) {
			if ((zl = sfbasename(pfname,-1,&zp)) > 0) {
			    strnwcpy(argz,MAXNAMELEN,zp,zl) ;
			    zp = argz ;
			}
		    }
		    av[0] = zp ;
		    for (ai = 1 ; ai < argc ; ai += 1) {
			av[ai] = argv[ai+3] ;
		    }
		    av[ai] = NULL ;

	if ((rs = envhelp_getvec(&hh,&ev)) >= 0) {
	    int	pipes[2] ;
	    int	fd = -1 ;
	    if ((rs = uc_piper(pipes,3)) >= 0) {
	        int	wfd = pipes[0] ;
	        fd = pipes[1] ;
	        if ((rs = spawner_start(&s,pfname,av,ev)) >= 0) {
		    int	i ;
	            spawner_sigignores(&s) ;
	            spawner_setsid(&s) ;
	            for (i = 0 ; i < 3 ; i += 1)
	                spawner_fdclose(&s,i) ;
	            spawner_fdnull(&s,O_RDONLY) ;
	            spawner_fddup(&s,wfd) ;
	            if ((rs = spawner_run(&s)) >= 0) {
	                pid_t	pid = rs ;
	                int	cs = 0 ;

#if	CF_DEBUGS
	                debugprintf("main: child pid=%d\n",pid) ;
#endif /* CF_DEBUGS */

	                u_close(wfd) ;
	                wfd = -1 ;

#if	CF_DEBUGS
			{
			    int fs ;
			    sleep(1) ;
			    fs = uc_fsize(fd) ;
	                    debugprintf("main: fsize=%u\n",fs) ;
			}
#endif /* CF_DEBUGS */

	                rs = uc_copy(fd,1,-1) ;
	                u_close(fd) ;
	                fd = -1 ;

#if	CF_DEBUGS
	                debugprintf("main: uc_copy() rs=%d\n",rs) ;
#endif /* CF_DEBUGS */

	                rs1 = spawner_wait(&s,&cs,0) ;
	                if (rs >= 0) rs = rs1 ;

#if	CF_DEBUGS
	                debugprintf("main: wait() rs=%d cs=%d\n",rs,cs) ;
			debugexit(pn,cs) ;
#endif /* CF_DEBUGS */

			proglog(pn,efp,cs) ;

	            } /* end if */

	            spawner_finish(&s) ;
	        } /* end if (open) */
	        if ((rs < 0) && (wfd >= 0)) u_close(wfd) ;
	        if ((rs < 0) && (fd >= 0)) {
	            u_close(fd) ;
	            fd = -1 ;
	        }
	    } /* end if (piper) */
	} /* end block */

		    uc_free(av) ;
		} /* end if (memory-allocation) */
		} /* end if */
		    envhelp_finish(&hh) ;
		} /* end if (envhelp) */
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
static int debugexit(cchar *pn,int cs)
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


