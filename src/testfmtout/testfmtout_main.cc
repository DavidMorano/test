/* testfmtout_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test some string formatting code */
/* version %I% last-modified %G% */


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
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<stdfnames.h>		/* LIBU */
#include	<stdintx.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<bfile.h>		/* LIBB */


/* local defines */


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


/* local variables */

constexpr sub_f		subs[] = {
    	sub1,
	sub2,
	sub3,
	sub4
} ; /* end array */


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
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int sub1(bfile *ofp) noex {
    	return ofp->printf("Hello world!\n") ;
}

local int sub2(bfile *ofp) noex {
    	cchar *fmt = "value=%3d\n" ;
	cint	v = 42 ;
	int	rs ;
	if ((rs = ofp->printf(fmt,v)) >= 0) {
	    long lv = 442 ;
	    fmt = "long-value=%4ld\n" ;
	    if ((rs = ofp->printf(fmt,lv)) >= 0) {
		lv = (neg lv) ;
	        fmt = "neg-long-value=%4ld\n" ;
	        rs = ofp->printf(fmt,lv) ;
	    }
	}
    	return rs ;
} /* end subroutine (sub2) */

local int sub3(bfile *ofp) noex {
    	int		rs = SR_OK ;
    	(void) ofp ;
    	return rs ;
} /* end subroutine (sub3) */

local int sub4(bfile *ofp) noex {
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

