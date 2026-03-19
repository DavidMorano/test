
/* write out in BASE64! */
local int outbase64(MI *pip,cchar *sbuf,int slen) noex {
    	FILE		*ofp = stdout ;
	int		rs = SR_OK ;
	int		wlen = 0 ; /* return-value */
	char		linebuf[BASE64_LINELEN + 4] ;
	for (int rlen = slen, i = 0 ; (rs >= 0) && (rlen > 0) ; ) {
	    cint	mlen = MIN(BASE64_BUFLEN,rlen) ;
	    if (cint len = base64_e(sbuf + i,mlen,linebuf) ; len > 0) {
	        if (pip->fl.test) {
	            rs = 0 ;
	            if (len > 0) {
	                int	c = 1 ;
	                int	ol = 0 ;
	                for (int m, j = 0 ; (rs >= 0) && (j < len) ; ) {
	                    m = MIN(c,(len - j)) ;
	                    rs = fwriter(ofp,(linebuf + j),m) ;
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
	            rs = fwriter(ofp,linebuf,len) ;
	            wlen += rs ;
	        }
	        if (rs >= 0) {
	            rs = fputch(ofp,CH_NL) ;
	            wlen += rs ;
	        } /* end if (ok) */
	    } /* end if (non-zero positive) */
	    rlen -= mlen ;
	    i += mlen ;
	    if (rs < 0) break ;
	} /* end for */
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (outbase64) */


