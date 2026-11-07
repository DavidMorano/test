/* testproginfo_main SUPPORT (testproginfo) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* this is a small test of the PROGINFO object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* special debugging */

/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was originally written to facilitate
	testing of software writen for RightCore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testproginfo

	Description:
	This is a small test of the PROGINFO object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<intceil.h>		/* LIBU */
#include	<strkeycmp.h>		/* LIBUC */
#include	<matkeystr.h>		/* LIBUC */
#include	<strnul.hh>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |COLUMNS| + |DECBUFLEN| */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

import proginfo ;
import testproginfo_info ;

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* special debugging */
#endif

#define	VDF		"TESTPROGINFO_DFN"


/* imported namespaces */


/* type-defs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int mi_hello(maininfo *) noex ;


/* local variables */

enum progmodes {
    	progmode_testproginfo,
    	progmode_testprog,
    	progmode_x,
	progmode_overlast
} ; /* end enum */

constexpr cpcchar	prognames[] = {
    	[progmode_testproginfo]	= "testproginfo",
    	[progmode_testprog]	= "testprog",
	[progmode_x]		= "x",
	[progmode_overlast]	= nullptr
} ; /* end array (prognames) */

constexpr mapex_map	mapexs[] = {
	{ SR_NOENT,	EX_NOUSER	},
	{ SR_AGAIN,	EX_TEMPFAIL	},
	{ SR_DEADLK,	EX_TEMPFAIL	},
	{ SR_NOLCK,	EX_TEMPFAIL	},
	{ SR_TXTBSY,	EX_TEMPFAIL	},
	{ SR_ACCESS,	EX_NOPERM	},
	{ SR_REMOTE,	EX_PROTOCOL	},
	{ SR_NOSPC,	EX_TEMPFAIL	},
	{ SR_INTR,	EX_INTR		},
	{ SR_EXIT,	EX_TERM		},
	{ SR_DOM,	EX_NOPROG	},
	{ 0, 		0		}
} ; /* end array (mapexs) */

cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	int		rs ;
	int		rs1 ;
	int		ex = EX_OK ;
	mainv		pns = prognames ;
	if (ccp cp = getourenv(envv,VDF)) {
	    rs = DEBUGOPEN(cp) ;
	    DEBUGPRINTF("ent rs=%d\n",rs) ;
	} /* end if debugging) */
    	if (maininfo mi(argc,argv,envv) ; (rs = mi.start(pns)) >= 0) {
	    DEBUGPRINTF("maininfo::start() rs=%d\n",rs) ;
	    if (ccp pn = mi.progname) {
	        DEBUGPRINTF("pn=%s\n",pn) ;
	        DEBUGPRINTF("pm=%d\n",mi.pm) ;
		printf("progname=%s\n",pn) ;
		if ((rs = mi.progmode(prognames)) >= 0) {
	            DEBUGPRINTF("pm=%d\n",mi.pm) ;
		    if ((rs = mi_hello(&mi)) >= 0) {
			rs = mi.retpid ;
	                DEBUGPRINTF("pid=%d\n",rs) ;
	                DEBUGPRINTF("pid=%d\n",mi.pid) ;
		    }
		}
	    } /* end block */
	    rs1 = mi.finish ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (maininfo) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if (error) */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int mi_hello(maininfo *mip) noex {
    	int		rs ;
	int		len = 0 ; /* return-value */
	cchar		s[] = "Hello error world!" ;
    	if ((rs = mip->eprint(s)) >= 0) {
	    len += rs ;
	    if ((rs = mip->eprintf("fmt> %s\n",s)) >= 0) {
	        len += rs ;
	        if ((rs = mip->eprint) >= 0) {
		    len += rs ;
		}
	    }
	} /* end if */
	DEBUGPRINTF("ret rs=%d len=%d\n",rs,len) ;
	return rs ;
} /* end subroutine (mi_hello) */


