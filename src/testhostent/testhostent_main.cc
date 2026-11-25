/* testhostent SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* get the |uc_gethostbyname(3uc)| subroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_UCGET	0		/* use |ucget{x}| */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Description:
	Test aspects of the HOSTENT object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSYD */
#include	<cstdlib>		/* CSYD */
#include	<cstdio>		/* CSYD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<uinet.h>		/* LIBU */
#include	<uclibmem.h>		/* LIBUC */
#include	<ucinet.h>		/* LIBUC */
#include	<ucget.h>		/* LIBUC */
#include	<ucgetx.h>		/* LIBUC */
#include	<hostent.h>		/* LIBUC */
#include	<snx.h>			/* LIBUC |sninetaddr(3uc)| */
#include	<inetaddrx.h>		/* LIBUC */
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

#define	VARDFN		"TESTHOSTENT_DFN"


/* imported namespaces */

using libuc::libmem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int testget	(ccharp) noex ;
local int testgetuc	(ccharp) noex ;
local int hostent_disp	(HOSTENT *) noex ;
local int mkdot		(char *,int,int,cchar *) noex ;


/* local variables */

cint			aslen		= INET4_ADDRSTRLEN ;
cchar			defhost[] 	= "mailhost" ;
cbool			f_debug		= CF_DEBUG ;
cbool			f_ucget		= CF_UCGET ;


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
	} /* end if (debugging */
	if ((rs >= 0) && (argc > 1)) {
	    for (int ai = 1 ; (rs >= 0) && (ai < argc) ; ai += 1) {
	        if (ccharp name = argv[ai] ; name[0]) {
                    rs = testget(name) ;
		}
            } /* end for */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBPRINTF("ret rs=%d\n",rs) ;
	DEBCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

[[maybe_unused]]
local int testget(ccharp hn) noex {
    	int		rs = SR_FAULT ;
	int		rs1 ;
	if (hn) {
	    rs = SR_INVALID ;
	    if (hn[0]) {
	        if (char *hebuf ; (rs = lm_ho(&hebuf)) >= 0) {
	            {
		        if (HOSTENT *hep = gethostbyname(hn)) {
		            rs = hostent_disp(hep) ;
			} else {
			    printf("no-entry\n") ;
		        } /* end if (gethostbyname) */
	            }
	            rs1 = lm_free(hebuf) ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (m-a-f) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (testget) */

[[maybe_unused]]
local int testgetuc(ccharp hn) noex {
    	int		rs = SR_FAULT ;
	int		rs1 ;
	if (hn) {
	    rs = SR_INVALID ;
	    if (hn[0]) {
	        if (char *hebuf ; (rs = lm_ho(&hebuf)) >= 0) {
	            HOSTENT	he ;
		    cauto	get = uc_gethostbyname ;
	            cint	helen = rs ;
	            if ((rs = get(&he,hebuf,helen,hn)) >= 0) {
			rs = hostent_disp(&he) ;
                    } else {
			printf("no-entry\n") ;
		    } /* end */
		    printf("get n=%s rs=%d \n",hn,rs) ;
		    rs1 = lm_free(hebuf) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (memory-allocation) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (testgetuc) */

local int hostent_disp(HOSTENT *hep) noex {
    	int		rs = SR_FAULT ;
	if (hep) {
	    cint af = hep->h_addrtype ;
	    rs = SR_OK ;
	    printf("name=%s\n",		hep->h_name) ;
	    printf("addrtype=%d\n",	hep->h_addrtype) ;
	    printf("addrlen=%d\n",	hep->h_length) ;
	    if (cchar **aliases = cast_const<ccharpp>(hep->h_aliases)) {
		for (int i = 0 ; (rs >= 0) && aliases[i] ; i += 1) {
                    printf("alias=%s\n",aliases[i]) ;
		} /* end for */
	    } /* end if (aliases) */
	    if (cchar **addrs = cast_const<ccharpp>(hep->h_addr_list)) {
		char asbuf[aslen + 1] ;
		for (int i = 0 ; (rs >= 0) && addrs[i] ; i += 1) {
		    ccharp ap = cast_const<ccharp>(hep->h_addr_list[i]) ;
		    if (rs >= 0) {
		        uint a = inet4int(ap) ;
		        printf("a=%08x\n",a) ;
		    }
                    if (rs >= 0) {
		        rs = inetntop(asbuf,aslen,af,ap) ;
		        printf("inetntop=%s\n",asbuf) ;
		    }
                } /* end for */
	    } /* end if (addresses) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (hostent_disp) */

[[maybe_unused]]
local int mkdot(char *rbuf,int rlen,int af,cchar *addr) noex {
    	int		rs ;
	int		rs1 ;
	int		len = 0 ; /* return-value */
	if (af == AF_INET4) {
    	    inetaddrs	at = inetaddr_bin ;
	    if (inetaddr ia ; (rs = ia.start(at,addr)) >= 0) {
	        {
	            rs = ia.getdot(rbuf,rlen) ;
		    len = rs ;
	        }
	        rs1 = ia.finish ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (inetaddr) */
	} else if (af == AF_INET6) {
	    rs = SR_AFNOSUPPORT ;
	} else {
	    rs = SR_AFNOSUPPORT ;
	} /* end if */
 	return (rs >= 0) ? len : rs ;
} /* end subroutine (mkdot) */


