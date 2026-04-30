/* testdate_main SUPPORT **/
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the date object */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* run-time debugging */
#define	CF_TZSET	1
#define	CF_LOCALTIME	1
#define	CF_MKTIME	1


/* revision history:

	= 2000-09-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<csignal>
#include	<cstddef>
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<bfile.h>
#include	<field.h>
#include	<char.h>
#include	<timestr.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"
#include	"date.h"


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif


/* external subroutines */


/* external variables */


/* local variables */

constexpr char		tterms[] = {
	                0x00, 0x1B, 0x00, 0x00,
	                0x01, 0x10, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00
} ; /* end array */

constexpr char		dterms[] = {
	                0x00, 0x1B, 0x00, 0x00,
	                0x01, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00,
	                0x00, 0x00, 0x00, 0x00
} ; /* end array */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	bfile	infile, *ifp = &infile ;
	bfile	outfile, *ofp = &outfile ;
	date	d ;
	field	f ;
	time_t	daytime ;
	int		rs = SR_OK ;
	int		i, n ;
	int	len, sl ;
	int	itype, otype ;
	int	fd_debug ;
	char	linebuf[LINEBUFLEN + 1] ;
	char	lineout[LINEBUFLEN + 1] ;
	char	timebuf[50] ;
	char	cname[xx_ZNAMESIZE] ;
	char	*cp ;

	if ((cp = getenv(DEBUGFDVAR1)) == nullptr) {
	    cp = getenv(DEBUGFDVAR2) ;
	}

	if ((cp != nullptr) &&
	    (cfdeci(cp,-1,&fd_debug) >= 0)) {
	    esetfd(fd_debug) ;
	}

	bopen(ifp,BIO_STDIN,"dr",0666) ;
	bopen(ofp,BIO_STDOUT,"dwct",0666) ;
	bprintf(ofp,"date object test program\n") ;
	u_time(&daytime) ;

/* initial stuff */

	date_init(&d,nullptr,nullptr,0) ;

	n = date_nzones(&d) ;

	bprintf(ofp,"date_nzones=%d\n",n) ;

#if	CF_TZSET
	bprintf(ofp,"tzset()\n") ;
	tzset() ;
#endif /* CF_TZSET */

#if	CF_LOCALTIME
	bprintf(ofp,"localtime()\n") ;
	localtime(&daytime) ;
#endif

#if	CF_MKTIME
	{
	    TM	*tsp, ts ;
	    time_t		t ;

	    bprintf(ofp,"mktime()\n") ;

	    tsp = (TM *) localtime_r(&daytime,&ts) ;
	    daylight = 0 ;
	    timezone = 0 ;
	    rs = uc_mktime(tsp,&t) ;
	    bprintf(ofp,"mktime() rs=%d\n",rs) ;
	    bprintf(ofp,"made time=%s\n",
	        timestr_log(t,timebuf)) ;
	} /* end block */
#endif /* CF_MKTIME */


/* loop stuff */

	forever {
	    int		dlen ;
	    char	*dp ;
	    bprintf(ofp,"date types :\n") ;
	    for (int i = 0 ; i < 3 ; i += 1) {
	        switch (i) {
	        case 0:
	            bprintf(ofp,"\t%d\tSTD\n",i) ;
	            break ;
	        case 1:
	            bprintf(ofp,"\t%d\tMSG\n",i) ;
	            break ;
	        case 2:
	            bprintf(ofp,"\t%d\tLOGZ\n",i) ;
	            break ;
	        } /* end switch */
	    } /* end for */

	    bprintf(ofp,
	        "enter type and date_string> ") ;

	    if ((len = breadln(ifp,linebuf,LINEBUFLEN)) <= 0)
	        break ;

	    field_start(&f,linebuf,len) ;

/* get the type */

	    field_get(&f,tterms) ;

	    itype = f.fp[0] - '0' ;

	    if (f.term == ',') {
	        field_get(&f,tterms) ;
	        otype = f.fp[0] - '0' ;
	    } /* end if (getting output type) */

/* get the date_string */

#ifdef	COMMENT
	    field_get(&f,dterms) ;
#else
	    dp = f.lp ;
	    dlen = f.rlen ;
	    if (dlen > 0) {
	        while (CHAR_ISWHITE(dp[dlen - 1])) dlen -= 1 ;
	    }
#endif

	    if (dlen > 0) {
	        bprintf(ofp,
	            "converting string=>%W<\n",dp,dlen) ;
	        switch (itype) {
	        case 0:
	            rs = date_setstd(&d,dp,dlen) ;
	            break ;
	        case 1:
#if	CF_DEBUGS
	            eprintf("main: str=>%W<\n",dp,dlen) ;
#endif
	            rs = date_setmsg(&d,dp,dlen) ;
	            break ;
	        case 2:
	            rs = date_setlogz(&d,dp,dlen) ;
	            break ;
	        default:
	            rs = SR_NOTSUP ;
	            bprintf(ofp,"unknown input type\n") ;
		    break ;
	        } /* end switch */
	        bprintf(ofp,"date_setxxx() rs=%d\n",rs) ;
	        if (rs >= 0) {
	            bprintf(ofp,"f_zoff=%d\n",
	                d.f.zoff) ;
	            bprintf(ofp,"dstflag=%d\n",
	                d.b.dstflag) ;
	            bprintf(ofp,"local %s\n",
	                timestr_logz(d.b.time,timebuf)) ;
	            for (int i = 0 ; i < xx_DTSEND ; i += 1) {
	                sl = date_mkdatestr(&d,i,lineout,LINEBUFLEN) ;

	                bprintf(ofp,"date type=%d > %W <\n",
	                    i,lineout,sl) ;

	            } /* end for */

	        } else {
	            bprintf(ofp,"bad conversion (rs %d)\n",rs) ;
		}

	    } else {
	        bprintf(ofp,"no string given to convert\n") ;
	    }

	    field_finish(&f) ;
	} /* end while */

	bprintf(ofp,"\n") ;
	date_free(&d) ;
	bclose(ofp) ;
	return EX_OK ;
}
/* end subroutine (main) */


