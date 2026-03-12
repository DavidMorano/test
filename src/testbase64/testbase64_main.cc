/* testbase64_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |base64(3uc)| subroutines */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<ulogerror.h>
#include	<uclibmem.h>
#include	<ucmem.h>
#include	<getfdfile.h>		/* |FD_STDIN| */
#include	<ascii.h>
#include	<base64.h>
#include	<ccfile.hh>
#include	<obuf.hh>
#include	<libf.h>		/* |fwrite(3f)| */
#include	<mkchar.h>
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG */

#include	"hasprint.h"


/* local defines */

#define	MI		maininfo

#define	BASE64LINELEN	76
#define	BASE64BUFLEN	((BASE64LINELEN / 4) * 3)

#undef	BUFLEN
#define	BUFLEN		(100 * BASE64BUFLEN)


/* imported namespaces */

using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using libuc::mem ;			/* variable */
using std::nothrow ;			/* constant */


/* local typedefs */


/* local structures */

struct maininfo_fl {
    	uint		dummy:1 ;
    	uint		text:1 ;
    	uint		test:1 ;
} ;

struct maininfo {
    	maininfo_fl	fl{} ;
	char		*fbuf{} ;
	int		flen ;
	int start() noex ;
	int finish() noex ;
	int encode(cchar *) noex ;
	int procln(obuf *,cchar *,int) noex ;
	int putout(obuf *bp,int ch) noex ;
	int putflush(obuf *bp) noex ;
	void dtor() noex ;
	destruct maininfo() noex {
	    if (fbuf) dtor() ;
	} /* end dtor */
} ; /* end struct (maininfo) */


/* forward references */

local int outbase64(MI *,cchar *,int) noex ;


/* local variables */


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
		        rs = mi.encode(arg) ;
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
	flen = BUFLEN ;
	if ((fbuf = new(nothrow) char [flen + 1]) != np) {
	    rs = SR_OK ;
	}
	return rs ;
} /* end method (maininfo::start) */

int maininfo::finish() noex {
    	int		rs = SR_OK ;
	if (fbuf) {
	    delete [] fbuf ;
	    fbuf = nullptr ;
	    flen = 0 ;
	}
	return rs ;
} /* end method (maininfo::finish) */

void maininfo::dtor() noex {
	if (cint rs = finish() ; rs < 0) {
	    ulogerror("maininfo",rs,"dtor") ;
	}
} /* end method (maininfo::dtor) */

int maininfo::encode(cchar *fn) noex {
        cint		inlen = (BUFLEN + 4) ;
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		olen = 0 ; /* return-value */
	if (char *inbuf ; (rs = mem.vall((inlen + 1),&inbuf)) >= 0) {
            if (fl.text) {
		obuf ob ;
                if (ccfile in ; (rs = in.open(fn,"r")) >= 0) {
		    while ((rs = in.readln(inbuf,inlen)) > 0) {
			rs = procln(&ob,inbuf,rs) ;
                        olen += rs ;
			if (rs < 0) break ;
		    } /* end while */
                    rs1 = in.close ;
                    if (rs >= 0) rs = rs1 ;
                } /* end if (opnened input file) */
            } else {
                int         ifd = FD_STDIN ;
                if (fn[0] != '-') {
                    rs = u_open(fn,O_RDONLY,0666) ;
                    ifd = rs ;
                }
                if (rs >= 0) {
                    while ((rs = u_read(ifd,inbuf,inlen)) > 0) {
                        rs = outbase64(this,inbuf,rs) ;
                        olen += rs ;
                        if (rs < 0) break ;
                    } /* end while */
                    rs1 = u_close(ifd) ;
                    if (rs >= 0) rs = rs1 ;
                } /* end if (ok) */
            } /* end if (straight or text-mode) */
            rs1 = mem.free(inbuf) ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (m-a-f) */
	return (rs >= 0) ? olen : rs ;
}
/* end method (maininfo::encode) */

int maininfo::procln(obuf *bp,cchar *lp,int ll) noex {
    	int		rs = SR_OK ;
	int		olen = 0 ; /* return-value */
	for (int ch, i = 0 ; (i < ll) && ((ch = mkchar(lp[i])) > 0) ; i += 1) {
	    if (ch == CH_NL) {
		if ((rs = putout(bp,CH_CR)) >= 0) {
		    olen += rs ;
		    rs = putout(bp,ch) ;
                    olen += rs ;
		}
            } else {
		rs = putout(bp,ch) ;
                olen += rs ;
	    } /* end if */
            if (rs < 0) break ;
	} /* end for */
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::procln) */

int maininfo::putflush(obuf *bp) noex {
    	int		rs = SR_NOMEM ;
	int		olen = 0 ; /* return-value */
	if (fbuf) {
	    int	 c = 0 ;
	    cint mlen = min(BASE64LINELEN,flen) ;
	    while ((rs = bp->read(fbuf,mlen)) > 0) {
		c += rs ;
	        rs = outbase64(this,fbuf,rs) ;
		olen += rs ;
		if (rs < 0) break ;
	    } /* end while */
	    if ((rs >= 0) && (c > 0)) {
		rs = bp->adv(c) ;
	    }
	} /* end if (non-null) */
	return (rs >= 0) ? olen : rs ;
} /* end method (maininfo::putflush) */

int maininfo::putout(obuf *bp,int ch) noex {
	int		rs ;
	int		olen = 0 ;
	if ((rs = bp->add(ch)) >= 0) {
	    if ((rs = bp->count) >= BUFLEN) {
		rs = putflush(bp) ;
		olen += rs ;
	    }
	}
	return (rs >= 0) ? olen : rs ;
}
/* end method (maininfo::putout) */

/* write out in BASE64! */
local int outbase64(MI *pip,cchar *sbuf,int slen) noex {
    	FILE		*fp = stderr ;
	int		rs = SR_OK ;
	int		wlen = 0 ; /* return-value */
	char		linebuf[BASE64LINELEN + 4] ;
	for (int rlen = slen, i = 0 ; (rs >= 0) && (rlen > 0) ; ) {
	    cint	mlen = MIN(BASE64BUFLEN,rlen) ;
	    if (cint len = base64_e(sbuf + i,mlen,linebuf) ; len > 0) {
	        if (pip->fl.test) {
	            rs = 0 ;
	            if (len > 0) {
	                int	c = 1 ;
	                int	ol = 0 ;
	                for (int m, j = 0 ; (rs >= 0) && (j < len) ; ) {
	                    m = MIN(c,(len - j)) ;
	                    rs = fwrite(fp,(linebuf + j),m) ;
	                    ol += rs ;
	                    j += m ;
	                    c += 1 ;
	                } /* end for */
	                if (rs >= 0) {
	                    rs = ol ;
		        }
	            } /* end if */
	            wlen += rs ;
	        } else {
	            rs = fwrite(fp,linebuf,len) ;
	            wlen += rs ;
	        }
	        if (rs >= 0) {
	            rs = fputch(fp,CH_NL) ;
	            wlen += rs ;
	        } /* end if (ok) */
	    } /* end if (non-zero positive) */
	    rlen -= mlen ;
	    i += mlen ;
	    if (rs < 0) break ;
	} /* end while */
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (outbase64) */


