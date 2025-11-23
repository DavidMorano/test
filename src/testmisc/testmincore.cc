/* testmincore SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |mincore(2)| UNIX® (POSIX®) system call */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This is test code (in the present case for the |mincore(2)|
	system call).

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/mman.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdarg>
#include	<cstdio>
#include	<usystem.h>
#include	<localmisc.h>		/* TIMEBUFLEN */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/ulibvals.ccm"

import ulibvals ;			/* |ulibval(3u)| */

/* local defines */


/* imported namespaces */

using libu::umem ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct mgr {
    	int		ps ;
	operator int () noex ;
	int setup() noex ;
	int check(void *,size_t) noex ;
	int checker(void *,size_t) noex ;
	static void operator () (int a) noex {
	    printf("a=%d\n",a) ;
	} ;
	static void statcall(int a) noex {
	    printf("a=%d\n",a) ;
	} ;
    } ; /* end struct (mgr) */
} /* end namespace */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv) {
    	mgr		mo ;
	int		rs ;
	mo(3) ;
	mo.statcall(4) ;
	rs = mo ;
	printf("ret (%d)\n",rs) ;
}
/* end subroutine (main) */


/* local subroutines */

mgr::operator int () noex {
    	ps = ulibval.pagesz ;
	return setup() ;
}

int mgr::setup() noex {
    	cnullptr	np{} ;
	csize	ms = size_t(ps * 2) ;
	cint	mp = (PROT_READ | PROT_WRITE) ;
	cint	mf = (MAP_PRIVATE | MAP_ANON) ;
	cint	fd = -1 ;
	int		rs ;
	int		rs1 ;
	void	*md ;
	if ((rs = u_mmapbegin(np,ms,mp,mf,fd,0z,&md)) >= 0) {
	    {
		if ((rs = check(md,ms)) >= 0) {
		    rs = checker(md,ms) ;
		}
	    }
	    rs1 = u_mmapend(md,ms) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (mem-map) */
	return rs ;
} /* end method (mgr::setup) */

int mgr::check(void *md,size_t ms) noex {
    	const caddr_t	ma = caddr_t(md) ;
    	cint		msi = intconv(ms) ;
    	int		rs = SR_OK ;
	int		rs1 ;
    	(void) md ;
	{
    	    cint sz = iceil(msi,ps) ;
	    if (char *va ; (rs = umem.mall((sz + 1),&va)) >= 0) {
		csize psize = size_t(ps) ;
		int i = 0 ;
	        for (caddr_t ai = ma ; ai < (ma + ms) ; ai += ps) {
		    (void) ai ;
		    rs = u_mincore(ai,psize,(va+i)) ;
		    printf("va[%d]=%02X\n",i,va[i]) ;
		    i += 1 ;
	        } /* end for */
	        rs1 = umem.free(va) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (m-a-f) */
	} /* end block */
	return rs ;
} /* end method (mgr::check) */

int mgr::checker(void *md,size_t ms) noex {
    	int		rs = SR_OK ;
	(void) md ;
	(void) ms ;
	return rs ;
} /* end method (mgr::checker) */


