/* testfmtout_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test some string formatting code */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 1998 A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This program helps to test the |fmtstr(3uc)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* POSIX */
#include	<sys/param.h>		/* POSIX */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<stdfnames.h>		/* LIBU */
#include	<stdintx.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<bfile.h>		/* LIBB */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */
#include	<libdebug.h>		/* LIBEBUG |DEBUGPRINTF(3debug)| */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* local namespaces */


/* local typedefs */

typedef int (*sub_f)(bfile *) noex ;


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int sub1(bfile *) noex ;
local int sub2(bfile *) noex ;
local int sub3(bfile *) noex ;
local int sub4(bfile *) noex ;
local int sub5(bfile *) noex ;
local int sub6(bfile *) noex ;


/* local variables */

constexpr sub_f		subs[] = {
    	sub1,
	sub2,
	sub3,
	sub4,
	sub5,
	sub6
} ; /* end array */

cbool			f_debug		= CF_DEBUG ;

/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cchar		*fn = STDFNOUT ;
	int	rs ;
	int	rs1 ;
	int	ex = EX_OK ;
	if (bfile out ; (rs = out.open(fn,"wct",0666)) >= 0) {
	    for (cauto &s : subs) {
		rs = (*s)(&out) ;
		if (rs < 0) break ;
	    } /* end for */
	    rs1 = out.close ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (bfile) */
	ex = (rs >= 0) ? EX_OK : EX_DATAERR ;
	if (ex) {
	    fprintf(stderr,"ret ex=%d\n",ex) ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int sub1(bfile *ofp) noex {
    	return ofp->printf("Hello world!\n") ;
}

local int sub2(bfile *ofp) noex {
    	int		rs ;
	int		v = 0 ;
    	cchar		*fmt ;
	DPRINTF("ent\n") ;
	DPRINTF("b\n") ;
	fmt = "value(b)=»%b«\n" ;
	if ((rs = ofp->printf(fmt,v)) >= 0) {
	DPRINTF("8b\n") ;
	    fmt = "value(8b)=»%8b«\n" ;
	    if ((rs = ofp->printf(fmt,v)) >= 0) {
	DPRINTF("8.2b\n") ;
	        fmt = "value(8.2b)=»%8.2b«\n" ;
	        if ((rs = ofp->printf(fmt,v)) >= 0) {
    	            fmt = "value(o)=%o\n" ;
	            if ((rs = ofp->printf(fmt,v)) >= 0) {
    	                fmt = "value(8o)=%8o\n" ;
	                if ((rs = ofp->printf(fmt,v)) >= 0) {
    	                    fmt = "value(8.2o)=%8.2o\n" ;
	                    if ((rs = ofp->printf(fmt,v)) >= 0) {
    			        fmt = "value(x)=%x\n" ;
			        if ((rs = ofp->printf(fmt,v)) >= 0) {
    	    		            fmt = "value(8x)=%8x\n" ;
	    		            if ((rs = ofp->printf(fmt,v)) >= 0) {
    	    		                fmt = "value(8.2x)=%8.2x\n" ;
	    		                if ((rs = ofp->printf(fmt,v)) >= 0) {
				            rs = SR_OK ;
				        }
			            }
			        }
			    }
			}
	            }
	        }
	    }
	}
	return rs ;
} /* end subroutine (sub2) */

local int sub3(bfile *ofp) noex {
    	cint		v = 33 ;
    	int		rs ;
    	cchar *fmt = "value(08b)=%08b\n" ;
	if ((rs = ofp->printf(fmt,v)) >= 0) {
	    fmt = "val-oct(8o)=%8o\n" ;
	    if ((rs = ofp->printf(fmt,v)) >= 0) {
	        fmt = "val-oct(08o)=%08o\n" ;
	        if ((rs = ofp->printf(fmt,v)) >= 0) {
	            fmt = "val-hex(x)=%x\n" ;
	            if ((rs = ofp->printf(fmt,v)) >= 0) {
	                fmt = "val-hex(12x)=%12x\n" ;
	                if ((rs = ofp->printf(fmt,v)) >= 0) {
	                    fmt = "val-hex(12.4x)=%12.4x\n" ;
	                    if ((rs = ofp->printf(fmt,v)) >= 0) {
	                        fmt = "val-hex(08x)=%08x\n" ;
	                        if ((rs = ofp->printf(fmt,v)) >= 0) {
	                            fmt = "val-hex(012x)=%012x\n" ;
	                            if ((rs = ofp->printf(fmt,v)) >= 0) {
	                                rs = SR_OK ;
			            }
			        }
			    }
		        }
		    }
	        }
	    }
	}
	return rs ;
} /* end subroutine (sub3) */

local int sub4(bfile *ofp) noex {
    	cchar *fmt = "value=%3d\n" ;
	cint	v = 42 ;
	int	rs ;
	if ((rs = ofp->printf(fmt,v)) >= 0) {
	    fmt = "val-int(06d)=%06d\n" ;
	    if ((rs = ofp->printf(fmt,v)) >= 0) {
	        long lv = 442 ;
	        fmt = "val-long(ld)=%ld\n" ;
	        if ((rs = ofp->printf(fmt,lv)) >= 0) {
	            fmt = "val-long(4ld)=%4ld\n" ;
	            if ((rs = ofp->printf(fmt,lv)) >= 0) {
		        lv = (neg lv) ;
	                fmt = "val-long-neg(4ld)=%4ld\n" ;
	                rs = ofp->printf(fmt,lv) ;
		    }
	        }
	    }
	}
    	return rs ;
} /* end subroutine (sub4) */

local int sub5(bfile *ofp) noex {
    	longlong	llv = -1 ;
    	int		rs = SR_OK ;
	cchar		*fmt = "val-longlong(lld)=%lld\n" ;
    	if ((rs = ofp->printf(fmt,llv)) >= 0) {
	    fmt = "val-longlong(6lld)=%6lld\n" ;
    	    if ((rs = ofp->printf(fmt,llv)) >= 0) {
	        fmt = "val-longlong-x(llx)=%llx\n" ;
    	        if ((rs = ofp->printf(fmt,llv)) >= 0) {
	            fmt = "val-longlong-x(036llx)=%036llx\n" ;
    	            if ((rs = ofp->printf(fmt,llv)) >= 0) {
	                rs = SR_OK ;
	            }
	        }
	    }
	}
    	return rs ;
} /* end subroutine (sub5) */

local int sub6(bfile *ofp) noex {
    	return ofp->printf("Goodbye.\n") ;
}


#ifdef	COMMENT
	    unsigned longlong	a, r ;
	    unsigned int	ui, uii ;
	    int	i, ii ;

	a = 0xFFFFFFFFFFFFFF01UL ;

	i = 7 ;
	ui = i ;
	ii = (~ i) ;
	uii = (~ ui) ;

	bprintf(ofp,"ii=%016llX\n",(longlong) uii) ;

	bprintf(ofp,"uii=%016llX\n",((unsigned longlong) ii)) ;

	r = ((unsigned longlong) ii) ;
	bprintf(ofp,"r1=%016llX\n",r) ;

	r = (longlong) (~ ui) ;
	bprintf(ofp,"r2=%016llX\n",r) ;

#endif /* COMMENT */

