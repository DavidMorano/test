/* testsort_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |qsort(3c)| and other sorting subroutines */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/******************************************************************************

  	Description:
	This little program shows a bad (core-dump quality) bug in
	the Solaris |qsort(3c)| and other sorting subroutines!

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<strings.h>		/* |strcasecmp(3c)| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<cstring>		/* |strcmp(3c)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<vstrcmp.h>
#include	<vstrkeycmp.h>
#include	<vstrsort.h>
#include	<localmisc.h>

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */


/* imported namespaces */

using std::sort ;			/* subroutine-template */


/* external subroutines */


/* external variables */


/* local variables */

constexpr cpcchar	kstrs[] = {
	"_=/bin/cat",
	"PATH=/bin",
	"CDPATH=/home/dam/src",
	"LIBDIR=/home/dam/lib",
	"BINDIR=/home/dam/bin",
	nullptr
} ; /* end array (kstrs) */


/* forward references */

local void	printout(cchar *,mainv) noex ;
local void	strload(cchar **,mainv) noex ;

local int strcmpo(cchar *s1,cchar *s2) noex {
    	return strcmp(s1,s2) ;
}
local int strcmpr(cchar *s1,cchar *s2) noex {
    	return strcmp(s2,s1) ;
}

local bool strlesso(cchar *s1,cchar *s2) noex {
	return (strcmpo(s1,s2) < 0) ;
}
local bool strlessr(cchar *s1,cchar *s2) noex {
	return (strcmpr(s1,s2) < 0) ;
}


/* local variables */

cbool		f_vstrsort = false ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cnullptr	np{} ;
	cnothrow	nt{} ;
	int		rs = SR_NOMEM ;
	int		ex = EXIT_SUCCESS ;

	printout("original",kstrs) ;

	cint dlen = lenstrarr(kstrs) ;
	if (ccharp *datarr ; (datarr = new(nt) ccharp [dlen + 1]) != np) {
	    {
		vstrsort_f fn = vstrcmpo ; /* obverse */
	        strload(datarr,kstrs) ;
		vstrsort(datarr,dlen,fn) ;
	        printout("vstrsort() obv",datarr) ;
	    }
	    {
		vstrsort_f fn = vstrcmpr ; /* reverse */
	        strload(datarr,kstrs) ;
		vstrsort(datarr,dlen,fn) ;
	        printout("vstrsort() rev",datarr) ;
	    }
	    {
		qsort_f fn = qsort_f(vstrkeycmp) ;
	        strload(datarr,kstrs) ;
		qsort(datarr,dlen,sizeof(char *),fn) ;
	        printout("qsort() obv",datarr) ;
	    }
	    {
	        strload(datarr,kstrs) ;
		sort(datarr,(datarr + dlen),strlesso) ; /* obverse */
	        printout("sort() obv",datarr) ;
	    }
	    {
	        strload(datarr,kstrs) ;
		sort(datarr,(datarr + dlen),strlessr) ; /* reverse */
	        printout("sort() rev",datarr) ;
	    }
	    delete [] datarr ;
	} /* end if (new-char) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local void printout(cchar *msg,mainv arr) noex {
	fprintf(stdout,"%s\n",msg) ;
	for (int i = 0 ; arr[i] != nullptr ; i += 1) {
		fprintf(stdout,"a[%d]=>%s<\n",i,arr[i]) ;
	}
} /* end subroutine (printout) */

local void strload(cchar **dst,mainv src) noex {
    	int	i{} ;
	for (i = 0 ; src[i] ; i += 1) {
	    dst[i] = src[i] ;
	}
	dst[i] = nullptr ;
} /* end subroutine (strload) */


