/* testsysconf_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |sysconf(2)| standard C-library sunroutine */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
  	Test the |sysconf(3c)| standard C-library call.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>		/* CSTD */
#include	<cstddef>		/* CSTD |nullptr_t| */
#include	<cstdlib>		/* CSTD |getenv(3c)| */
#include	<cstdio>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<ucsysconf.h>		/* LIBUC */
#include	<bufsizevar.hh>		/* LIBUC */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<dprint.hh>		/* LIBU |DPRINTF(3u)| */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif

struct cmdpair {
    	int	cmd ;
	cchar	*str ;
} ; /* enf struct */

constexpr cmdpair	pairs[] = {
	{ _SC_CLK_TCK,		"CLKTCK" },
	{ _SC_LINE_MAX,		"LINEMAX" },
	{ _SC_LINK_MAX,		"LINKMAX" },
	{ _SC_SYMLOOP_MAX,	"SYMLOOPMAX" },
	{ _SC_UTMPENT_SIZE_MAX,	"UTMPENTMAX" }
} ; /* end array */

static bufsizevar	maxlinelen(bufsize_ml) ;
constexpr bool		f_debug = CF_DEBUG ;

[[maybe_unused]] local int getraw() noex {
    	int		rs = SR_OK ;
	printf("raw\n") ;
    	for (cauto &e : pairs) {
	    long v{} ;
	    int ec ;
	    {
	        errno = 0 ;
    	        v = sysconf(e.cmd) ;
	        ec = errno ;
	    } /* end block */
	    printf("%s=%ld err=%d\n",e.str,v,ec) ;
	} /* end for */
	return rs ;
} /* end subroutine (getraw) */

[[maybe_unused]] local int getu() noex {
    	cnullptr	np{} ;
    	int		rs = SR_OK ;
	printf("getu\n") ;
    	    for (cauto &e : pairs) {
    	        rs = uc_sysconfval(e.cmd,np) ;
	        printf("%s=%d\n",e.str,rs) ;
		if (rs < 0) break ;
	    } /* end for */
	return rs ;
} /* end subroutine (getu) */

[[maybe_unused]] local int getuc() noex {
    	cnullptr	np{} ;
    	int		rs = SR_OK ;
	printf("getuc\n") ;
    	    for (cauto &e : pairs) {
    	        rs = uc_sysconfval(e.cmd,np) ;
	        printf("%s=%d\n",e.str,rs) ;
		if (rs < 0) break ;
	    } /* end for */
	return rs ;
} /* end subroutine (getuc) */

[[maybe_unused]] local int getbuf() noex {
    	int		rs ;
	DPRINTF("ent\n") ;
	printf("getbuf\n") ;
	if ((rs = maxlinelen) >= 0) {
	    printf("maxlinelen=%d\n",rs) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (getbuf) */


typedef int (*get_f)() noex ;

constexpr get_f		subgets[] = {
    	getraw,
	getu,
	getuc,
	getbuf
} ; /* end array (subgets) */

int main(int,con mainv,con mainv) {
    	[[maybe_unused]] cnullptr	np{} ;
    	int		ex = EX_OK ;
	int		rs = SR_OK ;
    	DPRINTF("ent\n") ;
	if (rs >= 0) {
    	    for (cauto &g : subgets) {
		rs = (*g)() ;
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (ok) */
	if ((ex == EX_OK) && (rs < 0)) {
	    ex = mapex(np,rs) ;
	}
    	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (main) */


