/* main */

/* generic use front-end */
/* version %I% last-modified %G% */


#define	CF_DEBUGS	0		/* non-switchable debug print-outs */
#define	CF_DEBUG	0		/* switchable at invocation */
#define	CF_GETEXECNAME	1		/* use 'getexecname(3c)' */


/* revision history:

	= 1989-03-01, David A�D� Morano
        This subroutine was originally written. This whole program, LOGDIR, is
        needed for use on the Sun CAD machines because Sun doesn't support
        LOGDIR or LOGNAME at this time. There was a previous program but it is
        lost and not as good as this one anyway. This one handles NIS+ also.
        (The previous one didn't.)

	= 1998-06-01, David A�D� Morano
	I enhanced the program a little to print out some other user
	information besides the user's name and login home directory.

	= 1999-03-01, David A�D� Morano
	I enhanced the program to also print out effective UID and
	effective GID.

*/

/* Copyright � 1989,1998,1999 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	Synopsis:

	$ testpthread.x


*******************************************************************************/


#include	<envstandards.h>

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/utsname.h>
#include	<sys/wait.h>
#include	<limits.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<time.h>
#include	<stdlib.h>
#include	<string.h>
#include	<pwd.h>
#include	<grp.h>
#include	<netdb.h>

#include	<usystem.h>
#include	<bfile.h>
#include	<baops.h>
#include	<vecstr.h>
#include	<schedvar.h>
#include	<sbuf.h>
#include	<realname.h>
#include	<mallocstuff.h>
#include	"pwfile.h"
#include	"ipasswd.h"
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"


/* local defines */

#define	MAXARGINDEX	100
#define	MAXARGGROUPS	(MAXARGINDEX/8 + 1)

#ifndef	ENVBUFLEN
#define	ENVBUFLEN	(MAXPATHLEN + MAXNAMELEN + 1)
#endif

#ifndef	LOGNAMELEN
#define	LOGNAMELEN	32
#endif

#ifndef	DEBUGLEVEL
#define	DEBUGLEVEL(n)	(pip->debuglevel >= (n))
#endif


/* external subroutines */

extern int	cfdeci(const char *,int,int *) ;
extern int	sncpy3(char *,int,const char *,const char *,const char *) ;
extern int	matstr(const char **,const char *,int) ;
extern int	matstr2(const char **,const char *,int) ;
extern int	matstr3(const char **,const char *,int) ;
extern int	mkpath2(char *,const char *,const char *) ;
extern int	mkpath3(char *,const char *,const char *,const char *) ;
extern int	matstr(const char **,const char *,int) ;
extern int	lastlogin(char *,uid_t,time_t *,char *,char *) ;

extern int	printhelp(bfile *,const char *,const char *,const char *) ;

extern cchar	*getourenv(cchar **,cchar *) ;

extern char	*strwcpy(char *,const char *,int) ;
extern char	*timestr_logz(time_t,char *) ;
extern char	*timestr_elapsed(time_t,char *) ;


/* external variables */


/* local structures */


/* forward references */

static void	*separate(void *) ;


/* local variables */

static const char *argopts[] = {
	"VERSION",
	"VERBOSE",
	"HELP",
	"ROOT",
	"of",
	"pwfile",
	"pwifile",
	"ipwfile",
	NULL
} ;

enum argopts {
	argopt_version,
	argopt_verbose,
	argopt_help,
	argopt_root,
	argopt_of,
	argopt_pwfile,
	argopt_pwifile,
	argopt_ipwfile,
	argopt_overlast
} ;

static int	twentyseven = 27 ;


/* exported subroutines */


int main(argc,argv,envv)
int		argc ;
const char	*argv[] ;
const char	*envv[] ;
{
	struct proginfo	pi, *pip = &pi ;
	bfile		errfile ;
	bfile		outfile, *ofp = &outfile ;
	bfile		nisfile, *nfp = &nisfile ;

	int	argr, argl, aol, akl, avl ;
	int	argvalue = -1 ;
	int	maxai, pan, npa, kwi, ai, i, j, k ;
	int	rs = SR_OK ;
	int	len, c ;
	int	sl, cl, ci ;
	int	uid ;
	int	ex = EX_INFO ;
	int	fd_debug ;
	int	f_optminus, f_optplus, f_optequal ;
	int	f_extra = FALSE ;
	int	f_version = FALSE ;
	int	f_usage = FALSE ;
	int	f_help = FALSE ;
	int	f_name = FALSE ;
	int	f_self = FALSE ;

	const char	*argp, *aop, *akp, *avp ;
	const char	*pr = NULL ;
	const char	*ofname = NULL ;
	const char	*pwfname = NULL ;
	const char	*pwifname = NULL ;
	const char	*un = NULL ;
	const char	*sp, *cp, *cp2 ;
	char	argpresent[MAXARGGROUPS] ;
	char	buf[BUFLEN + 1], *bp ;
	char	nodename[NODENAMELEN + 1] ;
	char	domainname[MAXHOSTNAMELEN + 1] ;
	char	usernamebuf[LOGNAME_MAX + 1] ;

#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	proginfo_start(pip,envv,argv[0],VERSION) ;

	if ((cp = getourenv(envv,VARBANNER)) == NULL) cp = BANNER ;
	rs = proginfo_setbanner(pip,cp) ;

	if (bopen(&errfile,BFILE_STDERR,"dwca",0666) >= 0) {
	    pip->efp = &errfile ;
	    pip->f.errfile = TRUE ;
	    bcontrol(&errfile,BC_LINEBUF,0) ;
	}

/* initialize */

	pip->verboselevel = 1 ;

/* start parsing the arguments */

	for (i = 0 ; i < MAXARGGROUPS ; i += 1) argpresent[i] = 0 ;

	npa = 0 ;			/* number of positional so far */
	maxai = 0 ;
	i = 0 ;
	argr = argc - 1 ;
	while (argr > 0) {

	    argp = argv[++i] ;
	    argr -= 1 ;
	    argl = strlen(argp) ;

	    f_optminus = (*argp == '-') ;
	    f_optplus = (*argp == '+') ;
	    if ((argl > 0) && (f_optminus || f_optplus)) {

	        if (argl > 1) {

	            if (isdigit(argp[1])) {

	                if (((argl - 1) > 0) && 
	                    (cfdeci(argp + 1,argl - 1,&argvalue) < 0))
	                    goto badargval ;

	            } else {

#if	CF_DEBUGS
	                debugprintf("main: got an option\n") ;
#endif

	                aop = argp + 1 ;
	                aol = argl - 1 ;
	                akp = aop ;
	                f_optequal = FALSE ;
	                if ((avp = strchr(aop,'=')) != NULL) {

#if	CF_DEBUGS
	                    debugprintf("main: got an option key w/ a value\n") ;
#endif

	                    akl = avp - aop ;
	                    avp += 1 ;
	                    avl = aop + aol - avp ;
	                    f_optequal = TRUE ;

#if	CF_DEBUGS
	                    debugprintf("main: aol=%d avp=\"%s\" avl=%d\n",
	                        aol,avp,avl) ;

	                    debugprintf("main: akl=%d akp=\"%s\"\n",
	                        akl,akp) ;
#endif

	                } else {

	                    akl = aol ;
	                    avl = 0 ;

	                }

/* keyword match or only key letters ? */

#if	CF_DEBUGS
	                debugprintf("main: about to check for a key word match\n") ;
#endif

	                if ((kwi = matstr(argopts,akp,akl)) >= 0) {

#if	CF_DEBUGS
	                    debugprintf("main: option keyword=%w kwi=%d\n",
	                        akp,akl,kwi) ;
#endif

	                    switch (kwi) {

/* version */
	                    case argopt_version:
	                        f_version = TRUE ;
	                        if (f_optequal)
	                            goto badargextra ;

	                        break ;

/* verbose mode */
	                    case argopt_verbose:
	                        pip->verboselevel = 2 ;
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl) {

	                                rs = cfdeci(avp,avl,
	                                    &pip->verboselevel) ;

	                                if (rs < 0)
	                                    goto badargval ;

	                            }
	                        }

	                        break ;

/* program root */
	                    case argopt_root:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl)
	                                pr = avp ;

	                        } else {

	                            if (argr <= 0)
	                                goto badargnum ;

	                            argp = argv[++i] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl)
	                                pr = argp ;

	                        }

	                        break ;

	                    case argopt_help:
	                        f_help = TRUE ;
	                        break ;

/* output file name */
	                    case argopt_of:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl)
	                                ofname = avp ;

	                        } else {

	                            if (argr <= 0)
	                                goto badargnum ;

	                            argp = argv[++i] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl)
	                                ofname = argp ;

	                        }

	                        break ;

/* password file */
	                    case argopt_pwfile:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl)
	                                pwfname = avp ;

	                        } else {

	                            if (argr <= 0)
	                                goto badargnum ;

	                            argp = argv[++i] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl)
	                                pwfname = argp ;

	                        }

	                        break ;

/* inverse password ('ipasswd') file */
	                    case argopt_pwifile:
	                    case argopt_ipwfile:
	                        if (f_optequal) {

	                            f_optequal = FALSE ;
	                            if (avl)
	                                pwifname = avp ;

	                        } else {

	                            if (argr <= 0)
	                                goto badargnum ;

	                            argp = argv[++i] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl)
	                                pwifname = argp ;

	                        }

	                        break ;

/* handle all keyword defaults */
	                    default:
	                        ex = EX_USAGE ;
	                        f_usage = TRUE ;
	                        bprintf(pip->efp,
	                            "%s: option (%s) not supported\n",
	                            pip->progname,akp) ;

	                        goto badargextra ;

	                    } /* end switch */

	                } else {

#if	CF_DEBUGS
	                    debugprintf("main: got an option key letter\n") ;
#endif

	                    while (akl--) {

#if	CF_DEBUGS
	                        debugprintf("main: option key letters\n") ;
#endif

	                        switch ((int) *akp) {

/* debug */
	                        case 'D':
	                            pip->debuglevel = 1 ;
	                            if (f_optequal) {

	                                f_optequal = FALSE ;
	                                if (avl > 0) {

	                                    rs = cfdeci(avp,avl,
	                                        &pip->debuglevel) ;

	                                    if (rs < 0)
	                                        goto badargval ;

	                                }
	                            }

	                            break ;

/* version */
	                        case 'V':
	                            f_version = TRUE ;
	                            break ;

	                        case 'n':
	                            f_name = TRUE ;
	                            break ;

/* alternate passwd file */
	                        case 'p':
	                            if (argr <= 0)
	                                goto badargnum ;

	                            argp = argv[++i] ;
	                            argr -= 1 ;
	                            argl = strlen(argp) ;

	                            if (argl)
	                                pwfname = argp ;

	                            break ;

/* quiet mode */
	                        case 'q':
	                            pip->f.quiet = TRUE ;
	                            break ;

/* verbose mode */
	                        case 'v':
	                            pip->verboselevel = 2 ;
	                            if (f_optequal) {

	                                f_optequal = FALSE ;
	                                if (avl > 0) {

	                                    rs = cfdeci(avp,avl,
	                                        &pip->verboselevel) ;

	                                    if (rs < 0)
	                                        goto badargval ;

	                                }
	                            }

	                            break ;

	                        case '?':
	                            f_usage = TRUE ;
	                            break ;

	                        default:
	                            ex = EX_USAGE ;
	                            f_usage = TRUE ;
	                            bprintf(pip->efp,
	                                "%s: unknown option - %c\n",
	                                pip->progname,*aop) ;

	                        } /* end switch */

	                        akp += 1 ;

	                    } /* end while */

	                } /* end if (individual option key letters) */

	            } /* end if (digits as argument or not) */

	        } else {

/* we have a plus or minux sign character alone on the command line */

	            if (i < MAXARGINDEX) {

	                BASET(argpresent,i) ;
	                maxai = i ;
	                npa += 1 ;	/* increment position count */

	            }

	        } /* end if */

	    } else {

	        if (i < MAXARGINDEX) {

#if	CF_DEBUGS
	            debugprintf("main: pos arg=>%s<\n",argv[i]) ;
#endif

	            BASET(argpresent,i) ;
	            maxai = i ;
	            npa += 1 ;

	        } else {

	            if (! f_extra) {

	                f_extra = TRUE ;
	                ex = EX_USAGE ;
	                bprintf(pip->efp,"%s: extra arguments specified\n",
	                    pip->progname) ;

	            }
	        }

	    } /* end if (key letter/word or positional) */

	} /* end while (all command line argument processing) */


#if	CF_DEBUG
	if (pip->debuglevel > 1)
	    debugprintf("main: finished parsing arguments\n") ;
#endif

	if (f_version)
	    bprintf(pip->efp,"%s: version %s\n",
	        pip->progname,VERSION) ;

	if (f_usage)
	    goto usage ;

	if (f_version)
	    goto retearly ;

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: debuglevel=%u\n",
	        pip->progname,pip->debuglevel) ;

#if	CF_DEBUG
	if (pip->debuglevel > 1)
	    debugprintf("main: special debugging turned on\n") ;
#endif


/* get the program root */

	if (pr == NULL) {

	    pr = getenv(VARPROGRAMROOT1) ;

	    if (pr == NULL)
	        pr = getenv(VARPROGRAMROOT2) ;

	    if (pr == NULL)
	        pr = getenv(VARPROGRAMROOT3) ;

/* try to see if a path was given at invocation */

	    if ((pr == NULL) && (pip->progdname != NULL))
	        proginfo_rootprogdname(pip) ;

/* do the special thing */

#if	CF_GETEXECNAME && defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
	    if ((pr == NULL) && (pip->pr == NULL)) {

	        const char	*pp ;


	        pp = getexecname() ;

	        if (pp != NULL)
	            proginfo_rootexecname(pip,pp) ;

	    }
#endif /* SOLARIS */

	} /* end if (getting a program root) */

	if (pip->pr == NULL) {

	    if (pr == NULL)
	        pr = PROGRAMROOT ;

	    proginfo_setprogroot(pip,pr,-1) ;

	}


/* program search name */

	proginfo_setsearchname(pip,VARSEARCHNAME,SEARCHNAME) ;


#if	CF_DEBUG
	if (DEBUGLEVEL(4))
	    debugprintf("main: pr=%s\n",pip->pr) ;
#endif

	if (pip->debuglevel > 0) {

	    bprintf(pip->efp,"%s: pr=%s\n",
	        pip->progname,pip->pr) ;

	    bprintf(pip->efp,"%s: searchname=%s\n",
	        pip->progname,pip->searchname) ;

	}


/* help file */

	if (f_help)
	    goto help ;


/* some initialization */

	if (pip->tmpdname == NULL)
	    pip->tmpdname = getenv("TMPDIR") ;

	if (pip->tmpdname == NULL)
	    pip->tmpdname = TMPDNAME ;




	if ((ofname != NULL) && (ofname[0] != '\0'))
	    rs = bopen(ofp,ofname,"wct",0666) ;

	else
	    rs = bopen(ofp,BFILE_STDOUT,"dwct",0666) ;

	if (rs < 0)
	    goto badoutopen ;

#if	CF_DEBUG
	if (DEBUGLEVEL(4))
	    debugprintf("main: done w/ opening output \n") ;
#endif



	{
		pthread_t	tid ;

		void	*rp = NULL ;


		uptcreate(&tid,NULL,separate,NULL) ;

		sleep(4) ;

		printf("this is from the parent\n") ;

		uptjoin(tid,&rp) ;

		printf("r=%d\n",(*((int *) rp))) ;

	} /* end block */



/* we are done */
done:
ret2:
	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: program finishing\n",
	        pip->progname) ;

	bclose(ofp) ;


/* early return thing */
retearly:
ret1:
	bclose(pip->efp) ;

ret0:
	proginfo_finish(pip) ;

	return ex ;

/* the information type thing */
usage:
	bprintf(pip->efp,
	    "%s: USAGE> %s [username|- [keyword(s) ...]]\n",
	    pip->progname,pip->progname) ;

	bprintf(pip->efp,"%s: \t[-?V] [-Dv]\n",
	    pip->progname) ;

	goto retearly ;

/* print out some help */
help:
	printhelp(NULL,pip->pr,pip->searchname,HELPFNAME) ;

	goto retearly ;

/* the bad things */
badargnum:
	bprintf(pip->efp,"%s: not enough arguments specified\n",
	    pip->progname) ;

	goto badarg ;

badargextra:
	bprintf(pip->efp,"%s: no value associated with this option key\n",
	    pip->progname) ;

	goto badarg ;

badargval:
	bprintf(pip->efp,"%s: bad argument value was specified\n",
	    pip->progname) ;

	goto badarg ;

/* bad arguments come here */
badarg:
	ex = EX_USAGE ;

	goto retearly ;

badoutopen:
	ex = EX_CANTCREAT ;
	bprintf(pip->efp,"%s: could not open the output file (%d)\n",
	    pip->progname,rs) ;

	goto badret ;

/* error types of returns */
badret:
	bclose(pip->efp) ;

	goto retearly ;
}
/* end subroutine (main) */



/* LOCAL SUBROUTINES */



static void	*separate(argp)
void	*argp ;
{


	printf("this is from the thread\n") ;

#ifdef	COMMENT
	uptexit(NULL) ;
#endif

	return &twentyseven ;
}



