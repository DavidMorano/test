/* teststrnstr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test the |strnstr(3c)| subroutine */
/* version %I% last-modified %G% */

#define	CF_OURS		1		/* ours or theirs */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Decription:
	This actually tests our implementation of what will become
	(eventually) the standard C-language library subroutine
	(maybe) |strnstr(3c)|.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	CF_OURS	
#define	CF_OURS		1		/* ours or theirs */
#endif


/* local namespaces */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern size_t strlen(ccharp) noex ;
    extern size_t strnlen(ccharp,size_t) noex ;
} /* end extern (C) */

extern "C" {
    extern int	strncmp(ccharp,ccharp,size_t) noex ;
} /* end extern (C) */


/* external variables */


/* local structures */


/* forward references */

#if	CF_OURS
char *strnstr(cchar *sp,cchar *ss,size_t n) noex {
    	char		*rp = nullptr ;
	if (sp && ss) ylikely {
	    rp = cast_const<charp>(sp) ;
	    if (csize sslen = strlen(ss) ; sslen > 0) {
	        if (csize sl = strnlen(sp,n) ; sl >= sslen) {
		    {
		        char *ep = rp + (sl - sslen) ;
		        bool f = false ;
		        for ( ; rp < ep ; rp += 1) {
			    f = (strncmp(rp,ss,sslen) == 0) ;
			    if (f) break ;
		        } /* end for */
		        if (! f) rp = nullptr ;
		    } /* end block */
	        } else {
	            rp = nullptr ;
	        } /* end */
	    } /* end if (positive) */
	} /* end if (non-null) */
	return rp ;
} /* end subroutine (strnstr) */
#else
#include	<cstring>
#endif /* CF_OURS */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 1) {
	    if (ccharp tstr = argv[1] ; tstr[0]) {
		charp rp{} ;
		printf("tstr=%s\n",tstr) ;
		for (int ai = 2 ; ai < argc ; ai += 1) {
		    ccharp sstr = argv[ai] ;
		    printf("sstr=%s\n",sstr) ;
		    if ((rp = strnstr(tstr,sstr,50))) {
		        printf("mat rp=%s\n",rp) ;
		    } else {
		        printf("mat-no\n") ;
		    } /* end if (strnstr) */
		} /* end for */
	    } /* end if */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


