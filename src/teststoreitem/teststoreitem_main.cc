/* teststoreitem_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* get the |storeitem(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_ARGS		1		/* test-args */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Description:
	Test aspects of the STOREITEM object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSYD */
#include	<cstdlib>		/* CSYD */
#include	<cstdio>		/* CSYD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<uclibmem.h>		/* LIBUC */
#include	<storeitem.h>		/* LIBUC */
#include	<snx.h>			/* LIBUC |sninetaddr(3uc)| */
#include	<isnot.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<deb.hh>		/* LIBU */
#include	<prognamevar.hh>	/* LIBDAM */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/deb.ccm"

import libutil ;			/* |lenstr(3u)| */
import deb ;				/* debugging */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif
#ifndef	CF_ARGS
#define	CF_ARGS		1		/* test-args */
#endif

#define	VARDFN		"TESTSTOREITEM_DFN"


/* imported namespaces */

using libuc::libmem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct thing {
	int		a ;
	int		*wp ;
	char		*sp ;
    } ; /* end struct */
} /* end namespace */


/* forward references */

local int testone	(ccharp) noex ;
local int testargs	(int,con mainv) noex ;
local int testload	(thing *,char *,int,con thing *) noex ;
local int dispthing	(con thing *) noex ;
local int printstrv	(con mainv) noex ;


/* local variables */

cint			maxline		= LINEBUFLEN ;
cbool			f_debug		= CF_DEBUG ;
cbool			f_args		= CF_ARGS ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (ccharp cp = getenv(VARDFN)) {
	    if ((rs = DEBOPEN(cp)) >= 0) {
		rs = DEBPRINTF("ent pn=%s rs=%d\n",ccp(pn),rs) ;
	    } else if (isNotPresent(rs)) {
		rs = SR_OK ;
	    } /* end */
	} /* end if (debugging) */
	if (rs >= 0) {
	    rs = testone("mailhost") ;
	} /* end if (testzero) */
	if ((rs >= 0) && f_args && ((argc - 1) > 0)) {
	    rs = testargs((argc -1),(argv + 1)) ;
	} /* end if (testzero) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBPRINTF("ret rs=%d\n",rs) ;
	DEBCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

[[maybe_unused]]
local int testone(ccharp hn) noex {
    	int		rs = SR_FAULT ;
	int		rs1 ;
	int		len = 0 ; /* return-value */
	DEBPRINTF("ent\n") ;
	if (hn) {
	    rs = SR_INVALID ;
	    if (hn[0]) {
	        int a = 42 ;
		if (cchar *cstrp ; (rs = lm_strw("hello",-1,&cstrp)) >= 0) {
		    char *strp = cast_const<charp>(cstrp) ;
	            if (char *hebuf ; (rs = lm_ho(&hebuf)) >= 0) {
		        cint helen = rs ;
	                {
			    con thing ot = { 2, &a, strp } ;
			    dispthing(&ot) ;
			    thing res ;
			    if ((rs = testload(&res,hebuf,helen,&ot)) >= 0) {
				len = rs ;
				rs = dispthing(&res) ;
			    }
	                } /* end block */
	                rs1 = lm_free(hebuf) ;
	                if (rs >= 0) rs = rs1 ;
	            } /* end if (m-a-f) */
		    rs1 = lm_free(strp) ;
	            if (rs >= 0) rs = rs1 ;
		} /* end if (m-a-f) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	DEBPRINTF("ret rs=%d len=%d\n",rs,len) ;
	return (rs >= 0) ? len : rs ;
} /* end subroutine (testone) */

local int testload(thing *resp,char *rbuf,int rlen,con thing *srcp) noex {
    	int		rs = SR_FAULT ;
	int		rs1 ;
	int		len = 0 ; /* return-value */
	DEBPRINTF("ent\n") ;
	if (resp && srcp) {
	    (void) rbuf ;
	    (void) rlen ;
	    (void) srcp ;
	    memclear(resp) ;
	    resp->a = srcp->a ;
	    if (storeitem si ; (rs = si.start(rbuf,rlen)) >= 0) {
		if (srcp->wp) {
		    cint w = *srcp->wp ;
		    DEBPRINTF("-> storeitem_word\n") ;
		    if (cint *ip{} ; (rs = si.word(&ip,w)) >= 0) {
			resp->wp = cast_const<int *>(ip) ;
		    }
		    DEBPRINTF("storeitem_word() rs=%d\n",rs) ;
		} /* end if (source) */
		if (srcp->sp) {
		    cchar *sp = srcp->sp ;
		    if (cchar *rp ; (rs = si.strw(&rp,sp)) >= 0) {
			resp->sp = cast_const<charp>(rp) ;
		    }
		} /* end if (source) */
		rs1 = si.finish ;
		if (rs >= 0) rs = rs1 ;
		DEBPRINTF("storeitem_finish() rs=%d\n",rs) ;
	    } /* end if (storeitem) */
	} /* end if (non-null) */
	DEBPRINTF("ret rs=%d len=%d\n",rs,len) ;
	return (rs >= 0) ? len : rs ;
} /* end subroutine (testload) */

local int dispthing(con thing *srcp) noex {
    	int		rs = SR_FAULT ;
	if (srcp) {
	    printf("a=%d\n",srcp->a) ;
	    if (srcp->wp) {
		printf("w=%d\n",*srcp->wp) ;
	    }
	    if (srcp->sp) {
		printf("s=%s\n",srcp->sp) ;
	    }
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (dispthing) */

local int testargs(int strc,con mainv strv) noex {
    	int		rs = SR_FAULT ;
	int		rs1 ;
	int		len = 0 ; /* return-value */
	(void) strc ;
	DEBPRINTF("ent\n") ;
	printf("testargs strc=%d\n",strc) ;
	if (strv) {
	    cint alen = maxline ;
	    if (char *abuf ; (rs = libmem.mall((alen + 1),&abuf)) >= 0) {
	        if (storeitem si ; (rs = si.start(abuf,alen)) >= 0) {
		    {
		        if (ccharpp tab ; (rs = si.strtab(&tab,strv)) >= 0) {
			    DEBPRINTF("si.strtab() rs=%d\n",rs) ;
			    len += rs ;
			    rs = printstrv(tab) ;
		        } /* end if */
		    }
		    rs1 = si.finish ;
	            if (rs >= 0) rs = rs1 ;
		    DEBPRINTF("si-out rs=%d\n",rs) ;
	        } /* end if (storeitem) */
	        rs1 = libmem.free(abuf) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (m-a-f) */
	} /* end if (non-null) */
	printf("testargs ret rs=%d len=%d\n",rs,len) ;
	DEBPRINTF("ret rs=%d len=%d\n",rs,len) ;
	return (rs >= 0) ? len : rs ;
} /* end subroutine (testargs) */

local int printstrv (con mainv strv) noex {
    	int		rs = SR_FAULT ;
	int		len = 0 ; /* return-value */
	if (strv) {
	    rs = SR_OK ;
	    for (int i = 0 ; (rs >= 0) && strv[i] ; i += 1) {
		ccharp sp = strv[i] ;
		len += (lenstr(sp) + 1) ;
		printf("i=%d s=»%s«\n",i,sp) ;
	    } /* end for */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
} /* end subroutine (printstrv) */


