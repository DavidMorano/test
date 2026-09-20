/* mainvector (C++98) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<string>		/* CSTD */
#include	<vector>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


struct termout_gch {
	uchar		ch, gr ;
} ;

int main() {
	using namespace std ;
	struct termout_gch	gch ;
	vector<struct termout_gch>	a ;
	vector<string>		vs ;
	int		sz ;
	int	&szr = sz ;
	int	*ip = new int[10] ;

	for (int i = 0 ; i < 20 ; i += 1) {
	    gch.ch = i ;
	    gch.gr = 0 ;
	    a.push_back(gch) ;
	} /* end for */

	sz = a.size() ;
	for (int i = 0 ; i < sz ; i += 1) {
	    printf("a[%u]=%d\n",i,a[i].ch) ;
	}

	for (int i = 0 ; i < sz ; i += 1) {
	    a[i].ch += 1 ;
	}

	for (int i = 0 ; i < sz ; i += 1) {
	    printf("a[%u]=%d\n",i,a[i].ch) ;
	}

	for (int i = 0 ; i < 10 ; i += 1) {
	    ip[i] = i ;
	}

	for (int i = 0 ; i < 10 ; i += 1) {
	    printf("a[%u]=%d\n",i,ip[i]) ;
	}

	delete ip ;
	return 0 ;
} /* end subroutine (main) */


