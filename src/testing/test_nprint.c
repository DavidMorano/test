/* main (test_nprint) */


#define	CF_ORPHANED	0


/* revision history:

	= David A.D. Morano, February 88


*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/************************************************************************

	Synopsis:
	$ daytime [mailfile] [-t offset] [-sV] [offset]


*************************************************************************/


#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<time.h>
#include	<pwd.h>
#include	<stdio.h>

#include	<bfile.h>
#include	<localmisc.h>


/* local program defines */

#define		VERSION		"1"
#define		NPARG		2

#define		SLEEP_TIME	7

#define		MAIL_TICS	3

#define		FULL_TICS	100

#define		DEF_OFF		(5*60)	/* default offset 5 minutes */
#define		SPOOLDIR	"/var/spool/mail"

#define		N		((char *) 0)

#define		MAILLEN		100

#define		S_NOMAIL	0
#define		S_MAIL		1
#define		S_MAILDONE	2



/* external subroutines */

extern struct passwd	*getpwuid() ;


/* external variables */





int main(argc,argv)
int	argc ;
char	*argv[] ;
{
	bfile	errfile, *efp = &errfile ;

	struct passwd	*pwsp ;
	struct ustat	ss, *sp = &ss ;

	pid_t	ppid, pid ;
	pid_t	pgid ;

	long	clock, offset ;

	int	tic = 0, len, mail_tics = MAIL_TICS ;
	int	uid ;
	int	pan, i ;
	int	argl, aol, state = S_NOMAIL ;
	int	wrs, werrno, rs ;
	int	f_debug = FALSE ;
	int	f_usage = FALSE ;
	int	f_orphaned = FALSE ;
	int	f_statdisplay = FALSE ;

	char	*progname, *argp, *aop ;
	char	mailbuf[MAILLEN], *mailfile = N ;
	char	login_name[L_cuserid] ;
	char	*buf, dbuf[100] ;


	progname = argv[0] ;
	if (bopen(efp,BFILE_STDERR,"wca",0666) >= 0)
		bcontrol(efp,BC_LINEBUF,0) ;


/* set default parameters */

	offset = DEF_OFF ;


/* get the command line arguments */

	pan = 0 ;			/* number of positional so far */
	i = 1 ;
	argc -= 1 ;
	while (argc > 0) {

	    argp = argv[i++] ;
	    argc -= 1 ;
	    argl = strlen(argp) ;

	    if ((argl > 0) && (*argp == '-')) {

	        if (argl > 1) {

	            if (isdigit(argp[1])) {

	                if (cfdec(argp + 1,argl - 1,&offset)) goto badarg ;

	            } else {

	                aop = argp ;
	                aol = argl ;
	                while (--aol) {

	                    aop += 1 ;
	                    switch (*aop) {

	                    case 'D':
	                        f_debug = TRUE ;
	                        break ;

	                    case 'V':
	                        bprintf(efp,"%s: version %s\n",
	                            progname,VERSION) ;

	                        break ;

	                    case 's':
	                        f_statdisplay = TRUE ;
	                        break ;

	                    case 't':
	                        if (argc <= 0) goto not_enough ;

	                        argp = argv[i++] ;
	                        argc -= 1 ;
	                        argl = strlen(argp) ;

	                        if (cfdec(argp,argl,&offset) != OK)
	                            goto badarg ;

	                        break ;

	                    default:
	                        bprintf(efp,"%s: unknown option - %c\n",
	                            progname,*aop) ;

	                    case '?':
	                        f_usage = TRUE ;

	                    } /* end switch */

	                } /* end while */
	            }

	        } else {

	            pan += 1 ;	/* increment position count */

	        } /* end if */

	    } else {

	        if (pan < NPARG) {

	            switch (pan) {

	            case 0:
	                if (strlen(argp)) mailfile = argp ;

	                break ;

	            case 1:
	                if (cfdec(argp,argl,&offset) != OK) goto badarg ;

	                break ;

	            default:
	                break ;

	            } /* end switch */

	            pan += 1 ;

	        } else {

	            bprintf(efp,"%s: extra arguments ignored\n",
	                progname) ;

	        }

	    } /* end if */

	} /* end while */

/* done with arguments */

	if (f_debug) {

	    bprintf(efp,"SD=%d offset=%d\n",f_statdisplay,offset) ;

	}

	bflush(efp) ;

	if (f_usage) goto usage ;



/* the test */

	nprintf("/tmp/test.err","can you see this ?\n") ;



done:
	close(1) ;

	bclose(efp) ;

	return OK ;

usage:
	bprintf(efp,
	    "%s: USAGE> %s [mailfile [offset]] [-sV] [-t offset] [-offset]\n",
	    progname,progname) ;

	goto badret ;

not_enough:
	bprintf(efp,"%s: not enough arguments supplied\n",
	    progname) ;

	goto badret ;

badarg:
	bprintf(efp,"%s: bad argument value specified\n",
	    progname) ;

badret:
	bclose(efp) ;

	return BAD ;
}
/* end subroutine (main) */



