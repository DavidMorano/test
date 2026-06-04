/* testcomsat_main (testcomsat) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* program to test COMSAT */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* run-time debug switch */

/* revision history:

	- 2005-05-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:

	Synopsis:
	$ testcomsat [-mu <user>] [-mo <off>] [<host(s)> ...] [-v[=n]] [-V]

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<stropts.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<netdb.h>
#include	<ctime>
#include	<cstddef>
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<getproto.h>
#include	<getpf.h>
#include	<getaf.h>
#include	<baops.h>
#include	<keyopt.h>
#include	<vecstr.h>
#include	<bfile.h>
#include	<userinfo.h>
#include	<inetaddr.h>
#include	<netorder.h>
#include	<hostinfo.h>
#include	<hostaddr.h>
#include	<sockaddress.h>
#include	<inetaddrx.h>
#include	<timestr.h>
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"config.h"
#include	"defs.h"
#include	"comsatmsg.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#define	MAXARGINDEX	100
#define	NARGGROUPS	(MAXARGINDEX/8 + 1)

#ifndef	USERBUFLEN
#define	USERBUFLEN	(NODENAMELEN + (2 * 1024))
#endif

#define	COMSATMSGLEN	(MAXPATHLEN+USERNAMELEN+32)

#define	PREPNAME_MAGIC	0x17161524

#ifndef	LOCALHOST
#define	LOCALHOST	"localhost"
#endif

#define	DEFPORTSPEC	"biff"

#ifndef	PI
#define	PI		proginfo
#endif

#ifndef	LI
#define	LI		locinfo
#endif

#ifndef	PI
#define	PI		proginfo
#endif

#ifndef	LI
#define	LI		locinfo
#endif

#ifndef	SA
#define	SA		sockaddress
#endif


/* external subroutines */

extern int	proginfo_setpiv(PI *,cchar *,const pivars *) ;
extern int	printhelp(void *,cchar *,cchar *,cchar *) ;


/* external variables */

extern char	hostaddrinfo_makedate[] ;


/* local structures */

LI_fl {
	uint		dummy:1 ;
} ;

LI {
	locinfo_fl	have, f, changed, final ;
	locinfo_fl	init, open ;
	vecstr		stores ;
	PI	*pip ;
	cchar	*muname ;	/* mail-username */
	cchar	*portspec ;	/* port-specification */
	char		*msgbuf ;
	int		msglen ;
	int		to ;
	int		af ;		/* address-family */
	int		mo ;		/* mail-offset */
} ;

#ifdef	COMMENT
struct prepname {
	cchar		*hostname ;
	int		hostnamelen ;
	ulong		magval ;
	int		f_alloc ;
} ;
#endif /* COMMENT */


/* forward references */

local int	usage(PI *) ;

local int	locinfo_start(LI *,PI *) ;
local int	locinfo_mkmsg(LI *) ;
local int	locinfo_setentry(LI *,cchar **,
			cchar *,int) ;
local int	locinfo_sendmsg(LI *,ADDRINFO *) ;
local int	locinfo_finish(LI *) ;

local int	procname(PI *,bfile *,cchar *) ;

#ifdef	COMMENT
local int	prepname_start(struct prepname *,cchar *) ;
local int	prepname_finish(struct prepname *) ;
#endif


/* local variables */

static cchar *argopts[] = {
	"ROOT",
	"TMPDIR",
	"VERSION",
	"VERBOSE",
	"HELP",
	"sn",
	"af",
	"of",
	"ef",
	"to",
	"mu",
	"mo",
	nullptr
} ;

enum argopts {
	argopt_root,
	argopt_tmpdir,
	argopt_version,
	argopt_verbose,
	argopt_help,
	argopt_sn,
	argopt_af,
	argopt_of,
	argopt_ef,
	argopt_to,
	argopt_mu,
	argopt_mo,
	argopt_overlast
} ;

constexpr pivars	initvars = {
	VARPROGRAMROOT1,
	VARPROGRAMROOT2,
	VARPROGRAMROOT3,
	PROGRAMROOT,
	VARPRLOCAL
} ;

constexpr mapex_map	mapexs[] = {
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


/* exported variables */


/* exported subroutines */

int main(argc,argv,envv)
int	argc ;
char	*argv[] ;
char	*envv[] ;
{
	PI	pi, *pip = &pi ;
	LI	li, *lip = &li ;

	USERINFO	u ;

	keyopt		akopts ;

	bfile		errfile ;
	bfile		outfile, *ofp = &outfile ;

	int	argr, argl, aol, akl, avl, kwi ;
	int	ai, ai_max, ai_pos ;
	int	pan ;
	int	rs, rs1 ;
	int	v ;
	int	ex = EX_INFO ;
	int	f_optplus, f_optminus, f_optequal ;
	int	f_version = false ;
	int	f_usage = false ;
	int	f_help = false ;
	int	f ;

	cchar	*argp, *aop, *akp, *avp ;
	cchar	*argval = nullptr ;
	char	argpresent[NARGGROUPS] ;
	char	userbuf[USERBUFLEN + 1] ;
	cchar	*pr = nullptr ;
	cchar	*sn = nullptr ;
	cchar	*afname = nullptr ;
	cchar	*ofname = nullptr ;
	cchar	*efname = nullptr ;
	cchar	*afspec = nullptr ;
	cchar	*portspec = nullptr ;
	cchar	*muname = nullptr ;
	cchar	*moffset = nullptr ;
	cchar	*cp ;

#if	CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

	rs = proginfo_start(pip,envv,argv[0],VERSION) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badprogstart ;
	}

	if ((cp = getenv(VARBANNER)) == nullptr) cp = BANNER ;
	proginfo_setbanner(pip,cp) ;

/* miscellaneous early stuff */

	pip->verboselevel = 1 ;

	pip->lip = lip ;
	rs = locinfo_start(lip,pip) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badlocstart ;
	}

/* start parsing the arguments */

	rs = keyopt_start(&akopts) ;
	pip->open.akopts = (rs >= 0) ;

/* parse arguments */

	for (ai = 0 ; ai < NARGGROUPS ; ai += 1)
	    argpresent[ai] = 0 ;

	ai = 0 ;
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
	    if ((argl > 1) && (f_optplus || f_optminus)) {

	        if (isdigit(argp[1])) {

	            argval = (argp + 1) ;

	        } else if (argp[1] == '-') {

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

/* do we have a keyword match or should we assume only key letters? */

	            if ((kwi = matostr(argopts,2,akp,akl)) >= 0) {

	                switch (kwi) {

/* program root */
	                case argopt_root:
	                    if (f_optequal) {
	                        f_optequal = false ;
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

/* temporary directory */
	                case argopt_tmpdir:
	                    if (f_optequal) {
	                        f_optequal = false ;
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

/* version */
	                case argopt_version:
	                    f_version = true ;
	                    if (f_optequal)
	                        rs = SR_INVALID ;
	                    break ;

/* verbose mode */
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

	                case argopt_help:
	                    f_help = true ;
	                    break ;

/* program search name */
	                case argopt_sn:
	                    if (f_optequal) {
	                        f_optequal = false ;
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

/* argument list file */
	                case argopt_af:
	                    if (f_optequal) {
	                        f_optequal = false ;
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
	                        f_optequal = false ;
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
	                        f_optequal = false ;
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

/* lookup-timeout */
	                case argopt_to:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl) {
	                        rs = cfdecti(argp,argl,&v) ;
	                        lip->to = v ;
	                    }
	                    break ;

/* mail-username */
	                case argopt_mu:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl)
				muname = argp ;
	                    break ;

/* mail-offset */
	                case argopt_mo:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl)
				moffset = argp ;
	                    break ;

/* handle all keyword defaults */
	                default:
	                    rs = SR_INVALID ;
	                    break ;

	                } /* end switch */

	            } else {

	                while (akl--) {
			    cint	kc = MKCHAR(*akp) ;

	                    switch (kc) {

/* debug */
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
	                        f_version = true ;
	                        break ;

	                    case 'Q':
	                        pip->f.quiet = true ;
	                        break ;

	                    case 'a':
	                    case 'f':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            afspec = argp ;
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
	                            rs = keyopt_loads(&akopts,argp,argl) ;
	                        break ;

	                    case 'q':
	                        pip->verboselevel = 0 ;
	                        break ;

/* port specification */
	                    case 'p':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            portspec = argp ;
	                        break ;

/* mail user-name */
	                    case 'u':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            muname = argp ;
	                        break ;
/* verbose */
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

	                    case '?':
	                        f_usage = true ;
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

	        } /* end if (digits as argument or not) */

	    } else {

	        if (ai >= MAXARGINDEX)
	            break ;

	        BASET(argpresent,ai) ;
	        ai_max = ai ;

	    } /* end if (key letter/word or positional) */

	    ai_pos = ai ;

	} /* end while (all command line argument processing) */

	if (efname == nullptr) efname = getenv(VARERRORFNAME) ;
	if (efname == nullptr) efname = BFILE_STDERR ;
	if ((rs1 = bopen(&errfile,efname,"wca",0666)) >= 0) {
	    pip->efp = &errfile ;
	    pip->open.errfile = true ;
	    bcontrol(&errfile,BC_SETBUFLINE,true) ;
	}

	if (rs < 0)
	    goto badarg ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: debuglevel=%u\n",pip->debuglevel) ;
#endif

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: debuglevel=%u\n",
	        pip->progname,pip->debuglevel) ;

	if (f_version)
	    bprintf(pip->efp,"%s: version %s\n",
	        pip->progname,VERSION) ;

/* initialize some other common stuff */

	rs = proginfo_setpiv(pip,pr,&initvars) ;

	if (rs >= 0)
	    rs = proginfo_setsearchname(pip,VARSEARCHNAME,sn) ;

	if (rs < 0) {
	    ex = EX_USAGE ;
	    goto retearly ;
	}

	if (pip->debuglevel > 0) {
	    bprintf(pip->efp,"%s: pr=%s\n", pip->progname, pip->pr) ;
	    bprintf(pip->efp,"%s: sn=%s\n", pip->progname, pip->searchname) ;
	}

/* help file */

	if (f_usage)
	    usage(pip) ;

	if (f_help)
	    printhelp(nullptr,pip->pr,pip->searchname,HELPFNAME) ;

	if (f_version || f_help || f_usage)
	    goto retearly ;


	ex = EX_OK ;

/* check arguments */

	if ((afspec != nullptr) && (afspec[0] != '\0')) {
	    rs = getaf(afspec,-1) ;
	    lip->af = rs ;
	}

	if (rs < 0) {
	    ex = EX_USAGE ;
	    goto badaddrspace ;
	}

/* user */

	rs = userinfo(&u,userbuf,USERBUFLEN,nullptr) ;
	if (rs < 0) {
	    ex = EX_NOUSER ;
	    goto baduser ;
	}

	pip->nodename = u.nodename ;
	pip->domainname = u.domainname ;
	pip->username = u.username ;
	pip->logid = u.logid ;
	pip->pid = u.pid ;

/* get a TMPDIR */

	if (pip->tmpdname == nullptr) pip->tmpdname = getenv(VARTMPDNAME) ;
	if (pip->tmpdname == nullptr) pip->tmpdname = TMPDNAME ;

/* sort out the arguments and apply defaults */

	if (portspec == nullptr) portspec = DEFPORTSPEC ;

	if (muname == nullptr) muname = u.username ;

	lip->portspec = portspec ;
	lip->muname = muname ;

	if ((moffset != nullptr) && (moffset[0] != '\0')) {
	    rs = cfdeci(moffset,-1,&v) ;
	    lip->mo = v ;
	}

	if (lip->mo < 0) rs = SR_INVALID ;

	if (rs >= 0) rs = locinfo_mkmsg(lip) ;

	if (rs < 0) goto badarg ;

/* go */

	if ((ofname == nullptr) || (ofname[0] == '\0') ||
	    (ofname[0] == '-')) ofname = BFILE_STDOUT ;
	rs = bopen(ofp,ofname,"wct",0666) ;
	if (rs < 0) {
	    ex = EX_CANTCREAT ;
	    bprintf(pip->efp,"%s: output unavailable (%d)\n",
	        pip->progname,rs) ;
	    goto badoutopen ;
	}

/* process the arguments */

	pan = 0 ;

	for (ai = 1 ; ai < argc ; ai += 1) {

	    f = (ai <= ai_max) && BATST(argpresent,ai) ;
	    f = f || ((ai > ai_pos) && (argv[ai] != nullptr)) ;
	    if (! f) continue ;

	    cp = argv[ai] ;
	    pan += 1 ;
	    rs = procname(pip,ofp,cp) ;
	    if (rs < 0)
	        break ;

	} /* end for (processing positional arguments) */

	if ((rs >= 0) && (afname != nullptr) && (afname[0] != '\0')) {
	    bfile	argfile ;

	    if (strcmp(afname,"-") == 0) afname = BFILE_STDIN ;
	    rs = bopen(&argfile,afname,"r",0666) ;
	    if (rs >= 0) {
	        int	len ;
	        char	linebuf[LINEBUFLEN + 1] ;

	        while ((rs = breadln(&argfile,linebuf,LINEBUFLEN)) > 0) {
	            len = rs ;

	            if (linebuf[len - 1] == '\n') len -= 1 ;
	            linebuf[len] = '\0' ;

	            cp = linebuf ;
	            if ((cp[0] == '\0') || (cp[0] == '#')) continue ;

	            pan += 1 ;
	    	    rs = procname(pip,ofp,cp) ;

	            if (rs < 0) {
	                bprintf(pip->efp,
	                    "%s: error (%d) in file=%s\n",
	                    pip->progname,rs,cp) ;
	                break ;
	            }

	        } /* end while (reading lines) */

	        bclose(&argfile) ;
	    } else {

	        if (! pip->f.quiet) {
	            bprintf(pip->efp,
	                "%s: inaccessible argument list file (%d)\n",
	                pip->progname,rs) ;
	            bprintf(pip->efp,"%s: \targfile=%s\n",
	                pip->progname,afname) ;
	        }

	    } /* end if */

	} /* end if (processing file argument file list) */

	if ((rs >= 0) && (pan == 0)) {

	    cp = "-" ;
	    pan += 1 ;
	    rs = procname(pip,ofp,cp) ;

	} /* end if (processing requests) */

	bclose(ofp) ;

done:
badoutopen:
	if ((rs < 0) && (ex == EX_OK)) {
	    switch (rs) {

	    case SR_INVALID:
	        ex = EX_USAGE ;
	        if (! pip->f.quiet)
	            bprintf(pip->efp,"%s: invalid query (%d)\n",
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

/* finish up */
baduser:
badaddrspace:
retearly:
	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: exiting ex=%u (%d)\n",
	        pip->progname,ex,rs) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: exiting ex=%u (%d)\n",ex,rs) ;
#endif

	if (pip->efp != nullptr) {
	    bclose(pip->efp) ;
	    pip->efp = nullptr ;
	}

	if (pip->open.akopts) {
	    pip->open.akopts = false ;
	    keyopt_finish(&akopts) ;
	}

	locinfo_finish(lip) ;

badlocstart:
	proginfo_finish(pip) ;
	proginfo_finish(pip) ;

ret0:
badprogstart:

#if	CF_DEBUG
	debugclose() ;
#endif

	return ex ;

/* bad stuff */
badarg:
	ex = EX_USAGE ;
	bprintf(pip->efp,"%s: invalid argument(s) specified (%d)\n",
	    pip->progname,rs) ;
	usage(pip) ;
	goto retearly ;

}
/* end subroutine (main) */


/* local subroutines */


local int usage(pip)
PI	*pip ;
{
	int	rs ;
	int	wlen = 0 ;


	rs = bprintf(pip->efp,
	    "%s: USAGE> %s [-u <mu>] [-mo <mo>] [<host(s)> ...]\n",
	    pip->progname,pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-Q] [-D] [-v[=<n>]] [-HELP] [-V]\n",
	    pip->progname) ;

	wlen += rs ;
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (usage) */


local int locinfo_start(lip,pip)
LI	*lip ;
PI	*pip ;
{
	int	rs ;


	if (lip == nullptr)
	    return SR_FAULT ;

	memclear(lip) ;
	lip->pip = pip ;
	lip->to = -1 ;
	lip->af = AF_UNSPEC ;

	rs = vecstr_start(&lip->stores,0,0) ;

	return rs ;
}
/* end subroutine (locinfo_start) */


local int locinfo_finish(lip)
LI	*lip ;
{
	int	rs = SR_OK ;
	int	rs1 ;


	if (lip == nullptr)
	    return SR_FAULT ;

	if (lip->msgbuf != nullptr) {
	    uc_free(lip->msgbuf) ;
	    lip->msgbuf = nullptr ;
	}

	rs1 = vecstr_start(&lip->stores,0,0) ;
	if (rs >= 0) rs = rs1 ;

	return rs ;
}
/* end subroutine (locinfo_finish) */

local int locinfo_mkmsg(LI *lip) noex {
	PI	*pip = lip->pip ;
	struct comsatmsg_mailoff	m0{} ;
	cint	msglen = COMSATMSGLEN ;
	int	rs = SR_OK ;
	int	len = 0 ;
	char	msgbuf[COMSATMSGLEN+1] ;

	strwcpy(m0.username,lip->muname,USERNAMELEN) ;
	m0.offset = lip->mo ;

	rs = comsatmsg_mailoff(&m0,0,msgbuf,msglen) ;
	len = rs ;
	if (rs >= 0) {
	    char	*p ;
	    int		size = len ;
	    if ((rs = uc_malloc(size,&p)) >= 0) {
		memcpy(p,msgbuf,len) ;
		lip->msgbuf = p ;
		lip->msglen = len ;
	    }
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) {
	debugprintf("locinfo_mkmsg: msg=>%t<\n",lip->msgbuf,lip->msglen) ;
	debugprintf("locinfo_mkmsg: ret rs=%d len=%u\n",rs,len) ;
	}
#endif

	return (rs >= 0) ? len : rs ;
}
/* end subroutine (locinfo_mkmsg) */


int locinfo_setentry(lip,epp,vp,vl)
LI	*lip ;
cchar	**epp ;
cchar	vp[] ;
int		vl ;
{
	int	rs = SR_OK ;
	int	len = 0 ;


	if (lip == nullptr) return SR_FAULT ;
	if (epp == nullptr) return SR_FAULT ;

	if (! lip->open.stores) {
	    rs = vecstr_start(&lip->stores,4,0) ;
	    lip->open.stores = (rs >= 0) ;
	}

	if (rs >= 0) {
	    int	oi = -1 ;

	    if (*epp != nullptr) oi = vecstr_findaddr(&lip->stores,*epp) ;

	    if (vp != nullptr) {
	        len = strnlen(vp,vl) ;
	        rs = vecstr_store(&lip->stores,vp,len,epp) ;
	    } else
		*epp = nullptr ;

	    if ((rs >= 0) && (oi >= 0))
	        vecstr_del(&lip->stores,oi) ;

	} /* end if */

	return (rs >= 0) ? len : rs ;
}
/* end subroutine (locinfo_setentry) */


local int locinfo_sendmsg(lip,aip)
LI	*lip ;
ADDRINFO	*aip ;
{
	PI	*pip = lip->pip ;
	SOCKADDR	*sap ;
	cint	to = lip->to ;
	int		rs ;
	int		flags = 0 ;
	int		sal ;
	int		fd = -1 ;

	sap = aip->ai_addr ;
	sal = aip->ai_addrlen ;

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) 
	    debugaddrprint("locinfo_sendmsg: ",sap) ;
#endif

	rs = u_socket(aip->ai_family,aip->ai_socktype,aip->ai_protocol) ;
	if (rs >= 0) {
	    int	fd = rs ;

	    rs = u_sendto(fd,lip->msgbuf,lip->msglen,flags,sap,sal) ;

	    u_close(fd) ;
	} /* end if */

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) 
	debugprintf("locinfo_sendmsg: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (locinfo_sendmsg) */

local int procname(PI *pip,bfile *ofp,cchar *hostname) noex {
	LI	*lip = pip->lip ;
	ADDRINFO	hint{} ;
	ADDRINFO	*aip ;
	HOSTADDR	ha ;
	cint	proto = IPPROTO_UDP ;
	int		rs ;
	int		rs1 ;
	cchar	*hn ;
	cchar	*ps ;

	if (hostname == nullptr) return SR_FAULT ;

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	    debugprintf("procname: hostname=%s\n",hostname) ;
#endif

	if ((hostname[0] == '\0') || (hostname[0] == '-'))
	    hostname = LOCALHOST ;

	if (pip->debuglevel > 0) {
	    bprintf(pip->efp,"%s: host=%s\n",
	        pip->progname,hostname) ;
	}
	/* prepare hints */
	hint.ai_protocol = proto ;
	if (lip->af >= 0) {
	    int pf = getpf(lip->af) ;
	    if (pf >= 0)
	        hint.ai_family = pf ;
	}

#if	CF_DEBUG
	debugprintf("dialudp: af=%u pf=%u\n",lip->af,hint.ai_family) ;
#endif

/* do the spin */

	hn = hostname ;
	ps = lip->portspec ;

	if ((rs = hostaddr_start(&ha,hn,ps,&hint)) >= 0) {
	    HOSTADDR_CUR	cur ;

	    if ((rs = hostaddr_curbegin(&ha,&cur)) >= 0) {
		int	rs1 ;
		int	c = 0 ;

	        while ((rs1 = hostaddr_enum(&ha,&cur,&aip)) >= 0) {

#if	CF_DEBUG
		    debugprintf("dialudp: trying proto=%u\n",
			aip->ai_protocol) ;
#endif

		   if ((aip->ai_protocol == 0) ||
	               (aip->ai_protocol == proto)) {

	                c += 1 ;
	                rs = locinfo_sendmsg(lip,aip) ;
	                if (rs >= 0)
	                    break ;

		    } /* end if (protocol match) */

	        } /* end while */

		if ((rs >= 0) && (c == 0)) rs = SR_HOSTUNREACH ;

#if	CF_DEBUG
		debugprintf("dialudp: done rs=%d c=%u\n",rs,c) ;
#endif

	        hostaddr_curend(&ha,&cur) ;
	    } /* end if (cursor) */

	    hostaddr_finish(&ha) ;
	} /* end if (initialized host addresses) */

ret0:

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	    debugprintf("procname: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (procname) */


#ifdef	COMMENT

local int prepname_start(ep,name)
struct prepname	*ep ;
cchar	name[] ;
{
	int	rs = SR_OK ;
	int	nl ;
	int	f = false ;

	if (ep == nullptr) return SR_FAULT ;
	if (name == nullptr) return SR_FAULT ;
	if (name[0] == '\0') return SR_INVALID ;

	memclear(ep) ;
	nl = strlen(name) ;
	while ((nl > 0) && (name[nl - 1] == '.')) {
	    f = true ;
	    nl -= 1 ;
	}

	ep->hostname = (char *) name ;
	if (f) {
	    cchar	*ccp ;
	    rs = uc_mallocstrw(name,nl,&ccp) ;
	    if (rs >= 0) {
	        ep->f_alloc = true ;
	        ep->hostname = ccp ;
	        ep->hostnamelen = nl ;
	    }
	}

	if (rs >= 0)
	    ep->magval = PREPNAME_MAGIC ;

#if	CF_DEBUG
	debugprintf("prepname_start: ret rs=%d f=%u f_a=%u\n",
	    rs,f, ep->f_alloc) ;
#endif

	return (rs >= 0) ? f : rs ;
}
/* end if (prepname_start) */

local int prepname_finish(prepname *ep) noex {
#if	CF_DEBUG
	debugprintf("prepname_finish: entered\n") ;
#endif
	if (ep == nullptr) return SR_FAULT ;
#if	CF_DEBUG
	debugprintf("prepname_finish: magic?\n") ;
#endif
	if (ep->magval != PREPNAME_MAGIC) return SR_NOTOPEN ;
#if	CF_DEBUG
	debugprintf("prepname_finish: f_a=%u\n", ep->f_alloc) ;
#endif

	if (ep->f_alloc && (ep->hostname != nullptr)) {
	    uc_free(ep->hostname) ;
	    ep->hostname = nullptr ;
	}

#if	CF_DEBUG
	debugprintf("prepname_finish: ret\n") ;
#endif

	ep->f_alloc = false ;
	ep->hostname = nullptr ;
	ep->magval = 0 ;
	return SR_OK ;
} /* end if (prepname_finish) */

#endif /* COMMENT */

#if	CF_DEBUG
local int debugaddrprint(cchar *s,SOCKADDR *sap) noex {
	SA	*ap = (SA *) sap ;
	int	rs = SR_OK ;
	int	af = 0 ;
	int	port = 0 ;
	char	addr[INETXADDRLEN+1] ;
	char	addrstr[INETX_ADDRSTRLEN+1] ;
	addrstr[0] = '\0' ;
	if (rs >= 0) {
	    rs = sockaddress_getaf(ap) ;
	    af = rs ;
	}
	debugprintf("%s af=%u\n",s,af) ;
	if (rs >= 0) {
	    rs = sockaddress_getport(ap) ;
	    port = rs ;
	}
	debugprintf("%s port=%u\n",s,port) ;
	if (rs >= 0)
	    rs = sockaddress_getaddr(ap,addr,INETXADDRLEN) ;
	if (rs >= 0) {
	    rs = sninetaddr(addrstr,INETX_ADDRSTRLEN,af,addr) ;
	    debugprintf("%s addr=%s\n",s,addrstr) ;
	}
	return rs ;
} /* end subroutine (debugaddrprint) */
#endif /* (CF_DEBUG || CF_DEBUG) */



