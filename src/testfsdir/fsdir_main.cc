/* fsdir_main SUPPORT (testfsdir) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test calling once */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/stat.h>		/* |stat(2)| */
#include	<unistd.h>		/* |getpid(2)| */
#include	<fcntl.h>
#include	<libproc.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<new>			/* |nothrow(3c++)| */
#include	<iostream>		/* |cout| */
#include	<thread>
#include	<mutex>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<usupport.h>
#include	<fsdir.h>
#include	<localmisc.h>		/* |MAXNAMELEN| + |eol| */

import libutil ;

using std::nullptr_t ;			/* type */
using libu::umemalloc ;			/* subroutine */
using libu::umemfree ;			/* subroutine */
using std::cout ;			/* variable */
using std::nothrow ;			/* constant */

typedef fsdir_ent	ent ;

static int dirlist(cchar *name) noex {
    	cnullptr	np{} ;
    	int		rs = SR_INVALID ;
	int		rs1 ;
	if (name[0]) {
	    cint	nlen = MAXNAMELEN ;
	    rs = SR_NOMEM ;
	    if (char *nbuf ; (nbuf = new(nothrow) char[nlen + 1]) != np) {
	        if (fsdir dir ; (rs = dir.open(name)) >= 0) {
		    for (ent de ; (rs = dir.read(&de,nbuf,nlen)) > 0 ; ) {
			cout << nbuf << eol ;
		    } /* end while */
		    rs1 = dir.close ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (fsdir) */
	        delete [] nbuf ;
	    } /* end if (m-a-f) */
	}
	return rs ;
} /* end subroutine (dirlist) */

int main(int argc,mainv argv,mainv) {
    	int		ex = 0 ;
	int		rs = SR_OK ;
	for (int ai = 1 ; (rs >= 0) && (ai < argc) ; ai += 1) {
	    if (argv[ai]) {
		cchar	*dirname = argv[ai] ;
		rs = dirlist(dirname) ;
	    }
	} /* end for */
	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


