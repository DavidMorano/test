/* textfsdirtree_main SUPPORT (testfsdirtree) */
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
#include	<fcntl.h>		/* POSIX® */
#include	<libproc.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>		/* CSTD */
#include	<new>			/* C++STD */
#include	<iostream>		/* C__STD |cout| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<fsdirtree.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |MAXNAMELEN| + |eol| */

import libutil ;

using libu::umem ;			/* variable */
using std::cout ;			/* variable */

local int dirlist(cchar *name) noex {
	cnothrow	nt{} ;
    	int		rs = SR_INVALID ;
	int		rs1 ;
	if (name[0]) {
	    cint	nlen = MAXNAMELEN ;
	    rs = SR_NOMEM ;
	    if (char *nbuf = new(nt) char[nlen + 1]) {
	        if (fsdirtree dir ; (rs = dir.open(name)) >= 0) {
		    for (ustat sb ; (rs = dir.read(&sb,nbuf,nlen)) > 0 ; ) {
			cout << nbuf << eol ;
		    } /* end while */
		    rs1 = dir.close ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (fsdirtree) */
	        delete [] nbuf ;
	    } /* end if (m-a-f) */
	} /* end if (valid) */
	return rs ;
} /* end subroutine (dirlist) */

int main(int argc,con mainv argv,con mainv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	for (int ai = 1 ; (rs >= 0) && (ai < argc) ; ai += 1) {
	    if (cchar *dirname = argv[ai]) {
		if (dirname[0]) {
		    rs = dirlist(dirname) ;
		}
	    }
	} /* end for */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


