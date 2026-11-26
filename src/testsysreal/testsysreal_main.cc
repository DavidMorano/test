/* testsysreal_main SUPPORT */
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
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<sysrealname.h>		/* LIBUC */
#include	<libdebug.h>		/* LIBDEBUG |EBUGPRINTF(3debug)| */
#include	<prognamevar.hh>	/* LIBDAM */


#define	VARDFN		"TESTSYSREAL_DFN"

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

local int procargs(arginfo *,sysrealname *) noex ;


/* local variables */

cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	arginfo		ainfo{} ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (cchar *cp = getenv(VARDFN)) {
	    rs = DEBUGOPEN(cp) ;
	    DEBUGPRINTF("starting pn=%s rs=%d\n",ccp(pn),rs) ;
	} /* end if (debugging) */

	ainfo.argc = argc ;
	ainfo.argv = argv ;

	if (sysrealname grm ; (rs = sysrealname_open(&grm)) >= 0) {
	    if (argc > 1) {
		rs = procargs(&ainfo,&grm) ;
	    } /* end if (arguments) */
	    rs1 = sysrealname_close(&grm) ;
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

local int procargs(arginfo *aip,sysrealname *snp) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		c = 0 ;
	for (int ai = 1 ; (ai < aip->argc) && aip->argv[ai] ; ai += 1) {
	    cchar	*gn = aip->argv[ai] ;
#if	CF_PRINTBEF
			      printf("before cursor gn=%s\n",gn) ;
#endif
	    sysrealname_cur	cur ;
	    if ((rs = sysrealname_curbeg(snp,&cur)) >= 0) {
		cint fo = 0 ;
#if	CF_PRINTBEF
			      printf("before lookup gn=%s\n",gn) ;
#endif
	        if ((rs1 = sysrealname_curlook(snp,&cur,fo,gn,-1)) >= 0) {
                    cauto srn_lu = sysrealname_curlookread ;
			  char	ub[USERNAMELEN+1] ;
			  [[maybe_unused]] cint	ul = USERNAMELEN ;
#if	CF_PRINTBEF
			      printf("before lookread gn=%s\n",gn) ;
#endif
			  while ((rs = srn_lu(snp,&cur,ub)) >= 0) {
				c += 1 ;
		DEBUGPRINTF("sysrealname_curlookread() rs=%d\n",rs) ;
		DEBUGPRINTF("ub=%s\n",ub) ;
#if	CF_PRINTOUT
			      printf("%s\n",ub) ;
#endif
			  } /* end while */
			  if (rs == SR_NOTFOUND) {
				rs = SR_OK ;
		DEBUGPRINTF("while-out done c=%u\n",c) ;
			   }
			} else {
			    printf("not-found (%d)\n",rs1) ;
			} /* end if */
			rs1 = sysrealname_curend(snp,&cur) ;
			if (rs >= 0) rs = rs1 ;
		    } /* end if (cursor) */
		} /* end for */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (procargs) */


