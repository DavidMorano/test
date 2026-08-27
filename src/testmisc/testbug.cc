/* testbug SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* generic short program front-end */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	1		/* non-switchable */
#define	CF_DEBUG	1		/* switchable debug print-outs */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */
#define	CF_DEBUGENV	0		/* debug environment */
#define	CF_DEBUGN	1
#define	CF_ALWAYS	1		/* always update the target? */
#define	CF_LOCSETENT	1		/* compile |locinfo_setentry()| */
#define	CF_TESTSLEEP	0		/* insert sleep for testing */
#define	CF_WRFILE	0		/* compile |wrfile()| */

/* revision history:

	= 2004-05-14, David A­D­ Morano
	The program was written from scratch to do what the previous
	program by the same name did.  It used pieces from other
	(similar in some ways) programs.  It is linted out and
	should be very clean -- we depend on this everyday to do
	what we need.  Pieces not used in their full like where
	they originally were, are sort of hacked up to minimal code.
	Try not to get your knickers in a bunch over that.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testbug

	Description:
	This is the main subroutine for MAKESAFE. This was a fairly
	generic subroutine adpapted for this program.  Note that
	parallel processing is enabled by default.  If you do not
	want parallel processing for some reason use the '-o'
	invocation option to set the maximum parallelism to '1'.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */

#if	defined(SFIO) && (SFIO > 0)
#define	CF_SFIO	1
#else
#define	CF_SFIO	0
#endif

#if	(defined(KSHBUILTIN) && (KSHBUILTIN > 0))
#include	<shell.h>
#endif

#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdarg>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<uclibmem.h>
#include	<mktmp.h>
#include	<ascii.h>
#include	<bits.h>
#include	<keyopt.h>
#include	<tmtime.h>
#include	<bfile.h>
#include	<filer.h>
#include	<vecstr.h>
#include	<vecobj.h>
#include	<sbuf.h>
#include	<ids.h>
#include	<ptm.h>
#include	<psem.h>
#include	<fsi.h>
#include	<fsdir.h>
#include	<dirlist.h>
#include	<cachectime>
#include	<upt.h>
#include	<spawnproc.h>
#include	<opentmp.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"shio.h"
#include	"kshlib.h"
#include	"testbug.h"
#include	"defs.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX((2 * MAXPATHLEN),2048)
#endif

#define	ARGBUFLEN	(MAXPATHLEN + 3)
#define	FBUFLEN		(2*LINEBUFLEN)

#define	NDEPS		100		/* default values */

#define	LOCINFO		struct locinfo
#define	LOCINFO_FL	struct locinfo_flags
#define	LOCINFO_CUR	struct locinfo_cur

#define	CPPERR		struct cpperr

#define	LSTATE		struct lstate

#define	NDF		"testbug.deb"


/* external subroutines */

extern int	printhelp(void *,cchar *,cchar *,cchar *) noex ;
extern int	proginfo_setpiv(PROGINFO *,cchar *,const pivars *) noex ;

#if	CF_DEBUGS || CF_DEBUG
extern int	debugopen(cchar *) noex ;
extern int	debugprintf(cchar *,...) noex ;
extern int	debugprinthex(cchar *,int,cchar *,int) noex ;
extern int	debugclose() noex ;
extern int	strlinelen(cchar *,int,int) noex ;
#endif

#if	CF_DEBUGN
extern int	nprintf(cchar *,cchar *,...) noex ;
#endif


/* external variables */

extern char	**environ ;


/* local structures */

struct locinfo_cur {
	dirlist_cur	c ;
} ;

struct locinfo_flags {
	uint		stores:1 ;
	uint		maint:1 ;	/* user requested maintenance */
	uint		tmpmaint:1 ;	/* thread spawned */
	uint		id:1 ;
	uint		incs:1 ;
	uint		cache:1 ;
	uint		dirs:1 ;
	uint		mtdb:1 ;
	uint		zero:1 ;
	uint		remote:1 ;
	uint		nochange:1 ;
	uint		print:1 ;
	uint		optpar:1 ;
	uint		optdebug:1 ;
} ;

struct locinfo {
	vecstr		stores ;
	LOCINFO_FL	have, f, changed, finval ;
	LOCINFO_FL	open ;
	IDS		id ;
	dirlist		incs ;
	CACHETIME	mtdb ;
	PTM		efm ;
	PTM		ofm ;
	PROGINFO	*pip ;
	void		*ofp ;
	cchar	*jobdname ;		/* tmp-user directory */
	cchar	*suffix_from ;
	cchar	*suffix_to ;
	cchar	*prog_cpp ;
	pthread_t	tid ;
	uid_t		uid_pr ;
	gid_t		gid_pr ;
	int		ncpu ;
	int		npar ;
	int		to_tmpfiles ;
	int		to_delete ;
	int		c_processed ;
	int		c_updated ;
} ;

struct lstate {
	int		f_continue ;
} ;

struct cpperr {
	cchar	*fname ;
	cchar	*ifname ;
	int		line ;
} ;


/* forward references */

local int	usage(PROGINFO *) noex ;

local int	testbugger(PROGINFO *) noex ;
local int	test1(PROGINFO *) noex ;

local int	procopts(PROGINFO *,keyopt *) noex ;
local int	procsubprog(PROGINFO *,cchar *) noex ;
local int	proctouchfile(PROGINFO *,cchar *) noex ;
local int	proceprintf(PROGINFO *,cchar *,...) noex ;

local int proclines(PROGINFO *,int) noex ;
local int procline(PROGINFO *,LSTATE *,cchar *,int) noex ;
local int procerr(PROGINFO *,int) noex ;
local int procerrline(PROGINFO *,cchar *,int) noex ;

local int	procout_begin(PROGINFO *,void *,cchar *) noex ;
local int	procout_end(PROGINFO *) noex ;
local int	procout_printf(PROGINFO *,cchar *,...) noex ;

local int	locinfo_start(LOCINFO *,PROGINFO *) noex ;
local int	locinfo_finish(LOCINFO *) noex ;
local int	locinfo_jobdname(LOCINFO *) noex ;
local int	locinfo_tmpcheck(LOCINFO *) noex ;
local int	locinfo_tmpmaint(LOCINFO *) noex ;
local int	locinfo_tmpdone(LOCINFO *) noex ;
local int	locinfo_fchmodown(LOCINFO *,int,ustat *,mode_t) noex ;
local int	locinfo_loadprids(LOCINFO *) noex ;
local int	locinfo_alreadybegin(LOCINFO *) noex ;
local int	locinfo_alreadyend(LOCINFO *) noex ;
local int	locinfo_alreadystat(LOCINFO *) noex ;
local int	locinfo_incdirs(LOCINFO *) noex ;
local int	locinfo_incadds(LOCINFO *,cchar *,int) noex ;
local int	locinfo_alreadylookup(LOCINFO *,cchar *,int,time_t *) noex ;

local int	locinfo_incbegin(LOCINFO *,LOCINFO_CUR *) noex ;
local int	locinfo_incenum(LOCINFO *,LOCINFO_CUR *,char *,int) noex ;
local int	locinfo_incend(LOCINFO *,LOCINFO_CUR *) noex ;
local int	locinfo_ncpu(LOCINFO *) noex ;

#if	CF_LOCSETENT
local int	locinfo_setentry(LOCINFO *,cchar **,cchar *,int) noex ;
#endif

local int cpperr_start(CPPERR *,int,cchar *,int) noex ;
local int cpperr_ifname(CPPERR *,cchar *,int) noex ;
local int cpperr_finish(CPPERR *) noex ;

#if	CF_DEBUG && CF_DEBUGENV
local int debugdumpenv(cchar **) noex ;
#endif

#if	CF_WRFILE
local int	wrfile(cchar *,int) noex ;
#endif


/* local variables */

constexpr pivars	initvars = {
	VARPROGRAMROOT1,
	VARPROGRAMROOT2,
	VARPROGRAMROOT3,
	PROGRAMROOT,
	VARPRLOCAL
} ;

enum argopts {
	argopt_root,
	argopt_version,
	argopt_verbose,
	argopt_tmpdir,
	argopt_help,
	argopt_sn,
	argopt_af,
	argopt_ef,
	argopt_of,
	argopt_cpp,
	argopt_jd,
	argopt_overlast
} ;

constexpr cpcchar	argopts[] = {
	"ROOT",
	"VERSION",
	"VERBOSE",
	"TMPDIR",
	"HELP",
	"sn",
	"af",
	"ef",
	"of",
	"cpp",
	"jd",
	nullptr
} ;

constexpr mapex		mapexs[] = {
	{ SR_NOENT, EX_NOUSER },
	{ SR_AGAIN, EX_TEMPFAIL },
	{ SR_DEADLK, EX_TEMPFAIL },
	{ SR_NOLCK, EX_TEMPFAIL },
	{ SR_TXTBSY, EX_TEMPFAIL },
	{ SR_ACCESS, EX_NOPERM },
	{ SR_REMOTE, EX_PROTOCOL },
	{ SR_NOSPC, EX_TEMPFAIL },
	{ SR_INTR, EX_INTR },
	{ SR_EXIT, EX_TERM },
	{ 0, 0 }
} ;

enum aknames {
	akname_cache,
	akname_cpp,
	akname_par,
	akname_debug,
	akname_maint,
	akname_overlast
} ;

constexpr cpcchar	aknames[] = {
	"cache",
	"cpp",
	"parallel",
	"debug",
	"maint",
	nullptr
} ;

constexpr cpcchar	progcpps[] = {
	"/usr/ccs/lib/cpp",
	"/usr/lib/cpp",
	"/usr/add-on/ncmp/bin/cpp",
	nullptr
} ;

constexpr char		errsub1[] = ", line " ;
constexpr char		errsub2[] = ": Cannot find include file " ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
	PROGINFO	pi, *pip = &pi ;
	LOCINFO		li, *lip = &li ;
	ARGINFO		ainfo ;
	bits		pargs ;
	keyopt		akopts ;
	shio		errfile ;

#if	(CF_DEBUGS || CF_DEBUG) && CF_DEBUGMALL
	uint		mo_start = 0 ;
#endif

	int		argr, argl, aol, akl, avl, kwi ;
	int		ai, ai_max, ai_pos ;
	int		rs, rs1 ;
	int		ex = EX_INFO ;
	int		f_optminus, f_optplus, f_optequal ;
	int		f_usage = false ;
	int		f_help = false ;
	int		f_version = false ;

	cchar	*argp, *aop, *akp, *avp ;
	cchar	*argval = nullptr ;
	cchar	*pr = nullptr ;
	cchar	*sn = nullptr ;
	cchar	*afname = nullptr ;
	cchar	*efname = nullptr ;
	cchar	*ofname = nullptr ;
	cchar	*touchfname = nullptr ;
	cchar	*progcpp = nullptr ;
	cchar	*cp ;

#if	CF_DEBUGN
	nprintf(NDF,"testbug: ent\n") ;
#endif

#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

#if	(CF_DEBUGS || CF_DEBUG) && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	rs = proginfo_start(pip,envv,argv[0],VERSION) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badprogstart ;
	}

	if ((cp = getenv(VARBANNER)) == nullptr) {
	    cp = BANNER ;
	}
	rs = proginfo_setbanner(pip,cp) ;

/* early things to initialize */

	pip->verboselevel = 1 ;

	pip->lip = &li ;
	if (rs >= 0) rs = locinfo_start(lip,pip) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badlocstart ;
	}

/* process program arguments */

	if (rs >= 0) rs = bits_start(&pargs,1) ;
	if (rs < 0) goto badpargs ;

	rs = keyopt_start(&akopts) ;
	pip->open.akopts = (rs >= 0) ;

	ai_max = 0 ;
	ai_pos = 0 ;
	argr = argc ;
	for (ai = 0 ; (ai < argc) && (argv[ai] != nullptr) ; ai += 1) {
	    if (rs < 0) break ;
	    argr -= 1 ;
	    if (ai == 0) continue ;

	    argp = argv[ai] ;
	    argl = strlen(argp) ;

	    f_optminus = (*argp == '-') ;
	    f_optplus = (*argp == '+') ;
	    if ((argl > 1) && (f_optminus || f_optplus)) {
	        cint	ach = MKCHAR(argp[1]) ;

	        if (isdigitlatin(ach)) {

	            argval = (argp + 1) ;

	        } else if (ach == '-') {

	            ai_pos = ai ;
	            break ;

	        } else {

	            aop = argp + 1 ;
	            akp = aop ;
	            aol = argl - 1 ;
	            f_optequal = false ;
	            if ((avp = strchr(aop,'=')) != nullptr) {
	                f_optequal = true ;
	                akl = avp - aop ;
	                avp += 1 ;
	                avl = aop + argl - 1 - avp ;
	                aol = akl ;
	            } else {
	                avp = nullptr ;
	                avl = 0 ;
	                akl = aol ;
	            }

	            if ((kwi = matostr(argopts,2,akp,akl)) >= 0) {

	                switch (kwi) {

/* program root */
	                case argopt_root:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            pr = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                pr = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;

/* version */
	                case argopt_version:
	                    f_version = true ;
	                    if (f_optequal)
	                        rs = SR_INVALID ;
	                    break ;

/* verbose */
	                case argopt_verbose:
	                    pip->verboselevel = 2 ;
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl) {
	                            rs = optvalue(avp,avl) ;
	                            pip->verboselevel = rs ;
	                        }
	                    }
	                    break ;

/* temporary directory */
	                case argopt_tmpdir:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            pip->tmpdname = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                pip->tmpdname = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;

/* help */
	                case argopt_help:
	                    f_help = true ;
	                    break ;

/* program search-name */
	                case argopt_sn:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            sn = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                sn = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;

/* argument file */
	                case argopt_af:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            afname = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                afname = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;

/* error file name */
	                case argopt_ef:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            efname = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                efname = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;

/* output file */
	                case argopt_of:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            ofname = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                ofname = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;

/* CPP program */
	                case argopt_cpp:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            progcpp = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                progcpp = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;
/* job directory */
	                case argopt_jd:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            lip->jobdname = avp ;
	                    } else {
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                lip->jobdname = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                    }
	                    break ;


/* default action and user specified help */
	                default:
	                    rs = SR_INVALID ;
	                    break ;

	                } /* end switch (key words) */

	            } else {

	                while (akl--) {
	                    cint	kc = MKCHAR(*akp) ;

	                    switch (kc) {

	                    case 'D':
	                        pip->debuglevel = 1 ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = optvalue(avp,avl) ;
	                                pip->debuglevel = rs ;
	                            }
	                        }
	                        break ;

	                    case 'I':
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl) {
	                                rs = locinfo_incadds(lip,argp,argl) ;
	                            }
	                        } else
	                            rs = SR_INVALID ;
	                        break ;

/* quiet */
	                    case 'Q':
	                        pip->fl.quiet = true ;
	                        break ;

	                    case 'R':
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                pr = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                        break ;

	                    case 'V':
	                        f_version = true ;
	                        break ;

/* options */
	                    case 'o':
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl) {
	                                rs = keyopt_loads(&akopts,argp,argl) ;
	                            }
	                        } else
	                            rs = SR_INVALID ;
	                        break ;

/* no-change */
	                    case 'n':
	                        lip->fl.nochange = true ;
	                        break ;

/* print something !! */
	                    case 'p':
	                        lip->fl.print = true ;
	                        break ;

	                    case 'r':
	                        lip->fl.remote = true ;
	                        break ;

/* touch file */
	                    case 't':
	                        if (argr > 0) {
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl)
	                                touchfname = argp ;
	                        } else
	                            rs = SR_INVALID ;
	                        break ;

/* verbose output */
	                    case 'v':
	                        pip->verboselevel = 2 ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = optvalue(avp,avl) ;
	                                pip->verboselevel = rs ;
	                            }
	                        }
	                        break ;

/* zero files (are OK) */
	                    case 'z':
	                        lip->fl.zero = true ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                lip->fl.zero = (rs > 0) ;
	                            }
	                        }
	                        break ;

	                    case '?':
	                        f_usage = true ;
	                        break ;

	                    default:
	                        rs = SR_INVALID ;
	                        break ;

	                    } /* end switch */
	                    akp += 1 ;

	                    if (rs < 0) break ;
	                } /* end while */

	            } /* end if (individual option key letters) */

	        } /* end if (digits or options) */

	    } else {

	        rs = bits_set(&pargs,ai) ;
	        ai_max = ai ;

	    } /* end if (key letter/word or positional) */

	    ai_pos = ai ;

	} /* end while (all command line argument processing) */

	if (efname == nullptr) efname = getenv(VAREFNAME) ;
	if (efname == nullptr) efname = getenv(VARERRORFNAME) ;
	if (efname == nullptr) efname = STDFNERR ;
	if ((rs1 = shio_open(&errfile,efname,"wca",0666)) >= 0) {
	    pip->efp = &errfile ;
	    pip->open.errfile = true ;
	    shio_control(&errfile,SHIO_CSETBUFLINE,true) ;
	} else if (! isNotPresent(rs1)) {
	    if (rs >= 0) rs = rs1 ;
	}

	if (rs < 0)
	    goto badarg ;

/* check arguments */

#if	CF_DEBUG
	if (DEBUGLEVEL(2)) {
	    int	pid = getpid() ;
	    debugprintf("main: debuglevel=%u\n",pip->debuglevel) ;
	    debugprintf("main: pid=%u\n",pid) ;
	}
#endif

	if (pip->debuglevel > 0) {
	    shio_printf(pip->efp,"%s: version %s\n",
	        pip->progname,VERSION) ;
	}

/* program root */

	if (rs >= 0) {
	    if ((rs = proginfo_setpiv(pip,pr,&initvars)) >= 0) {
	        rs = proginfo_setsearchname(pip,VARSEARCHNAME,sn) ;
	    }
	}

	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto retearly ;
	}

	if (pip->debuglevel > 0) {
	    shio_printf(pip->efp,"%s: pr=%s\n", pip->progname,pip->pr) ;
	    shio_printf(pip->efp,"%s: sn=%s\n", pip->progname,pip->searchname) ;
	} /* end if */

	if (f_usage)
	    usage(pip) ;

/* help */

	if (f_help)
	    printhelp(nullptr,pip->pr,pip->searchname,HELPFNAME) ;

	if (f_version || f_help || f_usage)
	    goto retearly ;


	ex = EX_OK ;

/* initialize */

	if ((rs >= 0) && (lip->npar == 0) && (argval != nullptr)) {
	    rs = optvalue(argval,-1) ;
	    pip->n = rs ;
	}

	if (afname == nullptr) afname = getenv(VARAFNAME) ;

	if (pip->tmpdname == nullptr) pip->tmpdname = getenv(VARTMPDNAME) ;
	if (pip->tmpdname == nullptr) pip->tmpdname = TMPDNAME ;

/* procopts */

	if (rs >= 0) {
	    if ((rs = procopts(pip,&akopts)) >= 0) {
	    	if ((rs = procsubprog(pip,progcpp)) >= 0) {
		    if ((rs = locinfo_jobdname(lip)) >= 0) {
			if ((rs = locinfo_tmpcheck(lip)) >= 0) {
	    		    rs = locinfo_incdirs(lip) ;
			}
		    }
		}
	    }
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(2)) {
	    keyopt	*kop = &akopts ;
	    keyopt_cur	cur ;
	    if ((rs = keyopt_curbegin(kop,&cur)) >= 0) {
	        while (rs >= 0) {
	            rs1 = keyopt_curenumkeys(kop,&cur,&cp) ;
	            debugprintf("main: akopt rs=%d\n",rs1) ;
	            if (rs1 < 0) break ;
	            debugprintf("main: akopt key=%s\n",cp) ;
	        } /* end while */
	        keyopt_curend(kop,&cur) ;
	    } /* end if (keyopt-cur) */
	}
#endif /* CF_DEBUG */

	if ((rs >= 0) && (lip->npar == 0)) {
	    rs = locinfo_ncpu(lip) ;
	    lip->npar = (rs+1) ; /* normally add one */
	}

	if (pip->debuglevel > 0) {
	    cchar	*pn = pip->progname ;
	    cchar	*fmt ;
	    fmt = "%s: cache mode=%u\n" ;
	    shio_printf(pip->efp,fmt,pn,lip->fl.cache) ;
	    fmt = "%s: allowed parallelism=%u\n" ;
	    shio_printf(pip->efp,fmt,pn,lip->npar) ;
	} /* end if */

/* check a few more things */

	if (pip->to_read <= 0) pip->to_read = TO_READ ;

/* find the CPP program (if we do not already have one) */

	if (pip->debuglevel > 0) {
	    shio_printf(pip->efp,"%s: CPP=%s\n",
	        pip->progname,lip->prog_cpp) ;
	}

/* continue */

	memset(&ainfo,0,sizeof(ARGINFO)) ;
	ainfo.argc = argc ;
	ainfo.ai = ai ;
	ainfo.ai_max = ai_max ;
	ainfo.ai_pos = ai_pos ;
	ainfo.argv = argv ;

	if (rs >= 0) {
	    shio	ofile ;
	    if ((rs = procout_begin(pip,&ofile,ofname)) >= 0) {

		switch (pip->n) {
		case 0:
		    rs = testbugger(pip) ;
		    break ;
		case 1:
		    rs = test1(pip) ;
		    break ;
		} /* end switch */

	        rs1 = procout_end(pip) ;
		if (rs >= 0) rs = rs1 ;
	    } else {
	        cchar	*pn = pip->progname ;
	        cchar	*fmt = "%s: output unavailable (%d)\n" ;
	        ex = EX_CANTCREAT ;
	        shio_printf(pip->efp,fmt,pn,rs) ;
	    } /* end if */
	} else if (ex == EX_OK) {
	    cchar	*pn = pip->progname ;
	    cchar	*fmt = "%s: invalid argument or configuration (%d)\n" ;
	    ex = EX_USAGE ;
	    shio_printf(pip->efp,fmt,pn,rs) ;
	    usage(pip) ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(2)) {
	    debugprintf("main: done rs=%d\n",rs) ;
	    debugprintf("main: processed=%d updated=%d\n",
	        lip->c_processed,lip->c_updated) ;
	}
#endif /* CF_DEBUG */

/* done */
	if (rs >= 0) {

#if	CF_DEBUG
	    if (DEBUGLEVEL(2))
	        debugprintf("main: good rs=%d processed=%d updated=%d\n",
	            rs,lip->c_processed,lip->c_updated) ;
#endif

	    if ((touchfname != nullptr) && (touchfname[0] != '\0')) {
	        rs = proctouchfile(pip,touchfname) ;
	        if (rs == SR_NOENT) ex = EX_CANTCREAT ;
	    } /* end if (touch-file) */

	} /* end if */

	if ((rs < 0) && (ex == EX_OK)) {
	    switch (rs) {
	    case SR_INVALID:
	        ex = EX_USAGE ;
	        if (! pip->fl.quiet) {
	            shio_printf(pip->efp,"%s: invalid query (%d)\n",
	                pip->progname,rs) ;
	        }
	        break ;
	    case SR_NOENT:
	        ex = EX_CANTCREAT ;
	        break ;
	    case SR_AGAIN:
	        ex = EX_TEMPFAIL ;
	        break ;
	    default:
	        ex = mapex(mapexs,rs) ;
	        break ;
	    } /* end switch */
	} /* end if */

/* we are out of here */
retearly:
	if ((pip->debuglevel > 0) || lip->fl.optdebug) {
	    cchar	*pn = pip->progname ;
	    if (lip->fl.optdebug) {
	        proginfo_pwd(pip) ;
	        shio_printf(pip->efp,"%s: dir=%s\n",pn,pip->pwd) ;
	    }
	    shio_printf(pip->efp,"%s: exiting ex=%u (%d)\n",pn,ex,rs) ;
	} /* end if */

#if	CF_DEBUG
	if (DEBUGLEVEL(1))
	    debugprintf("main: exiting ex=%u (%d)\n",ex,rs) ;
#endif

	if (pip->efp != nullptr) {
	    pip->open.errfile = false ;
	    shio_close(pip->efp) ;
	    pip->efp = nullptr ;
	}

	if (pip->open.akopts) {
	    pip->open.akopts = false ;
	    keyopt_finish(&akopts) ;
	}

	bits_finish(&pargs) ;

badpargs:
	locinfo_finish(lip) ;

badlocstart:
	proginfo_finish(pip) ;

badprogstart:

#if	(CF_DEBUGS || CF_DEBUG) && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

	return ex ;

/* bad things */
badarg:
	ex = EX_USAGE ;
	shio_printf(pip->efp,"%s: invalid argument specified (%d)\n",
	    pip->progname,rs) ;
	usage(pip) ;
	goto retearly ;

}
/* end subroutine (main) */


/* local subroutines */


/* print out (standard error) some short usage */
local int usage(PROGINFO *pip)
{
	int		rs = SR_NOTOPEN ;
	int		wlen = 0 ;
	cchar	*pn = pip->progname ;
	cchar	*fmt ;

	if (pip->efp != nullptr) {

	    fmt = "%s: USAGE> %s [<objfile(s)> ...] [[-I <incdir(s)>] ...]\n" ;
	    if (rs >= 0) rs = shio_printf(pip->efp,fmt,pn,pn) ;
	    wlen += rs ;

	    fmt = "%s:  [-t <target>] [-z]\n" ;
	    if (rs >= 0) rs = shio_printf(pip->efp,fmt,pn) ;
	    wlen += rs ;

	    fmt = "%s:  [-Q] [-D] [-v[=<n>]] [-V]\n" ;
	    if (rs >= 0) rs = shio_printf(pip->efp,fmt,pn) ;
	    wlen += rs ;

	} /* end if */

	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (usage) */

local int proceprintf(PROGINFO *pip,cchar *fmt,...) noex {
	va_list		ap ;
	LOCINFO		*lip = pip->lip ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		len = 0 ;
	if (pip->debuglevel > 0) {
	    va_begin(ap,fmt) ;
	    ptm *emp = &lip->efm ;
	    if ((rs = emp->lockbegin) >= 0) {
		{
	            rs = bvprintf(pip->efp,fmt,ap) ;
		    len = rs ;
		}
	        rs1 = emp->lockend ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (mutex) */
	    va_end(ap) ;
	} /* end if */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (proceprintf) */

local int procopts(PROGINFO *pip,keyopt *kop) noex {
	LOCINFO		*lip = pip->lip ;
	static cchar	*varp = getenv(VAROPTS) ;
	int		rs = SR_OK ;
	int		c = 0 ;
	cchar	*cp ;

	if (varp) {
	    rs = keyopt_loads(kop,varp,-1) ;
	}

	if (rs >= 0) {
	    keyopt_cur	cur ;
	    if ((rs = keyopt_curbegin(kop,&cur)) >= 0) {
	        int	ki ;
	        int	kl, vl ;
	        cchar	*kp, *vp ;

	        while ((kl = keyopt_curenumkeys(kop,&cur,&kp)) >= 0) {

	            if ((ki = matostr(aknames,2,kp,kl)) >= 0) {
	                vl = keyopt_fetch(kop,kp,nullptr,&vp) ;

	                switch (ki) {
	                case akname_cache:
	                    if (! lip->finval.cache) {
	                        lip->have.cache = true ;
	                        lip->fl.cache = true ;
	                        if (vl > 0) {
	                            rs = optbool(vp,vl) ;
	                            lip->fl.cache = (rs > 0) ;
	                        }
	                    }
	                    break ;
	                case akname_cpp:
	                    if ((vl > 0) && (lip->prog_cpp == nullptr)) {
	                        cchar	**vpp = &lip->prog_cpp ;
	                        rs = locinfo_setentry(lip,vpp,vp,vl) ;
	                    }
	                    break ;
	                case akname_par:
	                    if (! lip->finval.optpar) {
	                        lip->have.optpar = true ;
	                        if (vl > 0) {
	                            rs = optvalue(vp,vl) ;
	                            lip->npar = rs ;
	                        }
	                    }
	                    break ;
	                case akname_debug:
	                    if (! lip->finval.optdebug) {
	                        lip->have.optdebug = true ;
	                        lip->fl.optdebug = true ;
	                        if (vl > 0) {
	                            rs = optbool(vp,vl) ;
	                            lip->fl.optdebug = (rs > 0) ;
	                        }
	                    }
	                    break ;
	                case akname_maint:
	                    if (! lip->finval.maint) {
	                        lip->have.maint = true ;
	                        lip->fl.maint = true ;
				lip->fl.zero = true ;
	                        if (vl > 0) {
	                            rs = optbool(vp,vl) ;
	                            lip->fl.maint = (rs > 0) ;
	                        }
	                    }
	                    break ;
	                } /* end switch */
	                c += 1 ;
	            } /* end if (valid option) */

	            if (rs < 0) break ;
	        } /* end while (procopts) */

	        keyopt_curend(kop,&cur) ;
	    } /* end if (keyopt-cur) */
	} /* end if (ok) */

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main/procopts: ret rs=%d c=%u\n",rs,c) ;
#endif

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (procopts) */


local int testbugger(PROGINFO *pip)
{
	LOCINFO		*lip = pip->lip ;
	vecstr		args ;
	cmode		operms = 0664 ;
	int		rs ;
	int		cl ;
	int		opts ;
	int		oflags ;
	int		fd_out = -1 ;
	int		fd_err ;
	int		cstat ;
	cchar	**av ;
	cchar	*cp ;
	char		tmpfname[MAXPATHLEN + 1] ;
	char		outfname[MAXPATHLEN + 1] ;
	char		errfname[MAXPATHLEN + 1] ;

#if	CF_DEBUG
	if (DEBUGLEVEL(5))
	debugprintf("main/testbugger: ent\n") ;
#endif

	lip->prog_cpp = "/usr/bin/echo" ;

	errfname[0] = '\0' ;
	outfname[0] = '\0' ;
	opts = VECSTR_OCOMPACT ;
	rs = vecstr_start(&args,10,opts) ;
	if (rs < 0)
	    goto ret0 ;

/* get a basename for the zeroth program argument */

	cl = sfbasename(lip->prog_cpp,-1,&cp) ;

/* create the argument list for the CPP program */

	vecstr_add(&args,cp,cl) ;

	vecstr_add(&args,"--",-1) ;

	vecstr_add(&args,"hello world!",-1) ;

/* prepare STDERR for the program */

	mkpath2(tmpfname,lip->jobdname,"seXXXXXXXXXX") ;

	oflags = O_RDWR ;
	rs = opentmpfile(tmpfname,oflags,operms,errfname) ;
	fd_err = rs ;
	if (rs < 0)
	    goto ret1 ;

	if (errfname[0] != '\0') {
	    u_unlink(errfname) ;
	    errfname[0] = '\0' ;
	}

/* prepare STDOUT for the program */

	mkpath2(tmpfname,lip->jobdname,"soXXXXXXXXXX") ;

	oflags = O_RDWR ;
	rs = opentmpfile(tmpfname,oflags,operms,outfname) ;
	fd_out = rs ;
	if (rs < 0)
	    goto ret2 ;

/* start the program */

	if ((rs = vecstr_getvec(&args,&av)) >= 0) {
	SPAWNPROC	psa ;
#if	CF_DEBUG
	if (DEBUGLEVEL(5)) {
	    int	i ;
	    for (i = 0 ; av[i] != nullptr ; i += 1)
	        debugprintf("main/testbugger: arg%u=>%s<\n",i,av[i]) ;
	}
#endif
	memset(&psa,0,sizeof(SPAWNPROC)) ;
	psa.disp[0] = SPAWNPROC_Dnullptr ;
	psa.disp[1] = SPAWNPROC_DDUP ;
	psa.disp[2] = SPAWNPROC_DDUP ;
	psa.fd[1] = fd_out ;
	psa.fd[2] = fd_err ;
	if ((rs = spawnproc(&psa,lip->prog_cpp,av,pip->envv)) >= 0) {
	    const pid_t	pid = rs ;
	    int		rfd = fd_out ;
	    while (rs == 0) {
	        rs = u_waitpid(pid,&cstat,WUNTRACED) ;
	        if (rs == SR_INTR) rs = SR_OK ;
	    }
#if	CF_DEBUG
	    if (DEBUGLEVEL(5)) {
		USTAT	sb ;
	        debugprintf("main/testbugger: u_wait() rs=%d pid=%u\n",
			rs,pid) ;
		u_close(rfd) ;
		rfd = u_open(outfname,O_RDONLY,0666) ;
		u_fstat(rfd,&sb) ;
	        debugprintf("main/testbugger: fsize=%llu\n",sb.st_size) ;
	    }
#endif
	    if (rs >= 0) {
		if ((rs = u_rewind(rfd)) >= 0) {
	                if ((rs = proclines(pip,rfd)) >= 0) {
	                    rs = procerr(pip,fd_err) ;
	                }
		}
	    } /* end if (ok) */
	} /* end if spawnproc) */
	} /* end if (vecstr_getvec) */

/* done */
	u_close(fd_out) ;
	if (outfname[0] != '\0') {
	    u_unlink(outfname) ;
	    outfname[0] = '\0' ;
	}

ret2:
	u_close(fd_err) ;

ret1:
	vecstr_finish(&args) ;

	{
	    char	*p ;
	    p = outfname ;
	    if (p[0] != '\0') {
	        u_unlink(p) ;
	        p[0] = '\0' ;
	    }
	    p = errfname ;
	    if (p[0] != '\0') {
	        u_unlink(p) ;
	        p[0] = '\0' ;
	    }
	}

ret0:
	if ((pip->debuglevel > 0) && (rs < 0)) {
	    proceprintf(pip,"%s: testbugger (%d)\n",
	        pip->progname,rs) ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main/testbugger: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (testbugger) */


local int test1(PROGINFO *pip)
{
	LOCINFO		*lip = pip->lip ;
	vecstr		args ;
	cmode		operms = 0664 ;
	int		rs ;
	int		cl ;
	int		opts ;
	int		oflags ;
	int		fd_out = -1 ;
	int		fd_err ;
	int		cstat ;
	cchar	**av ;
	cchar	*cp ;
	char		tmpfname[MAXPATHLEN + 1] ;
	char		outfname[MAXPATHLEN + 1] ;
	char		errfname[MAXPATHLEN + 1] ;

#if	CF_DEBUG
	if (DEBUGLEVEL(5))
	debugprintf("main/test1: ent\n") ;
#endif

	lip->prog_cpp = "/usr/bin/echo" ;

	errfname[0] = '\0' ;
	outfname[0] = '\0' ;
	opts = VECSTR_OCOMPACT ;
	rs = vecstr_start(&args,10,opts) ;
	if (rs < 0)
	    goto ret0 ;

/* get a basename for the zeroth program argument */

	cl = sfbasename(lip->prog_cpp,-1,&cp) ;

/* create the argument list for the CPP program */

	vecstr_add(&args,cp,cl) ;

	vecstr_add(&args,"--",-1) ;

	vecstr_add(&args,"hello world!",-1) ;

/* prepare STDERR for the program */

	mkpath2(tmpfname,lip->jobdname,"seXXXXXXXXXX") ;

	oflags = O_RDWR ;
	rs = opentmpfile(tmpfname,oflags,operms,errfname) ;
	fd_err = rs ;
	if (rs < 0)
	    goto ret1 ;

	if (errfname[0] != '\0') {
	    u_unlink(errfname) ;
	    errfname[0] = '\0' ;
	}

/* prepare STDOUT for the program */

	mkpath2(tmpfname,lip->jobdname,"soXXXXXXXXXX") ;

	oflags = O_RDWR ;
	rs = opentmpfile(tmpfname,oflags,operms,outfname) ;
	fd_out = rs ;
	if (rs < 0)
	    goto ret2 ;

/* start the program */

	if ((rs = vecstr_getvec(&args,&av)) >= 0) {
	    int		rfd = fd_out ;
	    pid_t	pid = -1 ;

#if	CF_DEBUG
	if (DEBUGLEVEL(5)) {
	    int	i ;
	    for (i = 0 ; av[i] != nullptr ; i += 1)
	        debugprintf("main/test1: arg%u=>%s<\n",i,av[i]) ;
	}
#endif

	   if ((rs = uc_fork()) == 0) {
		cchar	*pf = lip->prog_cpp ;
		u_close(1) ;
		u_dup(fd_out) ;
		uc_execve(pf,av,pip->envv) ;
		uc_exit(1) ;
	   } else if (rs > 0) {
	       pid = rs ;
	   } /* end if (uc_fork) */
	   if (rs >= 0) rs = 0 ;
	   while (rs == 0) {
	       rs = u_waitpid(pid,&cstat,WUNTRACED) ;
	       if (rs == SR_INTR) rs = SR_OK ;
	   }
#if	CF_DEBUG
	    if (DEBUGLEVEL(5)) {
		USTAT	sb ;
	        debugprintf("main/test1: u_wait() rs=%d pid=%u\n",
			rs,pid) ;
#ifdef	COMMENT
		u_close(rfd) ;
		rfd = u_open(outfname,O_RDONLY,0666) ;
#endif
		u_fstat(rfd,&sb) ;
	        debugprintf("main/test1: fsize=%llu\n",sb.st_size) ;
	    }
#endif
	    if (rs >= 0) {
		if ((rs = u_rewind(rfd)) >= 0) {
	                if ((rs = proclines(pip,rfd)) >= 0) {
	                    rs = procerr(pip,fd_err) ;
	                }
		}
	    } /* end if (ok) */
	} /* end if (vecstr_getvec) */

/* done */
	u_close(fd_out) ;
	if (outfname[0] != '\0') {
	    u_unlink(outfname) ;
	    outfname[0] = '\0' ;
	}

ret2:
	u_close(fd_err) ;

ret1:
	vecstr_finish(&args) ;

	{
	    char	*p ;
	    p = outfname ;
	    if (p[0] != '\0') {
	        u_unlink(p) ;
	        p[0] = '\0' ;
	    }
	    p = errfname ;
	    if (p[0] != '\0') {
	        u_unlink(p) ;
	        p[0] = '\0' ;
	    }
	}

ret0:
	if ((pip->debuglevel > 0) && (rs < 0)) {
	    proceprintf(pip,"%s: testbugger (%d)\n",
	        pip->progname,rs) ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main/testbugger: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (test1) */


local int procsubprog(PROGINFO *pip,cchar *progcpp)
{
	LOCINFO		*lip = pip->lip ;
	int		rs = SR_OK ;
	cchar	*cp ;
	cchar	**vpp = &lip->prog_cpp ;

	if (progcpp != nullptr) {
	    rs = locinfo_setentry(lip,vpp,progcpp,-1) ;
	}

	if ((rs >= 0) && (lip->prog_cpp == nullptr)) {
	    if ((cp = getenv(VARCPP)) != nullptr) {
	        rs = locinfo_setentry(lip,vpp,cp,-1) ;
	    }
	}

	if ((rs >= 0) && (lip->prog_cpp == nullptr)) {
	    int		sl = -1 ;
	    cchar	*sp = CPPFNAME ;
	    char	tmpfname[MAXPATHLEN + 1] ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(3))
	        debugprintf("main: need to find CPP\n") ;
#endif

	    if ((rs = findfilepath(nullptr,tmpfname,sp,X_OK)) >= 0) {
	        if (rs > 0) {
	            sl = rs ;
	            sp = tmpfname ;
	        } else {
	            sl = -1 ;
		}
	    } else if (isNotPresent(rs)) {
	        int	i ;

	        for (i = 0 ; progcpps[i] != nullptr ; i += 1) {
	            sp = progcpps[i] ;
	            rs = perm(sp,-1,-1,nullptr,X_OK) ;
	            if (rs >= 0) break ;
	        } /* end for */

#if	CF_DEBUG
	        if (DEBUGLEVEL(3))
	            debugprintf("main: perm() rs=%d\n",rs) ;
#endif

	    } /* end if */

	    if (rs >= 0) {
	        rs = proginfo_setentry(pip,vpp,sp,sl) ;
	    }

	} /* end if */

	if (isNotPresent(rs)) {
	    cchar	*pn = pip->progname ;
	    cchar	*fmt = "%s: CPP program unavailable\n" ;
	    shio_printf(pip->efp,fmt,pn) ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(3)) {
	debugprintf("b_makesafe/procsubprog: ret rs=%d\n",rs) ;
	debugprintf("b_makesafe/procsubprog: cpp=%s\n",lip->prog_cpp) ;
	}
#endif

	return rs ;
}
/* end subroutine (procsubprog) */


local int proctouchfile(PROGINFO *pip,cchar touchfname[])
{
	bfile		touchfile ;
	int		rs = SR_OK ;
	int		f_write = false ;
	char		timebuf[TIMEBUFLEN + 1] ;

	if (pip == nullptr) return SR_FAULT ;
	if (touchfname == nullptr) return SR_FAULT ;

	if (touchfname[0] == '\0') return SR_INVALID ;

	pip->daytime = time(nullptr) ;

	rs = bopen(&touchfile,touchfname,"w",0666) ;

	if (isNotPresent(rs)) {
	    f_write = true ;
	    rs = bopen(&touchfile,touchfname,"wct",0666) ;
	}

	if (rs >= 0) {

#if	CF_ALWAYS
	    bprintf(&touchfile,"%s\n",
	        timestr_logz(pip->daytime,timebuf)) ;
#else
	    if (f_write || (lip->c_updated > 0))
	        bprintf(&touchfile,"%s\n",
	            timestr_logz(pip->daytime,timebuf)) ;
#endif /* CF_ALWAYS */

	    bclose(&touchfile) ;
	} /* end if (file) */

	return (rs >= 0) ? f_write : rs ;
}
/* end subroutine (proctouchfile) */


/* process the lines that contain dependency names */
local int proclines(PROGINFO *pip,int fd) noex {
	cint		to = pip->to_read ;
	int		rs ;
	int		rs1 ;
	int		c = 0 ;

#if	CF_DEBUG
	if (DEBUGLEVEL(5)) {
	    ustat	sb ;
	    int	rs1 ;
#if	CF_TESTSLEEP
	    sleep(5) ;
#endif
	    uc_fsync(fd) ;
	    debugprintf("proclines: ent to=%u\n",to) ;
	    rs1 = u_fstat(fd,&sb) ;
	    debugprintf("proclines: u_fstat() rs=%d\n",rs1) ;
	    debugprintf("proclines: fsize=%llu\n",sb.st_size) ;
	    debugprintf("proclines: mode=\\o%08o\n",sb.st_mode) ;
	}
#endif /* CF_DEBUG */

	    if (filer buf ; (rs = filer_start(&buf,fd,0z,FBUFLEN,0)) >= 0) {
	        struct lstate	ls ;
	        cint		llen = LINEBUFLEN ;
	        int		len ;
	        char		lbuf[LINEBUFLEN + 1] ;

	        memset(&ls,0,sizeof(struct lstate)) ;
	        while ((rs = filer_readln(&buf,lbuf,llen,to)) > 0) {
	            len = rs ;

	            if (lbuf[len - 1] == '\n') len -= 1 ;

#if	CF_DEBUG
	            if (DEBUGLEVEL(2))
	                debugprintf("proclines: line=>%r<\n",
	                    lbuf,
	                    ((lbuf[len - 1] == '\n') ? (len - 1) : len)) ;
#endif /* CF_DEBUG */

	            rs = procline(pip,&ls,lbuf,len) ;
	            c += rs ;

	            if (rs < 0) break ;
	        } /* end while */

	        rs1 = filer_finish(&buf) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (filer) */

	if ((pip->debuglevel > 0) && (rs < 0)) {
	    proceprintf(pip,"%s: proclines (%d)\n",
	        pip->progname,rs) ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(5))
	debugprintf("b_makesafe/proclines: ret rs=%d c=%u\n",rs,c) ;
#endif

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (proclines) */


/* process a dependecy line */
local int procline(PROGINFO *pip,LSTATE *lsp,cchar *lbuf,int len)
{
	int		rs = SR_OK ;
	int		sl ;
	int		f_continue = false ;
	int		c = 0 ;
	cchar	*tp, *sp ;

#if	CF_DEBUG
	if (DEBUGLEVEL(5)) {
	debugprintf("b_makesafe/procline: ent\n") ;
	debugprintf("b_makesafe/procline: l=%r\n",lbuf,len) ;
	}
#endif

	if ((len > 1) && (lbuf[len - 1] == CH_BSLASH)) {
	    f_continue = true ;
	    len -= 1 ;
	}

	sp = lbuf ;
	sl = len ;
	if (! lsp->f_continue) {
	    if ((tp = strnchr(sp,sl,':')) != nullptr) {
	        sl -= ((tp + 1) - sp) ;
	        sp = (tp + 1) ;
	    }
	}

	lsp->f_continue = f_continue ;

#if	CF_DEBUG
	if (DEBUGLEVEL(5))
	debugprintf("b_makesafe/procline: ret rs=%d c=%u\n",rs,c) ;
#endif

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (procline) */

/* process the error output */
local int procerr(PROGINFO *pip,int fd_err) noex {
	USTAT		sb ;
	cint		fsize = FBUFLEN ;
	int		rs ;
	int		rs1 ;
	int		to = pip->to_read ;

	rs = u_fstat(fd_err,&sb) ;

	if ((rs >= 0) && (sb.st_size > 0)) {
	    rs = u_rewind(fd_err) ;
	}

	if ((rs >= 0) && (sb.st_size > 0)) {
	    if (filer buf ; (rs = filer_start(&buf,fd_err,0z,fsize,0)) >= 0) {
	        cint	llen = LINEBUFLEN ;
	        int	len ;
	        char	lbuf[LINEBUFLEN + 1] ;

#if	CF_DEBUG
	        if (DEBUGLEVEL(2))
	            debugprintf("depsget: have error size=%u\n",
	                sb.st_size) ;
#endif

	        while (rs >= 0) {
	            rs = filer_readln(&buf,lbuf,llen,to) ;
	            len = rs ;
	            if (rs <= 0) break ;

	            if (lbuf[len - 1] == '\n') len -= 1 ;
	            lbuf[len] = '\0' ;

#if	CF_DEBUG
	            if (DEBUGLEVEL(2))
	                debugprintf("depsget: line> %r\n",
	                    lbuf,len) ;
#endif

	            rs = procerrline(pip,lbuf,len) ;

	        } /* end while */

	        rs1 = filer_finish(&buf) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (filer) */
	} /* end if (stat) */

	return rs ;
}
/* end subroutine (procerr) */


/* process an error line */
local int procerrline(PROGINFO *pip,cchar *lbuf,int len)
{
	int		rs = SR_OK ;
	int		cl, cl1, cl2 ;
	int		line ;
	cchar	*cp ;
	cchar	*cp1, *cp2 ;

	if ((cl2 = sfsub(lbuf,len,errsub2,&cp2)) >= 0) {
	    if ((cl1 = sfsub(lbuf,MIN(len,(cp2-lbuf)),errsub1,&cp1)) > 0) {
	        if ((cl = sfdequote(lbuf,(cp1-lbuf),&cp)) > 0) {
	            cint	dl = (cp2 - (cp1 + cl1)) ;
	            cchar	*dp = (cp1 + cl1) ;
	            if ((rs = cfdeci(dp,dl,&line)) >= 0) {
			CPPERR	e ;
	                if ((rs = cpperr_start(&e,line,cp,cl)) >= 0) {
	                    int		sl = (len-((cp2+cl2)-lbuf)) ;
	                    cchar	*sp = (cp2 + cl2) ;
	                    if ((cl = sfshrink(sp,sl,&cp)) > 0) {
	                        rs = cpperr_ifname(&e,cp,cl) ;
	                    }
	                    if (rs < 0)
	                        cpperr_finish(&e) ;
	                } /* end if (cpperr) */
	            } /* end if (cfdeci) */
	        } /* end if (sfdequote) */
	    } /* end if (sfsub) */
	} /* end if (sfsub) */

	return rs ;
}
/* end subroutine (procerrline) */

local int procout_begin(PROGINFO *pip,void *ofp,cchar *ofn)
{
	LOCINFO		*lip = pip->lip ;
	int		rs = SR_OK ;

	if ((ofn == nullptr) || (ofn[0] == '\0') || (ofn[0] == '-')) {
	    ofn = STDFNOUT ;
	}

	if (lip->fl.print || (pip->verboselevel > 0)) {
	    if ((rs = shio_open(ofp,ofn,"wct",0644)) >= 0) {
		ptm *mxp = &lip->ofm ;
	        if ((rs = mxp->create) >= 0) {
	            lip->ofp = ofp ;
	        }
	        if (rs < 0) {
	            shio_close(lip->ofp) ;
	        }
	    } /* end if (shio) */
	} /* end if */

	return rs ;
}
/* end subroutine (procout_begin) */

local int procout_end(PROGINFO *pip) noex {
	LOCINFO		*lip = pip->lip ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (lip->fl.print || (pip->verboselevel > 0)) {
	    {
	        ptm *mxp = &lip->ofm ;
	        rs1 = mxp->destroy ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = shio_close(lip->ofp) ;
	        if (rs >= 0) rs = rs1 ;
	        lip->ofp = nullptr ;
	    }
	}
	return rs ;
}
/* end subroutine (procout_end) */

local int procout_printf(PROGINFO *pip,cchar *fmt,...) noex {
	va_list		ap ;
	LOCINFO		*lip = pip->lip ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		len = 0 ;
	if ((lip->ofp != nullptr) && (pip->verboselevel > 0)) {
	    va_begin(ap,fmt) ;
	    ptm *mxp = &lip->ofm ;
	    if ((rs = mxp->lockbegin) >= 0) {
		{
	        rs = shio_vprintf(lip->ofp,fmt,ap) ;
	        len = rs ;
		}
	        rs1 = mxp->lockend ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (mutex) */
	    va_end(ap) ;
	} /* end if */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (procout_printf) */

local int cpperr_start(CPPERR *ep,int line,cchar *fp,int fl) noex {
	int		rs ;

	if (fp == nullptr) return SR_FAULT ;

	ep->line = line ;
	ep->fname = nullptr ;
	ep->ifname = nullptr ;
	if (cchar *cp ; (rs = lm_strw(fp,fl,&cp)) >= 0) {
	    ep->fname = cp ;
	}

	return rs ;
}
/* end subroutine (cpperr_start) */


local int cpperr_ifname(CPPERR *ep,cchar *fp,int fl)
{
	int		rs ;
	cchar	*cp ;

	if (fp == nullptr) return SR_FAULT ;

	if ((rs = lm_strw(fp,fl,&cp)) >= 0) {
	    ep->ifname = cp ;
	}

	return rs ;
}
/* end subroutine (cpperr_ifname) */


local int cpperr_finish(CPPERR *ep)
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (ep->fname != nullptr) {
	    rs1 = lm_free(ep->fname) ;
	    if (rs >= 0) rs = rs1 ;
	    ep->fname = nullptr ;
	}

	if (ep->ifname != nullptr) {
	    rs1 = lm_free(ep->ifname) ;
	    if (rs >= 0) rs = rs1 ;
	    ep->ifname = nullptr ;
	}

	ep->line = 0 ;
	return rs ;
}
/* end subroutine (cpperr_finish) */

local int locinfo_start(LOCINFO *lip,PROGINFO *pip) noex {
	int		rs = SR_OK ;
	memclear(lip) ; /* dangerous */
	lip->pip = pip ;
	lip->to_tmpfiles = TO_TMPFILES ;
	lip->fl.cache = OPT_CACHE ;
	if ((rs = ids_load(&lip->id)) >= 0) {
	    ptm *emp = &lip->efm ;
	    if ((rs = emp->create) >= 0) {
	        if ((rs = dirlist_start(&lip->incs)) >= 0) {
	            lip->open.incs = true ;
		    rs = locinfo_alreadybegin(lip) ;
		    if (rs < 0) {
	    	        dirlist_finish(&lip->incs) ;
		    }
	        }
	        if (rs < 0) {
		    emp->destroy() ;
		}
	    } /* end if (ptm_create) */
	    if (rs < 0) {
		ids_release(&lip->id) ;
	    }
	} /* end if (ids) */
	return rs ;
}
/* end subroutine (locinfo_start) */

local int locinfo_finish(LOCINFO *lip) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	{
	    rs1 = locinfo_alreadyend(lip) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (lip->open.incs) {
	    rs1 = dirlist_finish(&lip->incs) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    ptm *emp = &lip->efm ;
	    rs1 = emp->destroy ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    rs1 = ids_release(&lip->id) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    rs1 = locinfo_tmpdone(lip) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (lip->jobdname != nullptr) {
	    rs1 = lm_free(lip->jobdname) ;
	    if (rs >= 0) rs = rs1 ;
	    lip->jobdname = nullptr ;
	}
	if (lip->open.stores) {
	    lip->open.stores = false ;
	    rs1 = vecstr_finish(&lip->stores) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (locinfo_finish) */

#if	CF_LOCSETENT
int locinfo_setentry(LOCINFO *lip,cchar **epp,cchar *vp,int vl) noex {
	VECSTR		*slp ;
	int		rs = SR_OK ;
	int		len = 0 ;

	if (lip == nullptr) return SR_FAULT ;
	if (epp == nullptr) return SR_FAULT ;

	slp = &lip->stores ;
	if (! lip->open.stores) {
	    rs = vecstr_start(slp,4,0) ;
	    lip->open.stores = (rs >= 0) ;
	}

	if (rs >= 0) {
	    int	oi = -1 ;
	    if (*epp != nullptr) {
		oi = vecstr_findaddr(slp,*epp) ;
	    }
	    if (vp != nullptr) {
	        len = strnlen(vp,vl) ;
	        rs = vecstr_store(slp,vp,len,epp) ;
	    } else {
	        *epp = nullptr ;
	    }
	    if ((rs >= 0) && (oi >= 0)) {
	        vecstr_del(slp,oi) ;
	    }
	} /* end if (ok) */

	return (rs >= 0) ? len : rs ;
}
/* end subroutine (locinfo_setentry) */
#endif /* CF_LOCSETENT */

local int locinfo_jobdname(LOCINFO *lip) noex {
	PROGINFO	*pip = lip->pip ;
	int		rs ;
	if (lip->jobdname == nullptr) {
	    cchar	*pn = pip->progname ;
	    char	udname[MAXPATHLEN + 1] ;
	    if ((rs = mktmpuserdir(udname,"-",pn,0775)) >= 0) {
	        cchar	**vpp = &lip->jobdname ;
	        rs = locinfo_setentry(lip,vpp,udname,rs) ;
	    }
	} else {
	    rs = strlen(lip->jobdname) ;
	}
	return rs ;
}
/* end subroutine (locinfo_jobdname) */

/* this runs as an independent thread */
local int locinfo_tmpcheck(LOCINFO *lip) noex {
	PROGINFO	*pip = lip->pip ;
	int		rs = SR_OK ;

	if (lip->jobdname != nullptr) {
	    tmtime	t ;
	    if ((rs = tmtime_timelocal(&t,pip->daytime)) >= 0) {
	        if ((t.hour >= 18) || lip->fl.maint) {
		    uptsub_t	thr = (uptsub_t) locinfo_tmpmaint ;
	            pthread_t	tid ;
	            if ((rs = uptcreate(&tid,nullptr,thr,lip)) >= 0) {
	                rs = 1 ;
	                lip->tid = tid ;
	                lip->fl.tmpmaint = true ;
	            } /* end if (uptcreate) */
	        } /* end if (after hours) */
	    } /* end if (tmtime_timelocal) */
	} /* end if (jobdname) */

	return rs ;
}
/* end subroutine (locinfo_tmpcheck) */

/* this runs as an independent thread */
local int locinfo_tmpmaint(LOCINFO *lip) noex {
	PROGINFO	*pip = lip->pip ;
	cint	to = lip->to_tmpfiles ;
	int		rs ;
	int		c = 0 ;
	int		f_need = lip->fl.maint ;
	cchar		*dname = lip->jobdname ;
	char		tsfname[MAXPATHLEN+1] ;

	if ((rs = mkpath2(tsfname,dname,TSFNAME)) >= 0) {
	    cint	of = (O_WRONLY|O_CREAT) ;
	    cmode	om = 0666 ;
	    if ((rs = u_open(tsfname,of,om)) >= 0) {
	        ustat	usb ;
	        cint	fd = rs ;
	        if ((rs = u_fstat(fd,&usb)) >= 0) {
	            time_t	dt = pip->daytime ;
	            if ((rs = locinfo_fchmodown(lip,fd,&usb,om)) >= 0) {
	                int	maintlapse = (dt - usb.st_mtime) ;
	                f_need = f_need || (usb.st_size == 0) ;
	                f_need = f_need || (maintlapse >= to) ;
	                if (f_need) {
	                    int		tl ;
	                    char	timebuf[TIMEBUFLEN + 3] ;
	                    timestr_log(dt,timebuf) ;
	                    tl = strlen(timebuf) ;
	                    timebuf[tl++] = '\n' ;
	                    rs = u_write(fd,timebuf,tl) ;
	                } /* end if (timed-out) */
	            } /* end if (locinfo_fchmodown) */
	        } /* end if (stat) */
	        u_close(fd) ;
	    } /* end if (open file) */
	} /* end if (mkpath timestamp) */

	if ((rs >= 0) && f_need) {
	    rs = rmdirfiles(dname,nullptr,to) ;
	    c = rs ;
	}

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (locinfo_tmpmaint) */


local int locinfo_tmpdone(LOCINFO *lip)
{
	int		rs = SR_OK ;
	int		rs1 ;
	if (lip->fl.tmpmaint) {
	    int	trs ;
	    rs1 = uptjoin(lip->tid,&trs) ;
	    if (rs >= 0) rs = rs1 ;
	    if (rs >= 0) rs = trs ;
	}
	return rs ;
}
/* end subroutine (locinfo_tmpdone) */


local int locinfo_fchmodown(LOCINFO *lip,int fd,ustat *sbp,mode_t mm)
{
	PROGINFO	*pip = lip->pip ;
	int		rs = SR_OK ;
	int		f = false ;
	if ((sbp->st_size == 0) && (pip->euid == sbp->st_uid)) {
	    if ((sbp->st_mode & S_IAMB) != mm) {
	        if ((rs = locinfo_loadprids(lip)) >= 0) {
	            if ((rs = uc_fminmod(fd,mm)) >= 0) {
	                const uid_t	uid_pr = lip->uid_pr ;
	                const gid_t	gid_pr = lip->gid_pr ;
	                cint	n = _PC_CHOWN_RESTRICTED ;
	                if ((rs = u_fpathconf(fd,n,nullptr)) == 0) {
	                    f = true ;
	                    u_fchown(fd,uid_pr,gid_pr) ; /* may fail */
	                } else if (rs == SR_NOSYS) {
			    rs = SR_OK ;
	                }
	            }
	        } /* end if (locinfo_loadprids) */
	    } /* end if (need change) */
	} /* end if (zero-file) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (locinfo_fchmodown) */


local int locinfo_loadprids(LOCINFO *lip)
{
	PROGINFO	*pip = lip->pip ;
	int		rs = SR_OK ;
	if (lip->uid_pr < 0) {
	    ustat	sb ;
	    if ((rs = u_stat(pip->pr,&sb)) >= 0) {
	        lip->uid_pr = sb.st_uid ;
	        lip->gid_pr = sb.st_gid ;
	    } /* end if (u_stat) */
	} /* end if (needed) */
	return rs ;
}
/* end subroutine (locinfo_loadprids) */


local int locinfo_alreadybegin(LOCINFO *lip)
{
	int		rs = SR_OK ;
	if (lip->fl.cache) {
	    if ((rs = cachetime_start(&lip->mtdb)) >= 0) {
	        lip->open.cache = true ;
	    }
	}
	return rs ;
}
/* end subroutine (locinfo_alreadybegin) */

local int locinfo_alreadyend(LOCINFO *lip) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (lip->open.cache) {
	    lip->open.cache = false ;
	    rs1 = cachetime_finish(&lip->mtdb) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (locinfo_alreadyend) */

local int locinfo_incdirs(LOCINFO *lip) noex {
	int		rs = SR_OK ;
	int		c = 0 ;
	if (cchar *cp ; (cp = getenv(VARINCDIRS)) != nullptr) {
	    rs = dirlist_adds(&lip->incs,cp,-1) ;
	    c = rs ;
	} /* end if */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (locinfo_incdirs) */

local int locinfo_incadds(LOCINFO *lip,cchar *sp,int sl) noex {
	dirlist		*dlp = &lip->incs ;
	int		rs = SR_OK ;
	if (lip->open.incs) {
	    rs = dirlist_adds(dlp,sp,sl) ;
	} else {
	    rs = SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (locinfo_incadds) */

local int locinfo_alreadystat(LOCINFO *lip) noex {
	PROGINFO	*pip = lip->pip ;
	int		rs = SR_OK ;
	if ((pip->verboselevel > 0) || (pip->debuglevel > 0)) {
	    if (lip->open.cache) {
	        CACHETIME_STATS	stat ;

	        if ((rs = cachetime_stats(&lip->mtdb,&stat)) >= 0) {
	 	    cchar	*pn = pip->progname ;
	            cchar	*fmt ;
	            if (pip->verboselevel >= 3) {
	                fmt = "cache requests=%u hits=%u misses=%u\n" ;
	                shio_printf(lip->ofp,fmt,stat.req,stat.hit,stat.miss) ;
	            }
	            if (pip->debuglevel > 0) {
			fmt = "%s: cache requests=%u hits=%u misses=%u\n" ;
	                shio_printf(pip->efp,fmt,pn,
				stat.req,stat.hit,stat.miss) ;
	            }
	        } /* end if (successful) */

	    } /* end if (cache) */
	} /* end if (verbose or debug) */
	return rs ;
}
/* end subroutine (locinfo_alreadystat) */

local int locinfo_alreadylookup(LOCINFO *lip,cc *cp,int cl,time_t *rtp) noex {
	int		rs = SR_OK ;
	if (lip->open.cache) {
	    rs = cachetime_lookup(&lip->mtdb,cp,cl,rtp) ;
	} /* end if (cache) */
	return rs ;
}
/* end subroutine (locinfo_alreadylookup) */

local int locinfo_incbegin(LOCINFO *lip,LOCINFO_CUR *curp) noex {
	dirlist		*dlp = &lip->incs ;
	dirlist_cur	*dcp = &curp->c ;
	int		rs ;
	{
	    rs = dirlist_curbegin(dlp,dcp) ;
	}
	return rs ;
}
/* end subroutine (locinfo_incbegin) */

local int locinfo_incenum(LOCINFO *lip,LOCINFO_CUR *curp,
		char *rbuf,int rlen) noex {
	dirlist		*dlp = &lip->incs ;
	dirlist_cur	*dcp = &curp->c ;
	int		rs ;
	{
	    rs = dirlist_curenum(dlp,dcp,rbuf,rlen) ;
	}
	return rs ;
}
/* end subroutine (locinfo_incenum) */

local int locinfo_incend(LOCINFO *lip,LOCINFO_CUR *curp) noex {
	dirlist		*dlp = &lip->incs ;
	dirlist_cur	*dcp = &curp->c ;
	int		rs ;
	{
	    rs = dirlist_curend(dlp,dcp) ;
	}
	return rs ;
}
/* end subroutine (locinfo_incend) */

local int locinfo_ncpu(LOCINFO *lip) noex {
	int		rs = SR_OK ;
	if (lip->ncpu == 0) {
	    PROGINFO	*pip = lip->pip ;
	    rs = getnprocessors(pip->envv,0) ;
	    lip->ncpu = rs ;
	} else {
	    rs = lip->ncpu ;
	}
	return rs ;
}
/* end subroutine (locinfo_ncpu) */

#if	CF_DEBUG && CF_DEBUGENV
local int debugdumpenv(cchar **envv) noex {
	int		i = 0 ;
	debugprintf("main/debugdumpenv: env¬ {%p}\n",envv) ;
	for (i = 0 ; envv[i] != nullptr ; i += 1) {
	    cchar	*ep = envv[i] ;
	    debugprintf("main/debugdumpenv: e=%r\n",
		ep,strlinelen(ep,-1,40)) ;
	}
	return i ;
}
#endif /* CF_DEBUG */

#if	CF_WRFILE
local int wrfile(cchar *fn,int rfd) noex {
	cint	of = (O_WRONLY|O_CREAT) ;
	cint	to = 30 ;
	cint	ro = FM_TIMED ;
	cint	llen = LINEBUFLEN ;
	int		rs ;
	int		tlen = 0 ;
	char		lbuf[LINEBUFLEN+1] ;
	if ((rs = u_open(fn,of,0666)) >= 0) {
	    cint	wfd = rs ;
	    while ((rs = uc_reade(rfd,lbuf,llen,to,ro)) > 0) {
		tlen += rs ;
#if	CF_DEBUGS
		debugprintf("b_makesafe/wrfile: u_read() rs=%d\n",rs) ;
#endif
		rs = uc_writen(wfd,lbuf,rs) ;
		if (rs < 0) break ;
	    } /* end while */
	    u_close(wfd) ;
	}
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (wrfile) */
#endif /* CF_WRFILE */


