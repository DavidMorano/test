/* testccfile_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the CCFILE object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	testccfile

	Description:
	This program tests the CCFILE object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>		/* |FILE(3stdio)| */
#include	<cstring>		/* |strcmp(3c)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<ulogerror.h>
#include	<usupport.h>
#include	<umem.hh>
#include	<getfdfile.h>		/* |FD_STDIN| */
#include	<ascii.h>
#include	<ccfile.hh>
#include	<bufos.hh>
#include	<rmx.h>			/* |rmeol(3uc)| */
#include	<strnul.hh>
#include	<mkchar.h>
#include	<localmisc.h>
#include	<libf.h>		/* LIBF */
#include	<dprintf.h>

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#define	MI		maininfo

#define	BUFLEN		1024
#define	LINELEN		76

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* imported namespaces */

using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using libu::umem ;			/* variable */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct maininfo_fl {
    	uint		test:1 ;
    	uint		text:1 ;
    	uint		stream:1 ;
} ; /* end struct (maininfo_fl) */

struct maininfo {
    	FILE		*ofp = stdout ;
	char		*inbuf{} ;
	char		*fbuf{} ;
	int		inlen ;
	int		flen ;
    	maininfo_fl	fl{} ;
	int start() noex ;
	int finish() noex ;
	int proc(cchar *) noex ;
	int proc_text(cchar *) noex ;
	int proc_textstream(cchar *) noex ;
	int proc_textcc(cchar *) noex ;
	int proc_bin(cchar *) noex ;
	int proc_binstream(cchar *) noex ;
	int proc_binraw(cchar *) noex ;
	void dtor() noex ;
	destruct maininfo() noex {
	    if (fbuf || inbuf) dtor() ;
	} /* end dtor */
} ; /* end struct (maininfo) */


/* forward references */


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
    	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;
	if (argc > 0) {
	    if (maininfo mi ; (rs = mi.start()) >= 0) {
	        for (int ai = 1 ; ai < argc ; ai += 1) {
		    if (cchar *arg = argv[ai] ; arg && arg[0]) {
			DPRINTF("arg=%s\n",arg) ;
			if (strcmp(arg,"text") == 0) {
			    mi.fl.text = true ;
			} else if (strcmp(arg,"stream") == 0) {
			    mi.fl.stream = true ;
			} else {
		            rs = mi.proc(arg) ;
			}
		    } /* end if (argument) */
		    if (rs < 0) break ;
	        } /* end for */
	        rs1 = mi.finish() ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (maininfo) */
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

int maininfo::start() noex {
    	int		rs = SR_NOMEM ;
	inlen = LINELEN ;
	if (inbuf = new(nothrow) char [inlen + 1] ; inbuf) {
	    flen = BUFLEN ;
	    if (fbuf = new(nothrow) char [flen + 1] ; fbuf) {
	        rs = SR_OK ;
	    } /* end if (new-char) */
	    if (rs < 0) {
		delete [] inbuf ;
		inbuf = nullptr ;
		inlen = 0 ;
	    } /* end if (error) */
	} /* end if (new-char) */
	return rs ;
} /* end method (maininfo::start) */

int maininfo::finish() noex {
    	int		rs = SR_OK ;
	if (fbuf) {
	    delete [] fbuf ;
	    fbuf = nullptr ;
	    flen = 0 ;
	}
	if (inbuf) {
	    delete inbuf ;
	    inbuf = nullptr ;
	    inlen = 0 ;
	}
	return rs ;
} /* end method (maininfo::finish) */

void maininfo::dtor() noex {
	if (cint rs = finish() ; rs < 0) {
	    ulogerror("maininfo",rs,"dtor") ;
	}
} /* end method (maininfo::dtor) */

int maininfo::proc(cchar *fn) noex {
	int		rs ;
	int		wlen = 0 ; /* return-value */
            if (fl.text) {
		rs = proc_text(fn) ;
		wlen = rs ;
            } else {
		rs = proc_bin(fn) ;
		wlen = rs ;
	    } /* end if (text or binary) */
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc) */

int maininfo::proc_text(cchar *fn) noex {
	int		rs ;
	int		wlen = 0 ; /* return-value */
	if (fl.stream) {
	    rs = proc_textstream(fn) ;
    	    wlen += rs ;
	} else {
	    rs = proc_textcc(fn) ;
    	    wlen += rs ;
	}
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc_text) */

int maininfo::proc_textstream(cchar *fn) noex {
	int		rs = SR_OK ;
	int		wlen = 0 ; /* return-value */
	(void) fn ;
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc_textistream) */

int maininfo::proc_textcc(cchar *fn) noex {
    	int		rs = SR_NOMEM ;
	int		rs1 ;
	int		idx = 0 ;
	int		wlen = 0 ; /* return-value */
	DPRINTF("ent\n") ;
	    if (ccfile inf ; (rs = inf.open(fn,"r")) >= 0) {
	        DPRINTF("open rs=%d\n",rs) ;
	        while ((rs = inf.readln(inbuf,inlen)) > 0) {
		    cint len = rs ;
		if_constexpr (f_debug) {
		    cint rl = rmeol(inbuf,len) ;
		    {
		    strnul ps(inbuf,rl) ;
	            DPRINTF("readln rs=%d inbuf=>%s<\n",len,ccp(ps)) ;
		    }
		}
		    rs = fwriter(ofp,inbuf,len) ;
		    wlen += rs ;
	            DPRINTF("fwriter rs=%d\n",rs) ;
		    idx += len ;
		    if (rs < 0) break ;
	        } /* end while */
		DPRINTF("while rs=%d\n",rs) ;
	        rs1 = inf.close ;
	        if (rs >= 0) rs = rs1 ;
		DPRINTF("close rs=%d\n",rs1) ;
	    } /* end if (ccfile) */
	DPRINTF("ret rs=%d idx=%d wlen=%d \n",rs,idx,wlen) ;
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc_textcc) */

int maininfo::proc_bin(cchar *fn) noex {
    	int		rs = SR_OK ;
	int		wlen = 0 ;
	if (fl.stream) {
	    rs = proc_binstream(fn) ;
	    wlen += rs ;
	} else {
	    rs = proc_binraw(fn) ;
	    wlen += rs ;
	}
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc_bin) */

int maininfo::proc_binstream(cchar *fn) noex {
    	int		rs = SR_OK ;
	int		wlen = 0 ;
	(void) fn ;
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc_bintream) */

int maininfo::proc_binraw(cchar *fn) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	int		wlen = 0 ; /* return-value */
	int         ifd = FD_STDIN ;
	DPRINTF("ent ifd=%d fn=%s\n",ifd,fn) ;
	if (fn[0] != '-') {
	    rs = u_open(fn,O_RDONLY,0666) ;
	    ifd = rs ;
	} /* end if (std-input) */
	if (rs >= 0) {
	    while ((rs = u_read(ifd,inbuf,inlen)) > 0) {
		cint len = rs ;
		if_constexpr (f_debug) {
		    cint rl = rmeol(inbuf,len) ;
		    {
		    strnul ps(inbuf,rl) ;
	            DPRINTF("inbuf=>%s<\n",ccp(ps)) ;
		    }
		}
		rs = fwriter(ofp,inbuf,len) ;
		wlen += rs ;
		if (rs < 0) break ;
	    } /* end while */
            rs1 = u_close(ifd) ;
            if (rs >= 0) rs = rs1 ;
	} /* end if (ok) */
	DPRINTF("ret rs=%d olen=%d\n",rs,wlen) ;
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::proc_binraw) */


