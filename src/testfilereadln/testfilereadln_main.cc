/* testfilereadln_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* part of the TESTFILEREADLN program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* run-time debug print-outs */

/* revision history:

	= 1996-02-01, David A­D­ Morano
	The program was written from scratch to do what the previous
	program by the same name did.

*/

/* Copyright © 1996 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This is a fairly generic front-end subroutine for a program.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG */
#include	<prognamevar.hh>	/* LIBDAM */

#include	"testfilereadln.h"
#include	"filereadln.h"


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* run-time debug print-outs */
#endif

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX((MAXPATHLEN + 20),2048)
#endif

#define	VDFN		"TESTFILEREADLN_DFN"


/* external subroutines */


/* forward references */


/* external variables */


/* local variables */

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
	argopt_ef,
	argopt_of,
	argopt_overlast
} ; /* end enum */

constexpr cpcchar	argopts[] = {
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
	"ef",
	"of",
	nullptr
} ; /* end array */

constexpr mapex_map	mapexs[] = {
	{ SR_NOENT,	EX_NOUSER	},
	{ SR_AGAIN,	EX_TEMPFAIL	},
	{ SR_DEADLK,	EX_TEMPFAIL	},
	{ SR_NOLCK,	EX_TEMPFAIL	},
	{ SR_TXTBSY,	EX_TEMPFAIL	},
	{ SR_ACCESS,	EX_NOPERM	},
	{ SR_REMOTE,	EX_PROTOCOL	},
	{ SR_NOSPC,	EX_TEMPFAIL	},
	{ SR_INTR,	EX_INTR		},
	{ SR_EXIT,	EX_TERM		},
	{ SR_DOM,	EX_NOPROG	},
	{ 0, 0 }
} ; /* end array */

enum progmodes {
	progmode_testfilereadln,
	progmode_overlast
} ; /* end enum */

constexpr cpcchar	progmodes[] = {
	"testfilereadln",
	nullptr
} ; /* end array */

enum progopts {
	progopt_follow,
	progopt_nofollow,
	progopt_overlast
} ; /* end enum */

constexpr cpcchar	progopts[] = {
	"follow",
	"nofollow",
	nullptr
} ; /* end array */

cint			llen		= LINEBUFLEN ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	cnothrow	nt{} ;
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	if (char *cp = getenv(VDFN)) {
	    if ((rs = DEBUGOPEN(cp)) > 0) {
	        rs = DEBUGPRINTF("starting rs=%d\n",rs) ;
	    }
	} /* end if (debugging) */
	if ((rs >= 0) && (argc > 1)) {
	    if (charp lbuf = new(nt) char [llen + 1]) {
		for (int ai = 1 ; (rs >= 0) && (ai < argc) ; ai += 1) {
		    if (ccp ap = argv[ai] ; ap[0]) {
			if ((rs = filereadln(ap,lbuf,llen)) >= 0) {
			    printf("readln() rs=%d lbuf=%s\n",rs,lbuf) ;
			} /* end if (filereadln) */
		    } /* end if (non-empty) */
		} /* end for */
		delete [] lbuf ;
	    } /* end if (m-a-f) */
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DEBUGPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


