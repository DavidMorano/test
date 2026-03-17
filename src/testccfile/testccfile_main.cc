/* testccfile_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the CCFILE object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_CCFILE	1		/* <- test CCFILE object */

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
#include	<cstdio>
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
#include	<libdebug.h>		/* LIBDEBUG */
#include	<libf.h>		/* LIBF */
#include	<dprintf.h>

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#define	MI		maininfo

#define	STAGELEN	4
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
    	uint		dummy:1 ;
    	uint		text:1 ;
    	uint		test:1 ;
} ; /* end struct (maininfo_fl) */

struct maininfo {
    	FILE		*ofp = stdout ;
	char		*inbuf{} ;
	char		*fbuf{} ;
	char		*stagebuf{} ;
	int		inlen ;
	int		flen ;
	int		stagelen = 0 ;
	int		stagel = 0 ;
	int		mql = 0 ;
    	maininfo_fl	fl{} ;
	int start() noex ;
	int finish() noex ;
	int enc(cchar *) noex ;
	int enc_choose(cchar *) noex ;
	int enc_flush() noex ;
	int copyccfile(cchar *) noex ;
	int copyccfileload(bufos *,cchar *) noex ;
	int copyccfileflush(bufos *) noex ;
	int enc_binary(cchar *) noex ;
	int procln(bufos *,cchar *,int) noex ;
	int procdata(bufos *,cchar *,int) noex ;
	int procstage(bufos *,cchar *,int) noex ;
	int procgroup(bufos *,cchar *,int) noex ;
	int procout(bufos *) noex ;
	int procouter(bufos *) noex ;
	int putout(bufos *bp,int ch) noex ;
	int putflush(bufos *bp) noex ;
	void dtor() noex ;
	destruct maininfo() noex {
	    if (stagebuf || fbuf || inbuf) dtor() ;
	} /* end dtor */
} ; /* end struct (maininfo) */


/* forward references */


/* local variables */

cbool		f_debug		= CF_DEBUG ;
cbool		f_ccfile	= CF_CCFILE ;


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
		        rs = mi.enc(arg) ;
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
    	cnullptr	np{} ;
    	int		rs = SR_NOMEM ;
	fl.test = f_debug ;
	fl.text = f_ccfile ;
	stagelen = STAGELEN ;
	if ((stagebuf = new(nothrow) char [stagelen + 1]) != np) {
	    flen = BUFLEN ;
	    if ((fbuf = new(nothrow) char [flen + 1]) != np) {
	        rs = SR_OK ;
	    } /* end if (new-char) */
	    if (rs < 0) {
		delete [] stagebuf ;
		stagebuf = nullptr ;
		stagelen = 0 ;
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
	if (stagebuf) {
	    delete stagebuf ;
	    stagebuf = nullptr ;
	    stagelen = 0 ;
	}
	return rs ;
} /* end method (maininfo::finish) */

void maininfo::dtor() noex {
	if (cint rs = finish() ; rs < 0) {
	    ulogerror("maininfo",rs,"dtor") ;
	}
} /* end method (maininfo::dtor) */

int maininfo::enc(cchar *fn) noex {
	int		rs ;
	int		rs1 ;
	int		olen = 0 ; /* return-value */
        inlen = (BUFLEN + 4) ;
	if ((rs = umem.vall((inlen + 1),&inbuf)) >= 0) {
	    if ((rs = enc_choose(fn)) >= 0) {
		olen += rs ;
	    } /* end if */
            rs1 = umem.free(inbuf) ;
            if (rs >= 0) rs = rs1 ;
	    inbuf = nullptr ;
	    inlen = 0 ;
        } /* end if (m-a-f) */
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc) */

int maininfo::enc_choose(cchar *fn) noex {
    	int		rs = SR_OK ;
	int		olen = 0 ;
            if (fl.text) {
		rs = copyccfile(fn) ;
		olen = rs ;
            } else {
		rs = enc_binary(fn) ;
		olen = rs ;
	    } /* end if (text or binary) */
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc_choose) */

int maininfo::copyccfile(cchar *fn) noex {
    	cnothrow	nt{} ;
    	cint		llen = LINEBUFLEN ;
    	int		rs = SR_NOMEM ;
	int		rs1 ;
	int		idx = 0 ;
	int		wlen = 0 ; /* return-value */
	DPRINTF("ent llen=%d\n",llen) ;
	if (char *lbuf = new(nt) char [llen + 1] ; lbuf) {
	    DPRINTF("alloc llen=%d\n",llen) ;
	    if (ccfile inf ; (rs = inf.open(fn,"r")) >= 0) {
	        DPRINTF("open rs=%d\n",rs) ;
	        while ((rs = inf.readln(lbuf,llen)) > 0) {
		    cint len = rs ;
		if_constexpr (f_debug) {
		    cint rl = rmeol(inbuf,len) ;
		    {
		    strnul ps(inbuf,rl) ;
	            DPRINTF("readln rs=%d inbuf=>%s<\n",len,ccp(ps)) ;
		    }
		}
		    rs = fwriter(ofp,lbuf,len) ;
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
	    DPRINTF("ccfile rs=%d\n",rs) ;
	    delete [] lbuf ;
	    lbuf = nullptr ;
	} /* end if (new-chær) */
	DPRINTF("ret rs=%d idx=%d wlen=%d \n",rs,idx,wlen) ;
	return (rs >= 0) ? wlen : rs ;
} /* end method (maininfo::copyccfile) */

int maininfo::copyccfileload(bufos *,cchar *) noex {
    	return SR_OK ;
} /* end method (maininfo::copyccfileload) */

int maininfo::copyccfileflush(bufos *obp) noex {
    	int		rs = SR_NOMEM ;
	int		olen = 0 ;
	DPRINTF("ent\n") ;
	if (obp) {
	    if ((rs = procout(obp)) >= 0) {
	        olen += rs ;
	        rs = procouter(obp) ;
	        olen += rs ;
	    }
	}
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::copyccfileflush) */

int maininfo::enc_binary(cchar *fn) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	int		olen = 0 ; /* return-value */
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
		olen += rs ;
		if (rs < 0) break ;
	    } /* end while */
            rs1 = u_close(ifd) ;
            if (rs >= 0) rs = rs1 ;
	} /* end if (ok) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc_binary) */

int maininfo::procln(bufos *obp,cchar *lp,int ll) noex {
    	int		rs = SR_OK ;
	int		c = 0 ; /* return-value */
	DPRINTF("ent ll=%d\n",ll) ;
	if (ll > 0) {
		rs = procdata(obp,lp,ll) ;
		c += rs ;
	} /* end if (non-zero positive) */
	DPRINTF("ret rs=%d c=%d\n",rs,c) ;
	return (rs >= 0) ? c : rs ;
} /* end method (maininfo::procln) */

int maininfo::procdata(bufos *obp,cchar *lp,int ll) noex {
    	cint		grplen = STAGELEN ;
    	int		rs = SR_OK ;
	int		c = 0 ; /* return-value */
	if (ll > 0) {
	    while (ll >= grplen) {
		rs = procgroup(obp,lp,grplen) ;
		c += rs ;
		lp += grplen ;
		ll -= grplen ;
		if (rs < 0) break ;
	    } /* end while */
	    if ((rs >= 0) && (ll > 0)) {
		rs = procgroup(obp,lp,ll) ;
		c += rs ;
		lp += rs ;
		ll -= rs ;
	    }
	} /* end if (popping line data) */
	return (rs >= 0) ? c : rs ;
} /* end method (maininfo::procdata) */

int maininfo::procgroup(bufos *obp,cchar *sp,int sl) noex {
    	int		rs = SR_OK ;
	int		c = 0 ;
	if (sl > 0 ) {
	        rs = obp->add(sp,sl) ;
		c += 1 ;
	} /* end if (ok) */
	return (rs >= 0) ? c : rs ;
} /* end method (maininfo::procgroup) */

int maininfo::procout(bufos *obp) noex {
    	cint		linelen = LINELEN ;
    	int		rs ;
	int		olen = 0 ;
	DPRINTF("ent\n") ;
	while ((rs = obp->len) >= linelen) {
	    DPRINTF("len=%d\n",rs) ;
	    rs = procouter(obp) ;
	    olen += rs ;
	    if (rs < 0) break ;
	} /* end while (sufficient data to write out) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;

} /* end method (maininfo::procout) */

int maininfo::procouter(bufos *obp) noex {
    	cint		linelen = LINELEN ;
    	int		rs ;
	int		olen = 0 ;
	DPRINTF("ent\n") ;
	if ((rs = obp->extent) >= 0) {
	    mql = max(mql,rs) ;
	    if ((rs = obp->len) > 0) {
	        cint readlen = min(flen,linelen) ;
	        DPRINTF("len=%d readlen=%d\n",rs,readlen) ;
	        if ((rs = obp->read(fbuf,readlen)) > 0) {
	            DPRINTF("read rs=%d\n",rs) ;
	            cint len = rs ;
	            if ((rs = obp->adv(rs)) >= 0) {
	                DPRINTF("adv rs=%d\n",rs) ;
		        if ((rs = fwriter(ofp,fbuf,len)) >= 0) {
	                    DPRINTF("fwriter rs=%d\n",rs) ;
		            olen += rs ;
		        }
	            } /* end if (adv) */
	        } /* end if */
	    } /* end if (sufficient data to write out) */
	} /* end if (extent) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;

} /* end method (maininfo::procouter) */


