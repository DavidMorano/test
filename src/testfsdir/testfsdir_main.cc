/* textfsdir_main SUPPORT (testfsdir) */
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
#include	<sys/stat.h>		/* POSIX® |stat(2)| */
#include	<unistd.h>		/* POSIX® |getpid(2)| */
#include	<fcntl.h>		/* POSOX® */
#include	<libproc.h>		/* ?? */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<new>			/* C++STD */
#include	<iostream>		/* C++STD |cout| */
#include	<thread>		/* C++STD */
#include	<mutex>			/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<fsdir.h>		/* LIBUC */
#include	<localmisc.h>		/* |MAXNAMELEN| + |eol| */

import libutil ;

using libu::umem ;			/* variable */
using std::cout ;			/* variable */

typedef fsdir_ent	ent ;

local int dirlist(cchar *name) noex {
    	cnullptr	np{} ;
	cnothrow	nt{} ;
    	int		rs = SR_INVALID ;
	int		rs1 ;
	if (name[0]) {
	    cint	nlen = MAXNAMELEN ;
	    rs = SR_NOMEM ;
	    if (char *nbuf = new(nt) char[nlen + 1]) ylikely {
	        if (fsdir dir ; (rs = dir.open(name)) >= 0) ylikely {
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

int main(int argc,con mainv argv,con mainv) {
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
} /* end subroutine (main) */


