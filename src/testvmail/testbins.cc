/* testbins_main SUPPORT (testbins) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test something w/ VMAIL */
/* version %I% last-modified %G% */


#define	CF_DEBUG	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debug memory-allocations */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is a small test of a binary search technique.

	Synopsis:

	$ testbins.x


*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>
#include	<cinttypes>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<forward_list>
#include	<vector>
#include	<string>
#include	<fstream>
#include	<ostream>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ascii.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<bfile.h>		/* LIBB */

#include	"defs.h"
#include	"config.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	PCS
#define	PCS		"/usr/add-on/pcs"
#endif

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif

#define	OBUFLEN		(LINEBUFLEN*2)

#ifndef	PI
#define	PI		proginfo
#endif

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* namespaces */

using namespace	std ;


/* external subroutines */

#if	CF_DEBUG
extern "C" int	debugopen(const char *) ;
extern "C" int	debugprintf(const char *,...) ;
extern "C" int	debugprinthex(const char *,int,const char *,int) ;
extern "C" int	debugclose() ;
extern "C" int	strlinelen(const char *,int,int) ;
#endif


/* forward references */

#if	CF_DEBUG
local int	debugprintchars(cchar *,const wchar_t *,int) ;
#endif


/* local variables */

static const int 	values[] = {
	1,3,5,7, -1
} ;


/* exported subroutines */


/* ASRGUSED */
int main(int argc,cchar *argv[],cchar *envv[])
{
	PI	pi, *pip = &pi ;

#if	CF_DEBUG && CF_DEBUGMALL
	uint		mo_start = 0 ;
#endif

	int		rs = SR_OK ;
	int		ex = 0 ;
	const char	*pr = PCS ;
	const char	*cp ;

#if	CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUG */

#if	CF_DEBUG && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	memset(pip,0,sizeof(PI)) ;
	pip->pr = pr ;

/* go */

	if (rs >= 0) {
	    const int	svals[] = { 3, 0, 1, 9, 7, 5, 10 } ;
	    cout << "the values are:\n" ;
	    for (auto v : values) {
		cout << " " << v ;
	    }
	    cout << endl ;
	    for (auto sch : svals) {
	        int	front = 0 ;
	        int	back = (nelem(values)-1) ;
	        int	ch = '¿' ;
	        int	i ;
		cout << "sch=" << sch << endl ;
	        i = ((back-front)/2) ;
#if	CF_DEBUG
		{
		    const wchar_t	*w = (const wchar_t *) values ;
		    debugprintchars("main:",w,back) ;
		    debugprintf("main: sch=%d\n",sch) ;
		}
#endif
	        while (front < back) {
		    ch = values[i] ;
#if	CF_DEBUG
		    debugprintf("main: top i=%u ch=%u\n",i,ch) ;
#endif
		    if (sch > ch) {
			front = (i+1) ;
		    } else if (sch < ch) {
			back = i ;
		    } else {
			break ;
		    }
#if	CF_DEBUG
		    debugprintf("main: bot front=%u back=%u\n",front,back) ;
#endif
	            i = (front + ((back-front)/2)) ;
	        } /* end while */
#if	CF_DEBUG
		debugprintf("main: front=%u\n",front) ;
		debugprintf("main: back=%u\n",back) ;
		debugprintf("main: i=%u ch=%u\n",i,ch) ;
#endif
		if (front < back) {
		    cout << "found i=" << i << " ch=" << ch << endl ;
		} else {
		    cout << "not found" << endl ;
		}
	    } /* end for */
	} /* end if (ok) */

#if	CF_DEBUG
	debugprintf("main: done rs=%d\n",rs) ;
#endif

#if	CF_DEBUG && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	CF_DEBUG
	debugclose() ;
#endif

	if (rs < 0) ex = 1 ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

#if	CF_DEBUG
local int debugprintchars(cchar *id,const wchar_t *wbuf,int wlen) noex {
	for (int i = 0 ; i < wlen ; i += 1) {
	    const int	ch = wbuf[i] ;
	    debugprintf("main/%s: wc[%02u]=%08x\n",id,i,ch) ;
	}
	return 0 ;
} /* end subroutine (debugprintchars) */
#endif /* CF_DEBUG */


