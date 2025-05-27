/* maininfo SUPPORT */
/* lang=C++20 */

/* version %I% last-modified %G% */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* non-switchable debug print-outs */
#define	CF_DEBUGN	0		/* special debugging */
#define	CF_PROGINFO	0		/* use 'maininfo_xxx()' */
#define	CF_SIGHAND	1		/* install csignalandlers */
#define	CF_SIGALTSTACK	0		/* do *not* define */

/* revision history:

	= 2001-11-01, David A�D� Morano
	This subroutine was written for use as a front-end for Korn
	Shell (KSH) commands that are compiled as stand-alone
	programs.

*/

/* Copyright � 2001 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	This is the front-end to make the various SHELL (KSH)
	built-in commands into stand-alone programs.

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<climits>
#include	<cstdlib>
#include	<usystem.h>
#include	<vecstr.h>
#include	<upt.h>
#include	<localmisc.h>

#include	"maininfo.h"


/* local defines */


/* external subroutines */

extern int	snwcpy(char *,int,cchar *,int) ;
extern int	sncpy2(char *,int,cchar *,cchar *) ;
extern int	sncpy2w(char *,int,cchar *,cchar *,int) ;
extern int	sncpylc(char *,int,cchar *) ;
extern int	sncpyuc(char *,int,cchar *) ;
extern int	sfbasename(cchar *,int,cchar **) ;
extern int	bufprintf(char *,int,cchar *,...) ;
extern int	haslc(cchar *,int) ;
extern int	hasuc(cchar *,int) ;
extern int	isNotPresent(int) ;

#if	CF_DEBUGS
extern int	debugprintf(cchar *,...) ;
extern int	strlinelen(cchar *,int,int) ;
#endif

#if	CF_DEBUGN
extern int	nprintf(cchar *,cchar *,...) ;
#endif

extern cchar	*getourenv(cchar **,cchar *) ;

extern char	*strnrchr(cchar *,int,int) ;


/* external variables */


/* local structures */

typedef int (*thrsub)(void *) ;


/* forward references */

static int	maininfo_utiler(MAININFO *) ;


/* local variables */


/* exported variables */


/* exported subroutines */

int maininfo_start(MAININFO *mip,int argc,mainv argv) {
	sigset_t	ss ;
	cint		sig = SIGTIMEOUT ;
	int		rs ;
	cchar		*argz = NULL ;

	memset(mip,0,sizeof(MAININFO)) ;

	if ((argc > 0) && (argv != NULL)) argz = argv[0] ;

#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
	if (argz == NULL) argz = getexecname() ;
#endif

	uc_sigsetempty(&ss) ;
	uc_sigsetadd(&ss,sig) ;
	if ((rs = pt_sigmask(SIG_BLOCK,&ss,&mip->savemask)) >= 0) {
	    if ((rs = vecstr_start(&mip->stores,2,0)) >= 0) {
	        int	cl ;
	        cchar	*cp ;

	        if ((cl = sfbasename(argz,-1,&cp)) > 0) {
	            cchar	**vpp = &mip->progname ;
	            if (cp[0] == '-') {
	                mip->f.progdash = TRUE ;
	                cp += 1 ;
	                cl -= 1 ;
	            }
	            if (cl > 0) {
	                cchar	*tp ;
	                if ((tp = strnrchr(cp,cl,'.')) != NULL) {
	                    cl = (tp-cp) ;
	                }
	            }
	            if (cl > 0) {
	                rs = maininfo_setentry(mip,vpp,cp,cl) ;
	            } else {
	                rs = SR_DOM ;
	            }
	        } else {
	            rs = SR_DOM ;
	        }

	        if (rs < 0)
	            vecstr_finish(&mip->stores) ;
	    } /* end if (vecstr_start) */
	} /* end if (pt_sigmask) */

	return rs ;
}
/* end subroutine (maininfo_start) */

int maininfo_finish(MAININFO *mip) {
	int		rs = SR_OK ;
	int		rs1 ;

	if (mip == NULL) return SR_FAULT ;

	rs1 = vecstr_finish(&mip->stores) ;
	if (rs >= 0) rs = rs1 ;

	rs1 = pt_sigmask(SIG_SETMASK,&mip->savemask,NULL) ;
	if (rs >= 0) rs = rs1 ;

	return rs ;
}
/* end subroutine (maininfo_finish) */

int maininfo_setentry(MAININFO *mip,cchar **epp,cchar *vp,int vl) {
	int		rs = SR_OK ;
	int		oi = -1 ;
	int		len = 0 ;

	if (mip == NULL) return SR_FAULT ;
	if (epp == NULL) return SR_INVALID ;

	if (*epp != NULL) {
	    oi = vecstr_findaddr(&mip->stores,*epp) ;
	}
	if (vp != NULL) {
	    len = strnlen(vp,vl) ;
	    rs = vecstr_store(&mip->stores,vp,len,epp) ;
	} else {
	    *epp = NULL ;
	}
	if ((rs >= 0) && (oi >= 0)) {
	    vecstr_del(&mip->stores,oi) ;
	}

	return (rs >= 0) ? len : rs ;
}
/* end subroutine (maininfo_setentry) */

#if	CF_SIGALTSTACK
int maininfo_sigbegin(MAININFO *mip,maininfohand_t sh,cint *sigcatches) {
	size_t		ms ;
	cint	ps = getpagesize() ;
	cint	ss = (2*SIGSTKSZ) ;
	cint	mp = (PROT_READ|PROT_WRITE) ;
	cint	mf = (MAP_PRIVATE|MAP_NORESERVE|MAP_ANON) ;
	int		rs ;
	int		fd = -1 ;
	void		*md ;
	ms = iceil(ss,ps) ;
	if ((rs = u_mmap(NULL,ms,mp,mf,fd,0L,&md)) >= 0) {
	    mip->mdata = md ;
	    mip->msize = ms ;
	    mip->astack.ss_size = ms ;
	    mip->astack.ss_sp = md ;
	    mip->astack.ss_flags = 0 ;
	    if ((rs = u_sigaltstack(&mip->astack,NULL)) >= 0) {
	        rs = sighand_start(&mip->sh,NULL,NULL,sigcatches,sh) ;
	        if (rs < 0) {
	            mip->astack.ss_flags = SS_DISABLE ;
	            u_sigaltstack(&mip->astack,NULL) ;
	        }
	    } /* end if (u_sigaltstack) */
	    if (rs < 0) {
	        u_munmap(mip->mdata,mip->msize) ;
	        mip->mdata = NULL ;
	    }
	} /* end if (mmap) */
#if	CF_DEBUGN
	nprintf(NDF,"maininfo_sigbegin: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (maininfo_sigbegin) */
#else /* CF_SIGALTSTACK */
int maininfo_sigbegin(MAININFO *mip,maininfohand_t sh,cint *sigcatches) {
	int		rs = SR_OK ;
#if	CF_SIGHAND
	rs = sighand_start(&mip->sh,NULL,NULL,sigcatches,sh) ;
#endif
#if	CF_DEBUGN
	nprintf(NDF,"maininfo_sigbegin: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (maininfo_sigbegin) */
#endif /* CF_SIGALTSTACK */

int maininfo_sigend(MAININFO *mip) {
	int		rs = SR_OK ;
	int		rs1 ;

#if	CF_SIGHAND
	rs1 = sighand_finish(&mip->sh) ;
	if (rs >= 0) rs = rs1 ;
#endif

#if	CF_SIGALTSTACK
	mip->astack.ss_flags = SS_DISABLE ;
	rs1 = u_sigaltstack(&mip->astack,NULL) ;
	if (rs >= 0) rs = rs1 ;

	if (mip->mdata != NULL) {
	    rs1 = u_munmap(mip->mdata,mip->msize) ;
	    if (rs >= 0) rs = rs1 ;
	    mip->mdata = NULL ;
	    mip->msize = 0 ;
	}
#endif /* CF_SIGALTSTACK */

	return rs ;
}
/* end subroutine (maininfo_sigend) */

int maininfo_utilbegin(MAININFO *op,int f_run) {
	pthread_t	tid ;
	thrsub		w = (thrsub) maininfo_utiler ;
	int		rs = SR_OK ;

	if (f_run) {
	    if ((rs = uptcreate(&tid,NULL,w,op)) >= 0) {
	        op->tid = tid ;
	        op->f.utilout = TRUE ;
	    }
	} /* end if (run) */

	return rs ;
}
/* end subroutine (maininfo_utilbegin) */

int maininfo_utilend(MAININFO *op) {
	int		rs = SR_OK ;

	if (op->f.utilout) {
	    int		trs = SR_OK ;
	    op->f.utilout = FALSE ;
	    if ((rs = uptjoin(op->tid,&trs)) >= 0) {
	        rs = trs ;
	    }
	}

	return rs ;
}
/* end subroutine (maininfo_utilend) */

int maininfo_srchname(MAININFO *mip,cchar **rpp) {
	int		rs = SR_OK ;
	cchar		*srch = mip->progname ;
	if (rpp == NULL) return SR_FAULT ;
	*rpp = srch ;
	if (hasuc(srch,-1)) {
	    cint	slen = MAXNAMELEN ;
	    char	sbuf[MAXNAMELEN+1] ;
	    if ((rs = sncpylc(sbuf,slen,srch)) >= 0) {
	        rs = maininfo_setentry(mip,rpp,sbuf,rs) ;
	    }
	} else {
	    rs = strlen(srch) ;
	}
	return rs ;
}
/* end subroutine (maininfo_srchname) */


/* private subroutines */

static int maininfo_utiler(MAININFO *mip) {
	cint	of = (O_WRONLY|O_APPEND) ;
	int		rs = SR_OK ;
	int		rs1 ;
	cchar		*fn = "here.txt" ;

	if ((rs = u_open(fn,of,0664)) >= 0) {
	    cint	wlen = LINEBUFLEN ;
	    cint	fd = rs ;
	    cchar	*fmt = "hello world!\n" ;
	    char	wbuf[LINEBUFLEN+1] ;
	    if ((rs = bufprintf(wbuf,wlen,fmt)) >= 0) {
	        rs = u_write(fd,wbuf,rs) ;
	    }
	    rs1 = u_close(fd) ;
	    if (rs >= 0) rs = rs1 ;
	} else if (isNotPresent(rs)) {
	    rs = SR_OK ;
	} /* end if (open) */

	mip->f_done = TRUE ;
	return rs ;
}
/* end subroutine (maininfo_utiler) */


