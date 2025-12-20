/* sintq SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* short-integer queue module */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This, or something almost identical to this, is actually
	very old.  This code might date to about 1983.  But I
	just cleaned it up to the present form below.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	sintq

	Description:
	This module implements a short-intger queue object.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>

#include	"sintq.h"


/* local defines */


/* imported namespaces */

using libu::umem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int sintq_start(sintq *op,int ne) noex {
	int		rs = SR_FAULT ;
	if (ne <= 0) ne = SINTQ_DEFENTS ;
	if (op) ylikely {
	    cint sz = (ne * szof(short)) ;
	    rs = SR_INVALID ;
	    if (sz > 1) ylikely {
		if (void *vp ; (rs = umem.mall(sz,&vp)) >= 0) ylikely {
		    op->qbuf = shortp(vp) ;
	            op->qlen = ne ;
	            op->cnt = 0 ;
	            op->ri = 0 ;
	            op->wi = 0 ;
	        } /* end if (memory-allocation) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sintq_start) */

int sintq_finish(sintq *op) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (op) ylikely {
	    rs = SR_OK ;
	    if (op->qbuf) ylikely {
	        rs1 = umem.free(op->qbuf) ;
	        if (rs >= 0) rs = rs1 ;
	        op->qbuf = nullptr ;
	    }
	    op->qlen = 0 ;
	    op->cnt = 0 ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sintq_finish) */

int sintq_ins(sintq *op,int ch) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = SR_OVERFLOW ;
	    if (op->cnt < op->qlen) ylikely {
	        op->qbuf[op->wi] = short(ch) ;
	        op->wi = ((op->wi + 1) % op->qlen) ;
	        op->cnt += 1 ;
	        rs = op->cnt ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sintq_ins) */

int sintq_rem(sintq *op,short *rp) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = SR_EMPTY ;
	    if (op->cnt > 0) ylikely {
	        if (rp) *rp = op->qbuf[op->ri] ;
	        op->ri = ((op->ri + 1) % op->qlen) ;
	        op->cnt -= 1 ;
	        rs = op->cnt ;
	    } /* end if (not-empty) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sintq_rem) */

int sintq_remall(sintq *op) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = SR_OK ;
	    op->ri = 0 ;
	    op->wi = 0 ;
	    op->cnt = 0 ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sintq_remall) */

int sintq_size(sintq *op) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = op->qlen ;
	}
	return rs ;
}
/* end subroutine (sintq_size) */

int sintq_count(sintq *op) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = op->cnt ;
	}
	return rs ;
}
/* end subroutine (sintq_count) */

int sintq::ins(int ch) noex {
	return sintq_ins(this,ch) ;
}

int sintq::rem(short *rp) noex {
	return sintq_rem(this,rp) ;
}

void sintq::dtor() noex {
	if (cint rs = finish ; rs < 0) {
	    ulogerror("sintq",rs,"fini-finish") ;
	}
} /* end method (sintq::dtor) */

sintq::operator int () noex {
	int		rs = SR_BUGCHECK ;
	if (qbuf) ylikely {
	    rs = cnt ;
	} /* end if (non-null) */
	return rs ;
} /* end method (sintq::operator) */

int sintq_co::operator () (int a) noex {
	int		rs = SR_BUGCHECK ;
	if (op) ylikely {
	    switch (w) {
	    case sintqmem_start:
	        rs = sintq_start(op,a) ;
	        break ;
	    case sintqmem_remall:
	        rs = sintq_remall(op) ;
	        break ;
	    case sintqmem_size:
	        rs = sintq_size(op) ;
	        break ;
	    case sintqmem_count:
	        rs = sintq_count(op) ;
	        break ;
	    case sintqmem_len:
	        rs = sintq_count(op) ;
	        break ;
	    case sintqmem_finish:
	        rs = sintq_finish(op) ;
	        break ;
	    } /* end switch */
	} /* end if (non-null) */
	return rs ;
} /* end method (sintq_co::operator) */


