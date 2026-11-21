/* testsysrealname SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_PRINTBEF	0		/* use |printf(3stdio)| before */
#define	CF_PRINTOUT	1		/* use |printf(3stdio)| for out */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/syslog.h>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"sysrealname.h"

#define	VARDEBUGFNAME	"TESTSYSREALNAME_DEBUGFILE"

#define	NDEBFNAME	"testsysrealname.deb"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif

/* external subroutines */


/* external variables */


/* local structures */

struct arginfo {
	int		argc ;
	int		ai, ai_max, ai_pos ;
	mainv		argv ;
} ; /* end struct (arginfo) */


/* forward references */

local int procargs(struct ainfo *,SYSREALNAME *) ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	arginfo		ainfo{} ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		rs1 ;
	int	ai, ai_pos, ai_max ;
	int	max = 10 ;
	int	ttl = (10*60) ;
	int	opts = 0 ;

	if (cchar *cp = getenv(VARDEBUGFNAME)) {
	    rs = DEBUGOPEN(cp) ;
	    DEBUGPRINTF("starting rs=%d\n",rs) ;
	} /* end if (debugging) */

	ai = 0 ;
	ai_pos = 0 ;
	ai_max = 0 ;

	ainfo.argc = argc ;
	ainfo.ai = ai ;
	ainfo.argv = argv ;
	ainfo.ai_max = ai_max ;
	ainfo.ai_pos = ai_pos ;

	SYSREALNAME	grm ;
	if ((rs = sysrealname_start(&grm,max,ttl)) >= 0) {
	    if (argc > 1) {
		rs = procargs(&ainfo,&grm) ;
	    } /* end if (arguments) */
	    rs1 = sysrealname_finish(&grm) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (sysrealname) */

	if ((ex = EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBUGPRINTF("sysrealname-out rs=%d\n",rs) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procargs(ainfo *aip,SYSREALNAME *snp) {
	int		rs = SR_OK ;
	int		rs1 ;
	int		c = 0 ;
		for (int ai = 1 ; argv[ai] ; ai += 1) {
		    SYSREALNAME_CUR	cur ;
		    cchar	*gn = argv[ai] ;
#if	CF_PRINTBEF
			      printf("before cursor gn=%s\n",gn) ;
#endif
		    if ((rs = sysrealname_curbegin(&grm,&cur)) >= 0) {
#if	CF_PRINTBEF
			      printf("before lookup gn=%s\n",gn) ;
#endif
			if ((rs1 = sysrealname_lookup(&grm,&cur,gn,-1)) >= 0) {
			    auto srn_lu = sysrealname_lookread ;
			  char	ub[USERNAMELEN+1] ;
			  cint	ul = USERNAMELEN ;
#if	CF_PRINTBEF
			      printf("before lookread gn=%s\n",gn) ;
#endif
			  while ((rs = srn_lu(&grm,&cur,ub,ul)) >= 0) {
				c += 1 ;
#if	CF_DEBUG
		debugprintf("main: sysrealname_lookread() rs=%d\n",rs) ;
		debugprintf("main: ub=%s\n",ub) ;
#endif
#if	CF_PRINTOUT
			      printf("%s\n",ub) ;
#endif
			  } /* end while */
			  if (rs == SR_NOTFOUND) {
				rs = SR_OK ;
#if	CF_DEBUG
		debugprintf("main: while-out done c=%u\n",c) ;
#endif
			   }
			} else {
			    printf("not-found (%d)\n",rs1) ;
			} /* end if */
			rs1 = sysrealname_curend(&grm,&cur) ;
			if (rs >= 0) rs = rs1 ;
		    } /* end if (cursor) */
		} /* end for */
	return rs ;
} /* end subroutine (procargs) */


