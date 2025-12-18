local int epr(cchar *fmt,...) noex {
    	va_list		ap ;
	cnothrow	nt{} ;
	cnullptr	np{} ;
	cint		llen = MAXLINELEN ;
	int		rs = SR_FAULT ;
	int		pl = 0 ; /* return-value */
	cchar		pn[] = "test: " ;
	if (fmt) {
	    va_begin(ap,fmt) ;
	    rs = SR_NOMEM ;
	    if (char *lbuf ; (lbuf = new(nt) char[llen + 1]) != np) {
		try {
		    cerr << pn ;
	            if ((rs = vsnprintf(lbuf,llen,fmt,ap)) >= 0) {
			cerr << lbuf << eol ;
		    }
		} catch (...) {
		    rs = SR_NOMEM ;
		}
	        delete [] lbuf ;
	    } /* end if (m-a-f) */
	    va_end(ap) ;
	} /* end if (non-null) */
	return (rs >= 0) ? pl : rs ;
} /* end subroutine (epr) */

