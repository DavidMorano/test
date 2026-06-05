/* testfmtspec_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test the FMTSPEC object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	This program tests the |fmtspec(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* POSIX */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdarg>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<string>		/* CSTD */
#include	<new>			/* C++STD */
#include	<initializer_list>	/* C++STD */
#include	<utility>		/* C++STD */
#include	<functional>		/* C++STD */
#include	<algorithm>		/* C++STD */
#include	<string>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"fmtspec.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import fmtspec ;

/* local defines */


/* imported namespaces */


/* external subroutines */


/* local structures */


/* forward references */

local int sub(int,con mainv,...) noex ;


/* local variables */

constexpr cpcchar	fmts[] = {
	"4.3dxxx",
	"08xxxx",
	"10dxxx",
	"10uxxx",
	"10oxxx",
	"10hljhljdx",
	"12lldxx",
	"016lx<<hello-there>>",
	"032llx<<hello-there>>"
} ; /* end array */

namespace {
    struct lenmoder {
	cchar	*n[lenmod_overlast + 1] = {} ;
	consteval lenmoder() noex {
	    n[lenmod_none]		= "none" ;
	    n[lenmod_halfhalf]		= "halfhalf" ;
	    n[lenmod_half]		= "half" ;
	    n[lenmod_long]		= "long" ;
	    n[lenmod_longlong]		= "longlong" ;
	    n[lenmod_imax]		= "imax" ;
	    n[lenmod_imaxmax]		= "imaxmax" ;
	    n[lenmod_longdouble]	= "longdouble" ;
	    n[lenmod_wide]		= "wide" ;
	    n[lenmod_diff]		= "diff" ;
	    n[lenmod_size]		= "size" ;
	    n[lenmod_overlast]		= nullptr ;
	} ; /* end ctor */
    } ; /* end struct (lenmoder) */
} /* end namespace */

constexpr lenmoder	lenmod ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	    (void) envv ;
	if (rs >= 0) {
    	    cint ac = argc ;
	    rs = sub(argc,argv,ac) ;
	} /* end if (sub) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int sub(int argc,mainv argv,...) noex {
    	va_list		ap ;
	cint		lmover = lenmod_overlast ;
	int		rs = SR_OK ;
	int		rs1 ;
	(void) argc ;
	{
	    va_begin(ap,argv) ;
	    for (auto &sp : fmts) {
		cint	sl = lenstr(sp) ;
		if (fmtspec fo ; (rs = fo.start(ap,sp,sl)) >= 0) {
		    if (int lmi = fo.lenmod ; (lmi >= 0) && (lmi < lmover)) {
			cchar *lms = lenmod.n[lmi] ;
			printf("----\n") ;
			printf("fmt=%s\n"	,sp) ;
			printf("rs=%d\n"	,rs) ;
			printf("w=%d\n"		,fo.width) ;
			printf("p=%d\n"		,fo.prec) ;
			printf("mod=%s\n"	,lms) ;
			printf("code=%c\n"	,fo.fcode) ;
			printf("cnt=%d\n"	,fo.skiplen) ;
		    } /* end block */
		    rs1 = fo.finish ;
		    if (rs >= 0) rs = rs1 ;
		} /* end of (fmtspec) */
		if (rs < 0) break ;
	    } /* end for */
	    va_end(ap) ;
	} /* end block */
	return rs ;
} /* end subroutine (sub) */


