/* testuserinfo_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* part of the TESTUSERINFO program */
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
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG */
#include	<deb.hh>		/* LIBU |DEBPRINTF(3u)| */
#include	<prognamevar.hh>	/* LIBDAM */

#include	"testuserinfo.h"
#include	"userinfo.h"

#pragma		GCC dependency		"mod/deb.ccm"

import deb ;				/* debugging */

//* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* run-time debug print-outs */
#endif

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX((MAXPATHLEN + 20),2048)
#endif

#define	VDFN		"TESTUSERINFO_DFN"


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
	progmode_testuserinfo,
	progmode_overlast
} ; /* end enum */

constexpr cpcchar	progmodes[] = {
	"testuserinfo",
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

cchar			debfn[]		= "userinfo.deb" ;
cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	int		ex = EX_OK ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (char *cp = getenv(VDFN)) {
	    if ((rs = DEBUGOPEN(cp)) > 0) {
	        rs = DEBUGPRINTF("starting rs=%d\n",rs) ;
	    }
	} /* end if (debugging) */
	    if (rs1 = DEBOPEN(debfn) ; rs1 >= 0) {
		DEBPRINTF("deb fd=%d\n",rs1) ;
	    } /* end if (DEBOPEN) */
	if (rs >= 0) {
	    userinfo u ;
	    if ((rs = userinfo_start(&u,nullptr)) >= 0) {
	        DEBUGPRINTF("userinfo_start() rs=%d\n",rs) ;
		{
		    printf("userinfo() rs=%d\n",rs) ;
		    printf("pid=%u\n",	u.pid) ;
		    printf("ruid=%u\n",	u.ruid) ;
		    printf("rgid=%u\n",	u.rgid) ;
		    printf("pwuid=%u\n",	u.pwuid) ;
		    printf("pwgid=%u\n",	u.pwgid) ;
		    printf("username=%s\n",	u.username) ;
		    printf("password=%s\n",	u.password) ;
		    printf("shell=%s\n",	u.shell) ;
		    printf("organization=%s\n",u.organization) ;
		    printf("account=%s\n",	u.account) ;
		    printf("prbin=%s\n",	u.prbin) ;
		    printf("printer=%s\n",	u.printer) ;
		    printf("gecosname=%s\n",u.gecosname) ;
		    printf("homedname=%s\n",u.homedname) ;
		    printf("realname=%s\n",	u.realname) ;
		    printf("mailname=%s\n",	u.mailname) ;
		    printf("name=%s\n",	u.name) ;
		    printf("fullname=%s\n",	u.fullname) ;
		    printf("sysname=%s\n",	u.sysname) ;
		    printf("nodename=%s\n",	u.nodename) ;
		    printf("domainname=%s\n",u.domainname) ;
		    printf("groupname=%s\n",	u.groupname) ;
		    printf("projname=%s\n",	u.projname) ;
		    printf("tz=%s\n",	u.tz) ;
		    printf("md=%s\n",	u.md) ;
		    printf("wstation=%s\n",	u.wstation) ;
		    printf("logid=%s\n",	u.logid) ;
		} /* end block */
		rs1 = userinfo_finish(&u) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (userinfo) */
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DEBCLOSE ;
	DEBUGPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */


