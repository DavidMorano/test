/* testproginfo_info MODULE (module-implementation) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* this is a small test of the PROGINFO object */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was originally written to facilitate
	testing of software writen for RightCore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Module:
	testproginfo

	Description:
	This is a small test of the PROGINFO object.

*******************************************************************************/

module ;

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

#include	"testproginfo_info.hh"

module testproginfo_info ;

import proginfo ;

/* local defines */


/* imported namespaces */


/* type-defs */


/* external subroutines */


/* external variables */


/* local structures */


/* local variables */


/* exported variables */


/* exported subroutines */

int maininfo::pstart(mainv prognames) noex {
    	int		rs ;
	DEBUGPRINTF("maininfo-ent\n") ;
	DEBUGPRINTF("maininfo-ent pns=%p\n",prognames) ;
	if (prognames) {
	DEBUGPRINTF("maininfo-ent pn0=%s\n",prognames[0]) ;
	}
	if ((rs = proginfo::start(prognames)) >= 0) {
	    DEBUGPRINTF("maininfo rs=%d pm=%d\n",rs,pm) ;
	    if ((pm >= 0) && prognames) {
	        DEBUGPRINTF("maininfo pn=%s\n",prognames[rs]) ;
	    } /* end if (valid) */
	} /* end if (proginfo_start) */
	DEBUGPRINTF("maininfo-ret rs=%d\n",rs) ;
	return rs ;
} /* end method (maininfo::pstart) */

int maininfo::pfinish() noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	{
	    rs1 = proginfo::finish() ;
	    if (rs >= 0) rs = rs1 ;
	} /* end */
	return rs ;
} /* end method (maininfo::pfinish) */

int maininfo_co::operator () (mainv pns) noex {
    	int		rs = SR_OK ;
	DEBUGPRINTF("maininfo_co-mv-ent\n") ;
	if (pns) {
	    rs = op->pstart(pns) ;
	} /* end if (non-null) */
	DEBUGPRINTF("maininfo_co-mv-ret rs=%d\n",rs) ;
	return rs ;
} ; /* end method (maininfo::operator) */

maininfo_co::operator int () noex {
    	int		rs = SR_BUGCHECK ;
	DEBUGPRINTF("maininfo_co-em-ent\n") ;
	if (op) ylikely {
	    switch (w) {
	    case infomem_start:
		{
		    mainv pns = nullptr ;
	            rs = op->pstart(pns) ;
		}
	        break ;
	    case infomem_finish:
	        rs = op->pfinish() ;
	        break ;
	    } /* end switch */
	} /* end if (non-null) */
	DEBUGPRINTF("maininfo_co-em-ret rs=%d\n",rs) ;
	return rs ;
} ; /* end method (maininfo::operator) */


