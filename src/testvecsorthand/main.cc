/* main SUPPORT (testvecsorthand) */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* sorted vector testing */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cinttypes>
#include	<cstring>
#include	<new>			/* |nothrow(3c++)| */
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<forward_list>
#include	<vector>
#include	<string>
#include	<fstream>
#include	<ostream>
#include	<iostream>
#include	<iomanip>
#include	<usystem.h>
#include	<bfile.h>
#include	<field.h>
#include	<vechand.h>
#include	<char.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"vecsorthand.h"


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif


/* name spaces */

using namespace	std ;


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int	mainfins(vecsorthand *) noex ;
static int	mainadd(vecsorthand *,int) noex ;

extern "C" {
    static int	ourcmp(cvoid *,cvoid *) noex ;
}

/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	vecsorthand	slist ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = 0 ;

	if ((rs = vecsorthand_start(&slist,ourcmp,0)) >= 0) {
	    cvoid	*ep ;

	    rs = mainadd(&slist,1) ;
	    mainadd(&slist,2) ;
	    mainadd(&slist,3) ;

	    for (int i = 0 ; vecsorthand_get(&slist,i,&ep) >= 0 ; i += 1) {
		int	v ;
	        if (ep) {
		    int	*ip = (int *) ep ;
		    v = *ip ;
		    cout << ' ' << v ;
	        }
	    }
	    cout << eol ;
	    {
	        rs1 = mainfins(&slist) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    rs1 = vecsorthand_finish(&slist) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (vecsorthand) */

	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

static int mainadd(vecsorthand *vlp,int v) noex {
	cint		esize = sizeof(int) ;
	int		rs ;
	int		*ip ;
	if ((rs = uc_malloc(esize,&ip)) >= 0) {
	    *ip = v ;
	    rs = vecsorthand_add(vlp,ip) ;
	}
	return rs ;
}
/* end subroutine (mainadd) */

static int mainfins(vecsorthand *vlp) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		i ;
	int		*ep ;

	for (i = 0 ; vecsorthand_get(vlp,i,&ep) >= 0 ; i += 1) {
	    rs1 = uc_free(ep) ;
	    if (rs >= 0) rs = rs1 ;
	}

	return rs ;
}
/* end subroutine (mainfins) */

static int ourcmp(cvoid *a1p,cvoid *a2p) noex {
	int		**e1pp = (int **) a1p ;
	int		**e2pp = (int **) a2p ;
	int		rc = 0 ;
	{
	    int		*e1p = *e1pp ;
	    int		*e2p = *e2pp ;
	    if (e1p || e2p) {
	        if (e1p) {
	            if (e2p) {
	                rc = (*e1p - *e2p) ;
	            } else {
		        rc = -1 ;
		    }
	        } else {
		    rc = 1 ;
		}
	    }
	} /* end block) */
	return rc ;
}
/* end subroutine (ourcmp) */


