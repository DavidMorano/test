/* testshortq_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |obu(3uc)| subroutines */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_TEXT		1		/* text */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* UCHAR_MAX| */
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
#include	<libf.h>		/* |fwrite(3f)| */
#include	<ascii.h>
#include	<ccfile.hh>
#include	<shortq.h>
#include	<rmx.h>			/* |rmeol(3uc)| */
#include	<strnul.hh>
#include	<mkchar.h>
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG */
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
#ifndef	CF_TEXT
#define	CF_TEXT		1		/* text */
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
    	maininfo_fl	fl{} ;
	int start() noex ;
	int finish() noex ;
	int enc(cchar *) noex ;
	int enc_choose(cchar *) noex ;
	int enc_flush() noex ;
	int enc_text(cchar *) noex ;
	int enc_textload(shortq *,cchar *) noex ;
	int enc_textflush(shortq *) noex ;
	int enc_binary(cchar *) noex ;
	int procln(shortq *,cchar *,int) noex ;
	int procdata(shortq *,cchar *,int) noex ;
	int procstage(shortq *,cchar *,int) noex ;
	int procgroup(shortq *,cchar *,int) noex ;
	int procout(shortq *) noex ;
	int procouter(shortq *) noex ;
	int putout(shortq *bp,int ch) noex ;
	int putflush(shortq *bp) noex ;
	void dtor() noex ;
	destruct maininfo() noex {
	    if (stagebuf || fbuf || inbuf) dtor() ;
	} /* end dtor */
} ; /* end struct (maininfo) */


/* forward references */

local char	*strdshort(char *,int,short *) noex ;


/* local variables */

cbool		f_debug = CF_DEBUG ;
cbool		f_text	= CF_TEXT ;


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
	fl.text = f_text ;
	fl.test = f_debug ;
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
		rs = enc_text(fn) ;
		olen = rs ;
            } else {
		rs = enc_binary(fn) ;
		olen = rs ;
	    } /* end if (text or binary) */
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc_choose) */

int maininfo::enc_text(cchar *fn) noex {
    	int		rs ;
	int		rs1 ;
	int		olen = 0 ; /* return-value */
	DPRINTF("ent\n") ;
	if (shortq ob ; (rs = ob.start) >= 0) {
	    if ((rs = enc_textload(&ob,fn)) >= 0) {
		olen += rs ;
		rs = enc_textflush(&ob) ;
		olen += rs ;
	    }
	    rs1 = ob.finish ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (shortq) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc_text) */

int maininfo::enc_textload(shortq *obp,cchar *fn) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	int		olen = 0 ;
	DPRINTF("ent\n") ;
        if (ccfile in ; (rs = in.open(fn,"r")) >= 0) {
	    while ((rs = in.readln(inbuf,inlen)) > 0) {
		cint len = rs ;
	        DPRINTF("read rs=%d\n",rs) ;
		if_constexpr (f_debug) {
		    cint rl = rmeol(inbuf,rs) ;
		    {
		    strnul ps(inbuf,rl) ;
	            DPRINTF("inbuf=>%s<\n",ccp(ps)) ;
		    }
		}
		if ((rs = procln(obp,inbuf,len)) >= 0) {
		    rs = procout(obp) ;
                    olen += rs ;
		}
		(void) len ;
		if (rs < 0) break ;
	    } /* end while */
            rs1 = in.close ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (opnened input file) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc_textload) */

int maininfo::enc_textflush(shortq *obp) noex {
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
} /* end method (maininfo::enc_textflush) */

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
		if_constexpr (f_debug) {
		    cint rl = rmeol(inbuf,rs) ;
		    {
		    strnul ps(inbuf,rl) ;
	            DPRINTF("inbuf=>%s<\n",ccp(ps)) ;
		    }
		}
		rs = fwriter(ofp,inbuf,rs) ;
		olen += rs ;
		if (rs < 0) break ;
	    } /* end while */
            rs1 = u_close(ifd) ;
            if (rs >= 0) rs = rs1 ;
	} /* end if (ok) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::enc_binary) */

int maininfo::procln(shortq *obp,cchar *lp,int ll) noex {
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

int maininfo::procdata(shortq *obp,cchar *lp,int ll) noex {
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

int maininfo::procgroup(shortq *obp,cchar *sp,int sl) noex {
    	int		rs = SR_OK ;
	int		c = 0 ;
	if (sl > 0 ) {
	    for (int i = 0 ; (rs >= 0) && (i < sl) ; i += 1) {
		short wch = shortconv(sp[i] & UCHAR_MAX) ;
	        rs = obp->ins(wch) ;
		c += 1 ;
	    } /* end for */
	} /* end if (ok) */
	return (rs >= 0) ? c : rs ;
} /* end method (maininfo::procgroup) */

int maininfo::procout(shortq *obp) noex {
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

int maininfo::procouter(shortq *obp) noex {
	cnothrow	nt{} ;
    	cint		linelen = LINELEN ;
    	int		rs ;
	int		olen = 0 ;
	DPRINTF("ent\n") ;
	if ((rs = obp->len) > 0) {
	    rs = SR_NOMEM ;
	    if (short *sbuf = new(nt) short [flen + 1] ; sbuf) {
	        cint readlen = min(flen,linelen) ;
	        DPRINTF("len=%d readlen=%d\n",rs,readlen) ;
	        if ((rs = obp->read(sbuf,readlen)) > 0) {
	            DPRINTF("read rs=%d\n",rs) ;
	            cint len = rs ;
	            if ((rs = obp->adv(rs)) >= 0) {
	                DPRINTF("adv rs=%d\n",rs) ;
			if (char *cbuf = new(nt) char[readlen + 1] ; sbuf) {
			    strdshort(cbuf,readlen,sbuf) ;
		            if ((rs = fwriter(ofp,cbuf,len)) >= 0) {
	                        DPRINTF("fwriter rs=%d\n",rs) ;
		                olen += rs ;
		            } /* end if (fwriter) */
			    delete [] cbuf ;
			} /* end if (new-short) */
	            } /* end if (adv) */
	        } /* end if */
	        delete [] sbuf ;
	    } /* end if (new-short) */
	} /* end if (sufficient data to write out) */
	DPRINTF("ret rs=%d olen=%d\n",rs,olen) ;
	return (rs >= 0) ? olen : rs ;

} /* end method (maininfo::procouter) */

local char *strdshort(char *rbuf,int rlen,short *sbuf) noex {
    	char	*rp = nullptr ;
	if (rbuf && sbuf) {
	    rp = rbuf ;
    	    for (int i = 0 ; (i < rlen) && sbuf[i] ; i += 1) {
	        *rp++ = char(sbuf[i]) ;
	    } /* end for */
	    *rp = '\0' ;
	} /* end if (non-null) */
	return rp ;
} /* end subroutine (strdshsort) */


