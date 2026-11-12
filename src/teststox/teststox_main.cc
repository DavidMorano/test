/* teststox_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |sto{x}(3c++)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
  	Test the |sto{x}(3c++)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<string>		/* C++STD */
#include	<stringview>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU |cfdec(3u)| */
#include	<strnul.hh>		/* LIBU */
#include	<cfdec.h>		/* LIBUC */
#include	<ctdec.h>		/* LIBUC */
#include	<strabbr.h>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

using std::string ;			/* type */
using std::string_view ;		/* type */
using std::cout ;			/* variable */

using strview	= std::string_view ;

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

local int procexcept() noex ;

constexpr int		diglen		= DIGBUFLEN ;
constexpr int		b		= 10 ;
constexpr bool		f_debug		= CF_DEBUG ;

int main(int argc,con mainv argv,con mainv) {
    	cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
	char		digbuf[diglen + 1] ;
	ccharp		fmt{} ;
    	DPRINTF("ent\n") ;
	if (argc > 1) {
	    string dstr ;
	    for (int ai = 1 ; (ai < argc) && argv[ai] ; ai += 1) {
		if (cchar *ap = argv[ai] ; ap[0]) {
		    if (int al ; (al = lenstr(ap)) > 0) {
			strview sv(ap,al) ;
		        if (int v ; (rs = cfdec(ap,al,&v)) >= 0) {
			    uint vu ;
			    dstr = sv ;
			    printf("cfdec s=>%s<  v=%d\n",ap,v) ;
			    rs = stringtosi(dstr,b,&v) ;
			    printf("stosi rs=%d vs=%d\n",rs,v) ;
			    {
				rs = stringtoui(dstr,b,&vu) ;
			        printf("stoui rs=%d vu=%u\n",rs,vu) ;
				{
				    slonglong vll = slonglong(v) ;
				    rs = stringtosll(dstr,b,&vll) ;
				    ctdec(digbuf,diglen,vll) ;
			            fmt = "stosll rs=%d vll=%s\n" ;
			            printf(fmt,rs,digbuf) ;
				}
			    }
			} /* end if (cfdec) */
		    } /* end if (lenstr) */
		} /* end if (non-empty) */
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */
	if (rs >= 0) {
	    rs = procexcept() ;
	    printf("procexcept rs=%d\n",rs) ;
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	} /* end if (error) */
	{
    	    fmt = "ret ex=%s (%d) rs=%s (%d)\n" ;
    	    DPRINTF(fmt,strabbrexi(ex),ex,strabbrerr(rs),rs) ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procexcept() noex {
    	int		rs = SR_OK ;
	if (rs >= 0) {
	    sint vsi ;
	    string sval = "10000000000" ; /* <- ten zeros */
	    rs = stringtosi(sval,b,&vsi) ;
	    ccharp fmt = "%s: stringtoui() rs=%d\n" ;
	    printf(fmt,__func__,rs) ;
	} /* end if (ok) */
	return rs ;
} /* end subroutine (procexcept) */


