/* testmodsys_main SUPPORT (testmodsys) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test some aspect of environment handling */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* special debugging */

/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was written for use as a front-end for Korn
	Shell (KSH) commands that are compiled as stand-alone
	programs.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testmodsys

	Description:
	This is a small test for the MODSYS module.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD |strchr(3c)| */
#include	<string_view>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |COLUMNS| + |DECBUFLEN| */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

import modsys ;				/* |msconf(3modsys)| */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* special debugging */
#endif


/* imported namespaces */

using std::string_view ;		/* type */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int subvals() noex ;


/* local variables */

constexpr mapex_map	mapexs[] = {
	{ SR_NOENT,	EX_NOUSER },
	{ SR_AGAIN,	EX_TEMPFAIL },
	{ SR_DEADLK,	EX_TEMPFAIL },
	{ SR_NOLCK,	EX_TEMPFAIL },
	{ SR_TXTBSY,	EX_TEMPFAIL },
	{ SR_ACCESS,	EX_NOPERM },
	{ SR_REMOTE,	EX_PROTOCOL },
	{ SR_NOSPC,	EX_TEMPFAIL },
	{ SR_INTR,	EX_INTR },
	{ SR_EXIT,	EX_TERM },
	{ SR_DOM,	EX_NOPROG },
	{ 0, 0 }
} ; /* end array (mapexs) */

constexpr cpcchar	tests[] = {
    "HOME",
    "PATH",
    "LIBPATH",
    "INCPATH"
} ; /* end array */

cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int		rs = SR_OK ;
	int		ex = EX_OK ;
	DPRINTF("ent\n") ;
	if (rs >= 0) {
	    rs = subvals() ;
	} /* end block */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DPRINTF("ret rs=%d ex=%u\n",rs,ex) ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int subvals() noex {
    	int		rs ;
	if ((rs = msconf.maxnodelen) >= 0) {
	    printf("maxnodelen=%d\n",rs) ;
	    if ((rs = msconf.maxnamelen) >= 0) {
	        printf("maxnamelen=%d\n",rs) ;
	        if ((rs = msconf.maxpathlen) >= 0) {
	            printf("maxpathlen=%d\n",rs) ;
	            if ((rs = msconf.maxlinelen) >= 0) {
	                printf("maxlinelen=%d\n",rs) ;
	                if ((rs = msconf.tzname) >= 0) {
	                    printf("tzname=%d\n",rs) ;
	                    if ((rs = msnprocessors) >= 0) {
	                        printf("nproc=%d\n",rs) ;
			    }
	                }
		    }
	        }
	    }
	}
    	return rs ;
} /* end subroutine */


