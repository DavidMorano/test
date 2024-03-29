/* main (C99) */

/* test program */


#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_DEBUG	0		/* run-time debug print-outs */
#define	CF_FOLLOWFILES	0		/* follow sybolic links of files */
#define	CF_FTCASE	1		/* try a C-lang 'switch' */


/* revision history:

	= 1998-02-01, David A�D� Morano

	The program was written from scratch to do what the previous
	program by the same name did.


*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	This is a fairly generic front-end subroutine for a program.


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<signal.h>
#include	<unistd.h>
#include	<time.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

#include	<usystem.h>
#include	<baops.h>
#include	<estrings.h>
#include	<bfile.h>
#include	<keyopt.h>
#include	<paramopt.h>
#include	<sigblock.h>
#include	<bwops.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"
#include	"termout.h"


/* local defines */

#define	MAXARGINDEX	10000
#define	MAXARGGROUPS	(MAXARGINDEX/8 + 1)

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX((MAXPATHLEN + 20),2048)
#endif

#define	LINKINFO	struct linkinfo

#define	DMODE		0775


/* external subroutines */

extern int	mkpath1(char *,const char *) ;
extern int	mkpath2(char *,const char *,const char *) ;
extern int	mkpath1w(char *,const char *,int) ;
extern int	mkpath2w(char *,const char *,const char *,int) ;
extern int	matstr(const char **,const char *,int) ;
extern int	matostr(const char **,int,const char *,int) ;
extern int	matpstr(const char **,int,const char *,int) ;
extern int	nleadstr(const char *,const char *,int) ;
extern int	cfdeci(const char *,int,int *) ;
extern int	cfdecti(const char *,int,int *) ;
extern int	optbool(const char *,int) ;
extern int	removes(const char *) ;
extern int	mkdirs(const char *,mode_t) ;
extern int	fileobject(const char *) ;
extern int	strwcmp(const char *,const char *,int) ;
extern int	isNotPresent(int) ;

extern int	proginfo_setpiv(struct proginfo *,const char *,
			const struct pivars *) ;
extern int	printhelp(void *,const char *,const char *,const char *) ;

#if	CF_DEBUGS || CF_DEBUG
extern int	debugopen(const char *) ;
extern int	debugprintf(const char *,...) ;
#endif

extern char	*strwcpy(char *,const char *,int) ;
extern char	*strnrchr(const char *,int,int) ;


/* local structures */

struct fileinfo_flags {
	uint		dangle:1 ;
} ;

struct fileinfo {
	struct fileinfo_flags	f ;
	uint		fts ;
} ;

struct linkinfo {
	ino64_t		ino ;
	const char	*fname ;
} ;


/* forward references */

static int	usage(struct proginfo *) ;

static int	procopts(struct proginfo *) ;
static int	procfts(struct proginfo *) ;
static int	procname(struct proginfo *,const char *) ;

static int	procsufbegin(struct proginfo *) ;
static int	procsufhave(struct proginfo *,const char *,int) ;
static int	procsufend(struct proginfo *) ;

static int	mkpdirs(const char *,mode_t) ;


/* external variables */


/* local structures */

enum fts {
	ft_r,
	ft_d,
	ft_b,
	ft_c,
	ft_p,
	ft_n,
	ft_l,
	ft_s,
	ft_D,
	ft_e,
	ft_overlast
} ;


/* local variables */

static const char	*argopts[] = {
	"ROOT",
	"VERSION",
	"VERBOSE",
	"TMPDIR",
	"HELP",
	"sn",
	"pm",
	"option",
	"set",
	"follow",
	"af",
	"of",
	"ef",
	"yf",
	"yi",
	"iacc",
	"nice",
	NULL
} ;

enum argopts {
	argopt_root,
	argopt_version,
	argopt_verbose,
	argopt_tmpdir,
	argopt_help,
	argopt_sn,
	argopt_pm,
	argopt_option,
	argopt_set,
	argopt_follow,
	argopt_af,
	argopt_of,
	argopt_ef,
	argopt_yf,
	argopt_yi,
	argopt_iacc,
	argopt_nice,
	argopt_overlast
} ;

static const struct pivars	initvars = {
	VARPROGRAMROOT1,
	VARPROGRAMROOT2,
	VARPROGRAMROOT3,
	PROGRAMROOT,
	VARPRLOCAL
} ;

static const struct mapex	mapexs[] = {
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

static const char	*progmodes[] = {
	"filesize",
	"filefind",
	"filelinker",
	"filesyncer",
	"filerm",
	NULL
} ;

enum progmodes {
	progmode_filesize,
	progmode_filefind,
	progmode_filelinker,
	progmode_filesyncer,
	progmode_filerm,
	progmode_overlast
} ;

static const char	*progopts[] = {
	"uniq",
	"name",
	"noprog",
	"nosock",
	"nopipe",
	"nofifo",
	"nodev",
	"noname",
	"nolink",
	"noextra",
	"cores",
	"nosuf",
	"follow",
	"younger",
	"yi",
	"iacc",
	"quiet",
	"nice",
	NULL
} ;

enum progopts {
	progopt_uniq,
	progopt_name,
	progopt_noprog,
	progopt_nosock,
	progopt_nopipe,
	progopt_nofifo,
	progopt_nodev,
	progopt_noname,
	progopt_nolink,
	progopt_noextra,
	progopt_cores,
	progopt_nosuf,
	progopt_follow,
	progopt_younger,
	progopt_yi,
	progopt_iacc,
	progopt_quiet,
	progopt_nice,
	progopt_overlast
} ;

static const char	*ftstrs[] = {
	"file",
	"directory",
	"block",
	"character",
	"pipe",
	"fifo",
	"name",
	"socket",
	"link",
	"door",
	"exists",
	"regular",
	NULL
} ;

enum ftstrs {
	ftstr_file,
	ftstr_directory,
	ftstr_block,
	ftstr_character,
	ftstr_pipe,
	ftstr_fifo,
	ftstr_name,
	ftstr_socket,
	ftstr_link,
	ftstr_door,
	ftstr_exists,
	ftstr_regular,
	ftstr_overlast
} ;

#ifdef	COMMENT

static const char	*whiches[] = {
	"uniq",
	"name",
	"noprog",
	"nosock",
	"nopipe",
	"nodev",
	"nolink",
	NULL
} ;

enum whiches {
	which_uniq,
	which_name,
	which_noprog,
	which_nosock,
	which_nopipe,
	which_nodev,
	which_nolink,
	which_overlast
} ;

#endif /* COMMENT */

static const char	*po_fts = PO_FTS ;
static const char	*po_sufreq = PO_SUFREQ ;
static const char	*po_sufacc = PO_SUFACC ;
static const char	*po_sufrej = PO_SUFREJ ;

static const char	*sufs[] = {
	PO_SUFREQ,
	PO_SUFACC,
	PO_SUFREJ,
	NULL
} ;

enum sufs {
	suf_req,
	suf_acc,
	suf_rej,
	suf_overlast
} ;

static const int	termrs[] = {
	SR_FAULT,
	SR_INVALID,
	SR_NOMEM,
	SR_NOANODE,
	SR_BADFMT,
	SR_NOSPC,
	SR_NOSR,
	SR_NOBUFS,
	SR_BADF,
	SR_OVERFLOW,
	SR_RANGE,
	0
} ;


/* exported subroutines */


int mainer(argc,argv,envv)
int		argc ;
const char	*argv[] ;
const char	*envv[] ;
{
	struct proginfo	pi, *pip = &pi ;

	bfile	errfile ;
	bfile	outfile, *ofp = &outfile ;

	int	argr, argl, aol, akl, avl, kwi ;
	int	ai, ai_max, ai_pos ;
	int	pan ;
	int	rs, rs1 ;
	int	cl ;
	int	v ;
	int	ex = EX_INFO ;
	int	f_optminus, f_optplus, f_optequal ;
	int	f_usage = FALSE ;
	int	f_version = FALSE ;
	int	f_help = FALSE ;
	int	f ;

	const char	*argp, *aop, *akp, *avp ;
	const char	*argval = NULL ;
	char	argpresent[MAXARGGROUPS] ;
	const char	*pr = NULL ;
	const char	*sn = NULL ;
	const char	*pmspec = NULL ;
	const char	*afname = NULL ;
	const char	*ofname = NULL ;
	const char	*efname = NULL ;
	const char	*yfname = NULL ;
	const char	*cp ;

#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	rs = proginfo_start(pip,envv,argv[0],VERSION) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badprogstart ;
	}

	if ((cp = getenv(VARBANNER)) == NULL) cp = BANNER ;
	proginfo_setbanner(pip,cp) ;

/* early things to initialize */

	pip->ofp = ofp ;
	pip->namelen = MAXNAMELEN ;
	pip->verboselevel = 1 ;

	pip->bytes = 0 ;
	pip->megabytes = 0 ;
	pip->progmode = -1 ;

/* process program arguments */

	if (rs >= 0) {
	    rs = keyopt_start(&pip->akopts) ;
	    pip->open.akopts = (rs >= 0) ;
	}

	if (rs >= 0) {
	    rs = paramopt_start(&pip->aparams) ;
	    pip->open.aparams = (rs >= 0) ;
	}

	for (ai = 0 ; ai < MAXARGGROUPS ; ai += 1)
	    argpresent[ai] = 0 ;

	ai = 0 ;
	ai_max = 0 ;
	ai_pos = 0 ;
	argr = argc ;
	for (ai = 0 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
	    if (rs < 0) break ;
	    argr -= 1 ;
	    if (ai == 0) continue ;

	    argp = argv[ai] ;
	    argl = strlen(argp) ;

	    f_optminus = (*argp == '-') ;
	    f_optplus = (*argp == '+') ;
	    if ((argl > 1) && (f_optminus || f_optplus)) {

	        if (isdigit(argp[1])) {

	            argval = (argp+1) ;

	        } else if (argp[1] == '-') {

	            ai_pos = ai ;
	            break ;

	        } else {

	            aop = argp + 1 ;
	            akp = aop ;
	            aol = argl - 1 ;
	            f_optequal = FALSE ;
	            if ((avp = strchr(aop,'=')) != NULL) {
	                f_optequal = TRUE ;
	                akl = avp - aop ;
	                avp += 1 ;
	                avl = aop + argl - 1 - avp ;
	                aol = akl ;
	            } else {
	                avp = NULL ;
	                avl = 0 ;
	                akl = aol ;
	            }

/* do we have a keyword match or should we assume only key letters? */

	            kwi = matostr(argopts,2,akp,akl) ;

	            if (kwi >= 0) {

	                switch (kwi) {

/* program root */
	                case argopt_root:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            pr = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            pr = argp ;
	                    }
	                    break ;

/* program mode */
	                case argopt_pm:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            pmspec = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            pmspec = argp ;
	                    }
	                    break ;

/* the user specified some progopts */
	                case argopt_option:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl)
	                        rs = keyopt_loads(&pip->akopts,argp,argl) ;
	                    break ;

/* search name */
	                case argopt_sn:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            sn = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            sn = argp ;
	                    }
	                    break ;

/* version */
	                case argopt_version:
	                    f_version = TRUE ;
	                    if (f_optequal)
	                        rs = SR_INVALID ;
	                    break ;

/* verbose */
	                case argopt_verbose:
	                    pip->verboselevel = 2 ;
	                    if (f_optequal) {

	                        f_optequal = FALSE ;
	                        if (avl) {
	                            rs = cfdeci(avp,avl,&v) ;
	                            pip->verboselevel = v ;
	                        }
	                    }
	                    break ;

/* temporary directory */
	                case argopt_tmpdir:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            pip->tmpdname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            pip->tmpdname = argp ;
	                    }
	                    break ;

	                case argopt_help:
	                    f_help = TRUE ;
	                    break ;

/* the user specified some progopts */
	                case argopt_set:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl)
	                        rs = paramopt_loadu(&pip->aparams,argp,argl) ;
	                    break ;

/* argument files */
	                case argopt_af:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            afname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            afname = argp ;
	                    }
	                    break ;

/* output file */
	                case argopt_of:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            ofname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            ofname = argp ;
	                    }
	                    break ;

/* error file */
	                case argopt_ef:
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl)
	                            efname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            efname = argp ;
	                    }
	                    break ;

/* follow symbolic links */
	                case argopt_follow:
	                    pip->final.follow = TRUE ;
	                    pip->have.follow = TRUE ;
	                    pip->f.follow = TRUE ;
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl) {
	                            rs = optbool(avp,avl) ;
	                            pip->f.follow = (rs > 0) ;
	                        }
	                    }
	                    break ;

/* ignore inaccessible files */
	                case argopt_iacc:
	                    pip->final.iacc = TRUE ;
	                    pip->have.iacc = TRUE ;
	                    pip->f.iacc = TRUE ;
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl) {
	                            rs = optbool(avp,avl) ;
	                            pip->f.iacc = (rs > 0) ;
	                        }
	                    }
	                    break ;

/* nice value */
	                case argopt_nice:
	                    cp = NULL ;
	                    cl = -1 ;
	                    pip->final.nice = TRUE ;
	                    pip->have.nice = TRUE ;
	                    pip->f.nice = TRUE ;
	                    if (f_optequal) {
	                        f_optequal = FALSE ;
	                        if (avl) {
	                            cp = avp ;
	                            cl = avl ;
	                        }
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl) {
	                            cp = argp ;
	                            cl = argl ;
	                        }
	                    }
	                    if (cp != NULL) {
	                        rs = cfdeci(cp,cl,&v) ;
	                        pip->nice = v ;
	                    }
	                    break ;

/* younger-file */
	                case argopt_yf:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl)
	                        yfname = argp ;
	                    break ;

/* younger-interval */
	                case argopt_yi:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl) {
	                        pip->have.younger = TRUE ;
	                        pip->final.younger = TRUE ;
	                        rs = cfdecti(argp,argl,&v) ;
	                        pip->younger = v ;
	                    }
	                    break ;

/* default action and user specified help */
	                default:
	                    rs = SR_INVALID ;
	                    break ;

	                } /* end switch (key words) */

	            } else {

	                while (akl--) {
	                    int	kc = (*akp & 0xff) ;

	                    switch (kc) {

	                    case 'D':
	                        pip->debuglevel = 1 ;
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = cfdeci(avp,avl,&v) ;
	                                pip->debuglevel = v ;
	                            }
	                        }
	                        break ;

/* quiet */
	                    case 'Q':
	                        pip->f.quiet = TRUE ;
	                        break ;

/* program-root */
	                    case 'R':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            pr = argp ;
	                        break ;

	                    case 'V':
	                        f_version = TRUE ;
	                        if (f_optequal)
	                            rs = SR_INVALID ;
	                        break ;

/* continue on error */
	                    case 'c':
	                        pip->final.nostop = TRUE ;
	                        pip->have.nostop = TRUE ;
	                        pip->f.nostop = TRUE ;
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                pip->f.nostop = (rs > 0) ;
	                            }
	                        }
	                        break ;

/* target directory */
	                    case 'd':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl) {
	                            pip->final.tardname = TRUE ;
	                            pip->have.tardname = TRUE ;
	                            pip->tardname = argp ;
	                        }
	                        break ;

/* follow symbolic links */
	                    case 'f':
	                        pip->final.follow = TRUE ;
	                        pip->have.follow = TRUE ;
	                        pip->f.follow = TRUE ;
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                pip->f.follow = (rs > 0) ;
	                            }
	                        }
	                        break ;

/* file name length restriction */
	                    case 'l':
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = cfdeci(avp,avl,&v) ;
	                                pip->namelen = v ;
	                            }
	                        } else {
	                            if (argr <= 0) {
	                                rs = SR_INVALID ;
	                                break ;
	                            }
	                            argp = argv[++ai] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;
	                            if (argl) {
	                                rs = cfdeci(argp,argl,&v) ;
	                                pip->namelen = v ;
	                            }
	                        }
	                        break ;

/* no-change */
	                    case 'n':
	                        pip->f.nochange = TRUE ;
	                        break ;

/* options */
	                    case 'o':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            rs = keyopt_loads(&pip->akopts,argp,argl) ;
	                        break ;

/* quiet */
	                    case 'q':
	                        pip->final.quiet = TRUE ;
	                        pip->have.quiet = TRUE ;
	                        pip->f.quiet = TRUE ;
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                pip->f.quiet = (rs > 0) ;
	                            }
	                        }
	                        break ;

/* file types */
	                    case 't':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            rs = paramopt_loads(&pip->aparams,
	                                po_fts,argp,argl) ;
	                        break ;

/* verbose output */
	                    case 'v':
	                        pip->verboselevel = 2 ;
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = cfdeci(avp,avl,&v) ;
	                                pip->verboselevel = v ;
	                            }
	                        }
	                        break ;

	                    case 'y':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl) {
	                            pip->final.younger = TRUE ;
	                            pip->have.younger = TRUE ;
	                            rs = cfdecti(argp,argl,&v) ;
	                            pip->younger = v ;
	                        }
	                        break ;

/* allow zero number of arguments */
	                    case 'z':
	                        pip->final.zargs = TRUE ;
	                        pip->final.zargs = TRUE ;
	                        pip->f.zargs = TRUE ;
	                        if (f_optequal) {
	                            f_optequal = FALSE ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                pip->f.zargs = (rs > 0) ;
	                            }
	                        }
	                        break ;

	                    case '?':
	                        f_usage = TRUE ;
	                        break ;

	                    default:
	                        rs = SR_INVALID ;
	                        break ;

	                    } /* end switch */

	                    akp += 1 ;
	                    if (rs < 0)
	                        break ;

	                } /* end while */

	            } /* end if (individual option key letters) */

	        } /* end if (digits or progopts) */

	    } else {

	        if (ai >= MAXARGINDEX)
	            break ;

	        BASET(argpresent,ai) ;
	        ai_max = ai ;

	    } /* end if (key letter/word or positional) */

	    ai_pos = ai ;

	} /* end while (all command line argument processing) */

	if (efname == NULL) efname = getenv(VARERRORFNAME) ;
	if (efname == NULL) efname = BFILE_STDERR ;
	if ((rs1 = bopen(&errfile,efname,"wca",0666)) >= 0) {
	    pip->efp = &errfile ;
	    pip->open.errfile = TRUE ;
	    bcontrol(&errfile,BC_SETBUFLINE,TRUE) ;
	}

	if (rs < 0) {
	    ex = EX_USAGE ;
	    bprintf(pip->efp,"%s: invalid argument specified (%d)\n",
	        pip->progname,rs) ;
	    usage(pip) ;
	    goto retearly ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: debuglevel=%u\n",pip->debuglevel) ;
#endif

	if (pip->debuglevel > 0) {
	    bprintf(pip->efp,"%s: debuglevel=%u\n",
	        pip->progname,pip->debuglevel) ;
	    bcontrol(pip->efp,BC_LINEBUF,0) ;
	    bflush(pip->efp) ;
	}

	if (f_version)
	    bprintf(pip->efp,"%s: version %s\n",
	        pip->progname,VERSION) ;

/* get the program root */

	rs = proginfo_setpiv(pip,pr,&initvars) ;

	if (rs >= 0)
	    rs = proginfo_setsearchname(pip,VARSEARCHNAME,sn) ;

	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto retearly ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) {
	    debugprintf("main: pr=%s\n",pip->pr) ;
	    debugprintf("main: sn=%s\n",pip->searchname) ;
	}
#endif

	if (pip->debuglevel > 0) {
	    bprintf(pip->efp,"%s: pr=%s\n", pip->progname,pip->pr) ;
	    bprintf(pip->efp,"%s: sn=%s\n", pip->progname,pip->searchname) ;
	} /* end if */

/* get our program mode */

	if (pmspec == NULL) pmspec = pip->progname ;

	pip->progmode = matstr(progmodes,pmspec,-1) ;

	if (pip->progmode < 0)
	    pip->progmode = progmode_filesize ;

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) {
	    if (pip->progmode >= 0) {
	        debugprintf("main: progmode=%s(%u)\n",
	            progmodes[pip->progmode],pip->progmode) ;
	    } else
	        debugprintf("main: progmode=NONE\n") ;
	}
#endif /* CF_DEBUG */

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: progmode=%s(%u)\n",
	        pip->progname,progmodes[pip->progmode],pip->progmode) ;

	if (f_usage)
	    usage(pip) ;

/* help file */

	if (f_help)
	    printhelp(NULL,pip->pr,pip->searchname,HELPFNAME) ;

	if (f_version || f_help || f_usage)
	    goto retearly ;


	ex = EX_OK ;

/* initialization */

	pip->daytime = time(NULL) ;
	pip->euid = geteuid() ;
	pip->uid = getuid() ;

/* younger file? */

	if ((rs >= 0) && (pip->younger == 0)) {
	    if (argval != NULL) {
	        pip->have.younger = TRUE ;
	        rs = cfdecti(argval,-1,&v) ;
	        pip->younger = v ;
	    }
	}

	if ((rs >= 0) && (pip->younger == 0)) {
	    if ((yfname != NULL) && (yfname[0] != '\0')) {
	        struct ustat	sb ;
	        int rs1 = uc_stat(yfname,&sb) ;
	        if (rs1 >= 0) {
	            pip->have.younger = TRUE ;
	            pip->younger = (pip->daytime - sb.st_mtime) ;
	        }
	    }
	}

/* get more program options */

	if (rs >= 0)
	    rs = procopts(pip) ;

	if (rs >= 0)
	    rs = procfts(pip) ;

	if ((rs >= 0) && pip->f.cores)
	    pip->fts |= (1 << ft_r) ;

	if (rs < 0) {
	    ex = EX_USAGE ;
	    goto retearly ;
	}

	if (pip->f.f_noextra) {
	    pip->f.f_nodev = TRUE ;
	    pip->f.f_nopipe = TRUE ;
	    pip->f.f_nosock = TRUE ;
	    pip->f.f_noname = TRUE ;
	    pip->f.f_nodoor = TRUE ;
	}

/* create the 'fnos' value */

	if (pip->f.f_nodev) {
	    bwset(pip->fnos,ft_c) ;
	    bwset(pip->fnos,ft_b) ;
	}
	if (pip->f.f_noname) bwset(pip->fnos,ft_n) ;
	if (pip->f.f_nopipe) bwset(pip->fnos,ft_p) ;
	if (pip->f.f_nolink) bwset(pip->fnos,ft_l) ;
	if (pip->f.f_nosock) bwset(pip->fnos,ft_s) ;
	if (pip->f.f_nodoor) bwset(pip->fnos,ft_d) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2)) {
	    debugprintf("main: f_follow=%u\n",pip->f.follow) ;
	    debugprintf("main: f_continue=%u\n",pip->f.nostop) ;
	    debugprintf("main: f_iacc=%u\n",pip->f.iacc) ;
	}
#endif /* CF_DEBUG */

	if (pip->debuglevel > 0) {
	    const char	*pn = pip->progname ;
	    bprintf(pip->efp,"%s: follow=%u\n",pn,pip->f.follow) ;
	    bprintf(pip->efp,"%s: continue=%u\n",pn,pip->f.nostop) ;
	    bprintf(pip->efp,"%s: iacc=%u\n",pn,pip->f.iacc) ;
	}

/* check a few more things */

	if (pip->tmpdname == NULL) pip->tmpdname = getenv(VARTMPDNAME) ;
	if (pip->tmpdname == NULL) pip->tmpdname = TMPDNAME ;

	{
	    int	f = FALSE ;

	    f = f || (pip->progmode == progmode_filelinker) ;
	    f = f || (pip->progmode == progmode_filesyncer) ;
	    if (f) {
	        const char	*fmt ;

	        if (pip->tardname == NULL) {
	            if ((cp = getenv(VARTARDNAME)) != NULL) {
	                pip->have.tardname = TRUE ;
	                pip->tardname = cp ;
	            }
	        }

	        if ((pip->tardname == NULL) || (pip->tardname[0] == '\0')) {
	            fmt ="%s: no target directory specified\n" ;
	            rs = SR_INVALID ;
	            bprintf(pip->efp,fmt, pip->progname) ;
	        }
	        if (rs >= 0) {
	            rs = fsdirtreestat(pip->tardname,0,&pip->tarstat) ;
	            if ((rs < 0) || (! S_ISDIR(pip->tarstat.st_mode))) {
	                fmt = "%s: target directory inaccessible (%d)\n" ;
	                rs = SR_NOTDIR ;
	                bprintf(pip->efp,fmt, pip->progname,rs) ;
	            }
	        }
	        if (rs < 0) {
	            ex = EX_USAGE ;
	            goto retearly ;
	        }

	    }
	} /* end block */

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: tardname=%s\n",pip->tardname) ;
#endif

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: tardname=%s\n",pip->progname,pip->tardname) ;

#ifdef	COMMENT
	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: follow=%u\n",pip->progname,pip->f.follow) ;
#endif

	if ((rs >= 0) && (pip->nice > 0)) {
	    int	n = MIN(pip->nice,19) ;
	    rs = u_nice(n) ;
	}

/* get ready */

	if (rs >= 0)
	    rs = procsufbegin(pip) ;

	if (rs < 0)
	    goto done ;

/* start processing */

	if ((ofname == NULL) || (ofname[0] == '\0') || (ofname[0] == '-'))
	    ofname = BFILE_STDOUT ;
	rs = bopen(ofp,ofname,"wct",0644) ;
	if (rs < 0) {
	    ex = EX_CANTCREAT ;
	    bprintf(pip->efp,"%s: output unavailable (%d)\n",
	        pip->progname,rs) ;
	    goto badoutopen ;
	}

/* OK, we do it */

	pan = 0 ;

	for (ai = 1 ; ai < argc ; ai += 1) {

	    f = (ai <= ai_max) && BATST(argpresent,ai) ;
	    f = f || ((ai > ai_pos) && (argv[ai] != NULL)) ;
	    if (! f) continue ;

	    cp = argv[ai] ;
	    pan += 1 ;
	    rs = procname(pip,cp) ;

	    if (rs < 0) {
	        bprintf(pip->efp,
	            "%s: error name=%s (%d)\n",
	            pip->progname,cp,rs) ;
	        break ;
	    }

	} /* end for (looping through requested circuits) */

/* process any files in the argument filename list file */

	if ((rs >= 0) && (afname != NULL) && (afname[0] != '\0')) {
	    bfile	afile, *afp = &afile ;

	    if (strcmp(afname,"-") == 0) afname = BFILE_STDIN ;
	    rs = bopen(afp,afname,"r",0666) ;
	    if (rs >= 0) {
	        int	len ;
	        char	linebuf[LINEBUFLEN + 1] ;

	        while ((rs = breadln(afp,linebuf,LINEBUFLEN)) > 0) {
	            len = rs ;

	            if (linebuf[len - 1] == '\n') len -= 1 ;
	            linebuf[len] = '\0' ;

	            cp = linebuf ;
	            cl = len ;
	            if (cl == 0) continue ;

	            pan += 1 ;
	            rs = procname(pip,cp) ;

	            if (rs < 0) {
	                bprintf(pip->efp,
	                    "%s: error name=%s (%d)\n",
	                    pip->progname,cp,rs) ;
	                break ;
	            }

	        } /* end while (reading lines) */

	        bclose(afp) ;
	    } else {

	        if (! pip->f.quiet) {
	            bprintf(pip->efp,
	                "%s: could not open the argument list file (%d)\n",
	                pip->progname,rs) ;
	            bprintf(pip->efp,"%s: \targfile=%s\n",
	                pip->progname,afname) ;
	        }

	    } /* end if */

	} /* end if (processing file argument file list) */

	if ((rs >= 0) && (pip->progmode == progmode_filesize)) {
	    long	blocks, blockbytes ;

	    bprintf(ofp,"%lu megabyte%s and %lu bytes\n",
	        pip->megabytes,
	        ((pip->megabytes == 1) ? "" : "s"),
	        pip->bytes) ;

/* calculate UNIX blocks */

	    blocks = pip->megabytes * 1024 * 2 ;
	    blocks += (pip->bytes / UNIXBLOCK) ;
	    blockbytes = (pip->bytes % UNIXBLOCK) ;

	    bprintf(ofp,"%lu UNIX blocks and %lu bytes\n",
	        blocks,blockbytes) ;

	} /* end if (program mode=filesize) */

	bclose(ofp) ;

badoutopen:
	procsufend(pip) ;

	if ((pip->debuglevel > 0) && (pan > 0))
	    bprintf(pip->efp,"%s: files=%u processed=%u\n",
	        pip->progname,pip->c_files,pip->c_processed) ;

	if ((rs >= 0) && (pan == 0) && (! pip->f.zargs) && (! pip->f.quiet)) {
	    ex = EX_USAGE ;
	    bprintf(pip->efp,"%s: no files or directories were specified\n",
	        pip->progname) ;
	}

done:
	if ((rs < 0) && (ex == EX_OK)) {
	    switch (rs) {

	    case SR_INVALID:
	        ex = EX_USAGE ;
	        if (! pip->f.quiet)
	            bprintf(pip->efp,"%s: invalid usage (%d)\n",
	                pip->progname,rs) ;
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

retearly:
	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: exiting ex=%u (%d)\n",
	        pip->progname,ex,rs) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: exiting ex=%u (%d)\n",ex,rs) ;
#endif

	if (pip->efp != NULL) {
	    bclose(pip->efp) ;
	    pip->efp = NULL ;
	}

	if (pip->open.aparams) {
	    pip->open.aparams = FALSE ;
	    paramopt_finish(&pip->aparams) ;
	}

	if (pip->open.akopts) {
	    pip->open.akopts = FALSE ;
	    keyopt_finish(&pip->akopts) ;
	}

ret2:
ret1:
	proginfo_finish(pip) ;

ret0:
badprogstart:

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

	return ex ;
}
/* end subroutine (main) */


/* local subroutines */


static int usage(pip)
struct proginfo	*pip ;
{
	int	rs ;
	int	wlen = 0 ;


	rs = bprintf(pip->efp,
	    "%s: USAGE> %s [<dir(s)> ...] [-af {<argfile>|-}] \n",
	    pip->progname,pip->progname) ;


	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-f] [-c] [-ia] [-s <suffix(es)>] \n",
	    pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-sa <sufacc(s)>] [-sr <sufrej(s)>] [-t <type(s)>]\n",
	    pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-o <option(s)] \n",
	    pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-Q] [-D] [-v[=<n>]] [-HELP] [-V]\n",
	    pip->progname) ;

	wlen += rs ;
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (usage) */


static int procopts(pip)
struct proginfo	*pip ;
{
	KEYOPT		*kop = &pip->akopts ;
	KEYOPT_CUR	kcur ;

	int	rs = SR_OK ;
	int	oi ;
	int	kl, vl ;
	int	v ;
	int	c = 0 ;

	const char	*kp, *vp ;
	const char	*cp ;


	if ((cp = getenv(VAROPTS)) != NULL)
	    rs = keyopt_loads(kop,cp,-1) ;

	if (rs < 0)
	    goto ret0 ;

/* process program options */

	if ((rs = keyopt_curbegin(kop,&kcur)) >= 0) {

	    while ((kl = keyopt_enumkeys(kop,&kcur,&kp)) >= 0) {

/* get the first value for this key */

	        vl = keyopt_fetch(kop,kp,NULL,&vp) ;

/* do we support this option? */

	        if ((oi = matostr(progopts,1,kp,kl)) >= 0) {

	            c += 1 ;
	            switch (oi) {

	            case progopt_uniq:
	                if (! pip->final.f_uniq) {
	                    pip->final.f_uniq = TRUE ;
	                    pip->f.f_uniq = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_uniq = (rs > 0) ;
	                    }
	                }
	                break ;

/* [what is this?] */
	            case progopt_name:
	                if (! pip->final.f_name) {
	                    pip->final.f_name = TRUE ;
	                    pip->f.f_name = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_name = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_noprog:
	                if (! pip->final.f_noprog) {
	                    pip->final.f_noprog = TRUE ;
	                    pip->f.f_noprog = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_noprog = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_nosock:
	                if (! pip->final.f_nosock) {
	                    pip->final.f_nosock = TRUE ;
	                    pip->f.f_nosock = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_nosock = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_nopipe:
	            case progopt_nofifo:
	                if (! pip->final.f_nopipe) {
	                    pip->final.f_nopipe = TRUE ;
	                    pip->f.f_nopipe = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_nopipe = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_nodev:
	                if (! pip->final.f_nodev) {
	                    pip->final.f_nodev = TRUE ;
	                    pip->f.f_nodev = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_nodev = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_noname:
	                if (! pip->final.f_noname) {
	                    pip->final.f_noname = TRUE ;
	                    pip->f.f_noname = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_noname = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_nolink:
	                if (! pip->final.f_nolink) {
	                    pip->final.f_nolink = TRUE ;
	                    pip->f.f_nolink= TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_nolink = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_noextra:
	                if (! pip->final.f_noextra) {
	                    pip->final.f_noextra = TRUE ;
	                    pip->f.f_noextra = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.f_noextra = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_cores:
	                if (! pip->final.cores) {
	                    pip->final.cores = TRUE ;
	                    pip->f.cores = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.cores = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_follow:
	                if (! pip->final.follow) {
	                    pip->final.follow = TRUE ;
	                    pip->have.follow = TRUE ;
	                    pip->f.follow = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.follow = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_younger:
	            case progopt_yi:
	                if ((vl > 0) && (! pip->final.younger)) {
	                    pip->final.younger = TRUE ;
	                    pip->have.younger = TRUE ;
	                    rs = cfdecti(vp,vl,&v) ;
	                    pip->younger = v ;
	                }
	                break ;

	            case progopt_iacc:
	                if (! pip->final.iacc) {
	                    pip->final.iacc = TRUE ;
	                    pip->have.iacc = TRUE ;
	                    pip->f.iacc = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.iacc = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_quiet:
	                if (! pip->final.quiet) {
	                    pip->final.quiet = TRUE ;
	                    pip->have.quiet = TRUE ;
	                    pip->f.iacc = TRUE ;
	                    if (vl > 0) {
	                        rs = optbool(vp,vl) ;
	                        pip->f.quiet = (rs > 0) ;
	                    }
	                }
	                break ;

	            case progopt_nice:
	                if ((vl > 0) && (! pip->final.nice)) {
	                    pip->final.nice = TRUE ;
	                    pip->have.nice = TRUE ;
	                    rs = cfdeci(vp,vl,&v) ;
	                    pip->nice = v ;
	                }
	                break ;

	            } /* end switch */

	        } /* end if */

	        if (rs < 0)
	            break ;

	    } /* end while */

	    keyopt_curend(kop,&kcur) ;
	} /* end if (cursor) */

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (procopts) */


static int procfts(pip)
struct proginfo	*pip ;
{
	PARAMOPT	*pop = &pip->aparams ;
	PARAMOPT_CUR	cur ;

	int	rs = SR_OK ;
	int	vl ;
	int	fti ;
	int	c = 0 ;

	const char	*varftypes = getenv(VARFTYPES) ;
	const char	*vp ;


	if (varftypes != NULL)
	    rs = paramopt_loads(pop,po_fts,varftypes,-1) ;

	if (rs < 0) goto ret0 ;

	if ((rs = paramopt_curbegin(pop,&cur)) >= 0) {

	    while (rs >= 0) {

	        vl = paramopt_fetch(pop,po_fts,&cur,&vp) ;
	        if (vl == SR_NOTFOUND) break ;

	        if (vl == 0) continue ;

	        rs = vl ;
	        if (rs < 0)
	            break ;

	        fti = matostr(ftstrs,1,vp,vl) ;

#if	CF_DEBUG
	        if (DEBUGLEVEL(3))
	            debugprintf("main/procfts: v=%t\n",vp,vl) ;
#endif

	        if (fti >= 0) {

	            switch (fti) {

	            case ftstr_regular:
	            case ftstr_file:
	                pip->fts |= (1 << ft_r) ;
	                break ;

	            case ftstr_directory:
	                pip->fts |= (1 << ft_d) ;
	                break ;

	            case ftstr_block:
	                pip->fts |= (1 << ft_b) ;
	                break ;

	            case ftstr_character:
	                pip->fts |= (1 << ft_c) ;
	                break ;

	            case ftstr_pipe:
	            case ftstr_fifo:
	                pip->fts |= (1 << ft_p) ;
	                break ;

	            case ftstr_socket:
	                pip->fts |= (1 << ft_s) ;
	                break ;

	            case ftstr_link:
	                pip->fts |= (1 << ft_l) ;
	                break ;

	            case ftstr_name:
	                pip->fts |= (1 << ft_n) ;
	                break ;

	            case ftstr_door:
	                pip->fts |= (1 << ft_D) ;
	                break ;

	            case ftstr_exists:
	                pip->fts |= (1 << ft_e) ;
	                break ;

	            } /* end switch */

	            c += 1 ;

	        } /* end if */

	    } /* end while */

	    paramopt_curend(pop,&cur) ;
	} /* end if (cursor) */

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (procfts) */


int procname(pip,name)
struct proginfo	*pip ;
const char	name[] ;
{
	FSDIRTREE_STAT	sb, ssb, *sbp = &sb ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	f_islink = FALSE ;
	int	f_isdir = FALSE ;


	if (name == NULL)
	    return SR_FAULT ;

	if (name[0] == '\0')
	    return SR_INVALID ;

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	    debugprintf("main/procname: entered name=%s\n",name) ;
#endif

	rs = fsdirtreestat(name,1,&sb) ; /* this is LSTAT */

#if	CF_DEBUG
	if (DEBUGLEVEL(3)) {
	    if (rs < 0) sb.st_mode = 0 ;
	    debugprintf("main/procname: fsdirtreestat() rs=%d mode=%0o\n", 
	        rs,sb.st_mode) ;
	}
#endif

	if (rs < 0) goto ret0 ;

	f_isdir = S_ISDIR(sb.st_mode) ;
	f_islink = S_ISLNK(sb.st_mode) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(3)) {
	    debugprintf("main/procname: f_isdir=%u\n",f_isdir) ;
	    debugprintf("main/procname: f_islink=%u\n",f_islink) ;
	}
#endif

	if (f_islink && pip->f.follow) {

	    rs1 = fsdirtreestat(name,0,&ssb) ; /* STAT */
	    if (rs1 >= 0) {
	        f_isdir = S_ISDIR(ssb.st_mode) ;
	        sbp = &ssb ;
	    }

#if	CF_DEBUG
	    if (DEBUGLEVEL(3))
	        debugprintf("main/procname: symlink dangle=%u\n",
	            ((rs1 < 0)?1:0)) ;
#endif

	} /* end if */

ret0:

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	    debugprintf("main/procname: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (procname) */


static int procsufhave(pip,sp,sl)
struct proginfo	*pip ;
const char	*sp ;
int		sl ;
{
	PARAMOPT	*pop = &pip->aparams ;
	PARAMOPT_CUR	cur ;

	int	rs = SR_OK ;
	int	vl ;
	int	m ;
	int	f = FALSE ;

	const char	*key = po_sufreq ;
	const char	*vp ;


	if (sl < 0) sl = strlen(sp) ;

	if ((rs = paramopt_curbegin(pop,&cur)) >= 0) {

	    while (rs >= 0) {
	        vl = paramopt_fetch(pop,key,&cur,&vp) ;
	        if (vl == SR_NOTFOUND) break ;
	        rs = vl ;
	        if ((rs >= 0) && (sl == vl)) {
	            m = nleadstr(sp,vp,vl) ;
	            f = (m == vl) ;
	            if (f) break ;
	        }
	    } /* end while */

	    paramopt_curend(pop,&cur) ;
	} /* end if */

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (procsufhave) */


static int procsufbegin(pip)
struct proginfo	*pip ;
{
	PARAMOPT	*pop = &pip->aparams ;

	VECPSTR		*vlp ;

	int	rs = SR_OK ;
	int	si ;
	int	c = 0 ;

	const char	*po = NULL ;


	for (si = 0 ; si < suf_overlast ; si += 1) {
	    int	f = FALSE ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(3))
	        debugprintf("main/procsufbegin: si=%u c=%u\n",si,c) ;
#endif

	    switch (si) {
	    case suf_req:
	        f = pip->have.sufreq ;
	        if (f) {
	            po = sufs[si] ;
	            vlp = (pip->sufs + si) ;
	        }
	        break ;
	    case suf_acc:
	        f = pip->have.sufacc ;
	        if (f) {
	            po = sufs[si] ;
	            vlp = (pip->sufs + si) ;
	        }
	        break ;
	    case suf_rej:
	        f = pip->have.sufrej ;
	        if (f) {
	            po = sufs[si] ;
	            vlp = (pip->sufs + si) ;
	        }
	        break ;
	    } /* end switch */

#if	CF_DEBUG
	    if (DEBUGLEVEL(3))
	        debugprintf("main/procsufbegin: si=%u f=%u\n",si,f) ;
#endif

	    if (f) {
	        int n = paramopt_countvals(pop,po) ;

#if	CF_DEBUG
	        if (DEBUGLEVEL(3))
	            debugprintf("main/procsufbegin: si=%u n=%u\n",si,n) ;
#endif

	        if (n > 0) {
	            PARAMOPT_CUR	cur ;
	            if ((rs = vecpstr_start(vlp,n,0,0)) >= 0) {
	                switch (si) {
	                case suf_req: 
	                    pip->open.sufreq = TRUE ; 
	                    break ;
	                case suf_acc: 
	                    pip->open.sufacc = TRUE ; 
	                    break ;
	                case suf_rej: 
	                    pip->open.sufrej = TRUE ; 
	                    break ;
	                } /* end switch */
	                if ((rs = paramopt_curbegin(pop,&cur)) >= 0) {
	                    int	vl ;
	                    const char	*vp ;
	                    while (rs >= 0) {
	                        vl = paramopt_fetch(pop,po,&cur,&vp) ;
	                        if (vl == SR_NOTFOUND)
	                            break ;
	                        rs = vl ;
	                        if ((rs >= 0) && (vl > 0)) {
	                            rs = vecpstr_adduniq(vlp,vp,vl) ;
	                            if (rs < INT_MAX) c += 1 ;

#if	CF_DEBUG
	                            if (DEBUGLEVEL(3) && (rs < INT_MAX))
	                                debugprintf("main/procsufbegin: "
					    "suf=%t\n",
	                                    vp,vl) ;
#endif

	                        }
	                    } /* end while */
	                    paramopt_curend(pop,&cur) ;
	                }
	                if (c > 0) {
	                    switch (si) {
	                    case suf_req:
	                        pip->f.sufreq = TRUE ;
	                        break ;
	                    case suf_acc:
	                        pip->f.sufacc = TRUE ;
	                        break ;
	                    case suf_rej:
	                        pip->f.sufrej = TRUE ;
	                        break ;
	                    } /* end switch */
	                }
	            } /* end if */
	        }
	    } /* end if */

	} /* end for */

ret0:

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	    debugprintf("main/procsufbegin: ret rs=%d c=%u\n",rs,c) ;
#endif

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (procsufbegin) */


static int procsufend(pip)
struct proginfo	*pip ;
{
	VECPSTR	*slp ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	i ;
	int	f ;


	for (i = 0 ; i < suf_overlast ; i += 1) {
	    slp = (pip->sufs + i) ;
	    f = FALSE ;
	    switch (i) {
	    case suf_req:
	        f = pip->open.sufreq ;
	        pip->open.sufreq = FALSE ;
	        break ;
	    case suf_acc:
	        f = pip->open.sufacc ;
	        pip->open.sufacc = FALSE ;
	        break ;
	    case suf_rej:
	        f = pip->open.sufrej ;
	        pip->open.sufrej = FALSE ;
	        break ;
	    } /* end switch */
	    if (f) {
	        rs1 = vecpstr_finish(slp) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	} /* end for */

	return rs ;
}
/* end subroutine (procsufend) */


/* make *parent* directories as needed */
static int mkpdirs(const char *tarfname,mode_t dm)
{
	int	rs = SR_OK ;
	int	dl ;

	const char	*dp ;

	dl = sfdirname(tarfname,-1,&dp) ;
	if (dl > 0) {
	    char	dname[MAXPATHLEN + 1] ;
	    rs = mkpath1w(dname,dp,dl) ;
	    if (rs >= 0) {
	        uc_unlink(dname) ; /* just a little added help */
	        rs = mkdirs(dname,dm) ;
	    }
	} else
	    rs = SR_NOENT ;

	return rs ;
}
/* end subroutine (mkpdirs) */



