/* testtimezone_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* the getitng the time-zone */
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
	This program tests (evaluates) some aspects of time-zone
	retrieval.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdint>		/* CSTD */
#include	<new>			/* C++STD placement-new */
#include	<typeinfo>		/* C++STD */
#include	<typetraits>		/* C++STD */
#include	<chrono>		/* C++STD */
#include	<string>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<ucsysmisc.h>		/* LIBUC |uc_ftime(3uc)| */
#include	<uctime.h>		/* LIBUC */
#include	<ucgetx.h>		/* LIBUC |uc_gettimeofday(3uc)| */
#include	<tmtime.hh>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

import ulibvals ;			/* |ulibval(3u)| */

/* local defines */

#ifndef	VARDEBUGFILE
#define	VARDEBUGFILE	"TESTTIMEZONE_DEBUGFILE"
#endif


/* imported namespaces */

using std::is_same_v ;			/* template */
using std::type_info ;			/* template */
using std::cout ;			/* variable */
using libuc::mem ;			/* variable */

/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int libtypes	() noex ;
local int libchrono	() noex ;
local int libstrftime	() noex ;
local int libtmtime	() noex ;
local int libucftime	() noex ;
local int libucgettime	() noex ;
local int libuftime	() noex ;
local int libtimezone	() noex ;
local int libtzname	() noex ;


/* local variables */

static cint	maxtzname	= ulibval.maxtzname ;
cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv envv) {
    	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	if (cchar *cp = getourenv(envv,VARDEBUGFILE) ; cp) {
	    rs = DEBUGOPEN(cp) ;
	} /* end if (getenver) */
	DEBUGPRINTF("prepare rs=%d\n", rs) ;
	if ((rs >= 0) && ((rs = maxtzname) >= 0)) {
	    DEBUGPRINTF("beg maxtzname=%d\n", rs) ;
	    printf("maxtzname=%d\n",rs) ;
    	    if (rs >= 0) rs = libtypes() ;
    	    if (rs >= 0) rs = libchrono() ;
	    if (rs >= 0) rs = libstrftime() ;
	    if (rs >= 0) rs = libtmtime() ;
	    if (rs >= 0) rs = libucftime() ;
	    if (rs >= 0) rs = libucgettime() ;
	    if (rs >= 0) rs = libuftime() ;
	    if (rs >= 0) rs = libtimezone() ;
	    if (rs >= 0) rs = libtzname() ;
	    DEBUGPRINTF("end rs=%d\n",rs) ;
	} /* end if (maxtzname) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subrutine (main) */


/* local subroutines */

local int libtypes() noex {
    	TIMEZONE	tz{} ;
	timeb		tb{} ;
    	int		rs = SR_OK ;
	(void) tz ;
	(void) tb ;
	return rs ;
} /* end subroutine (libtypes) */

local int libchrono() noex {
    	int		rs = SR_OK ;
    try {
	cauto tzp = std::chrono::current_zone() ; // may throw
        cauto now = std::chrono::system_clock::now() ;
        const std::chrono::zoned_time cur_time(tzp,now) ; /* <- variable */
        cout << "cur_time=" << cur_time << eol ;
	cout << "zoneinfo=» " << tzp->name() << " «" << eol ;
	{
	    using namespace std::chrono ;
	    cauto info = tzp->get_info(now) ;
	    {
		seconds s_off = seconds(info.offset) ;
		seconds s_sav = seconds(info.save) ;
		/* cout << "zoneinfo=" << info.name() << eol ; */
		{
		    cauto roff = s_off.count() ;
		    cauto rsav = s_sav.count() ;
	            cout << "offset=" << info.offset ;
		    cout << " " << roff << eol ;
	            cout << "  save=" << info.save ;
		    cout << " " << rsav << eol ;
		}
	        {
	          cout << "save=  " << info.save << eol ;
	          cauto rsav = s_sav.count() ;
		  {
		      cint wsav = conv<int>(rsav) ;
		      printf("wsav=%d\n",wsav) ;
		  }
	        }
	    }
	    cout << "abbr=  " << info.abbrev << eol ;
	} /* end block */
    } catch (const std::runtime_error& ex) {
	rs = SR_IO ;
        std::cerr << ex.what() << '\n';
    }
    return rs ;
} /* end subroutine (libchrono) */

local int libstrftime() noex {
    	custime		dt = time(nullptr) ;
    	int		rs ;
	int		rs1 ;
	if (TM tmd ; (rs = uc_timelocal(&dt,&tmd)) >= 0) {
	    cchar *fmt = "%Z %z" ;
	    if (char *rbuf ; (rs = mem.zi(&rbuf)) >= 0) {
		cint rlen = rs ;
	        if ((rs = uc_strftime(rbuf,rlen,fmt,&tmd)) >= 0) {
		    cout << rbuf << eol ;
		} /* end if (uc_strdtime) */
		rs1 = mem.free(rbuf) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (m-a-f) */
	} /* end if (uc_timelocal) */
	return rs ;
} /* end subroutine (libstrftime) */

local int libtmtime() noex {
    	custime		dt = time(nullptr) ;
    	int		rs ;
	DEBUGPRINTF("ent\n") ;
	if (tmtime tmd ; (rs = tmtime_timelocal(&tmd,dt)) >= 0) ylikely {
	    cout << tmd.znbuf << " " << tmd.gmtoff << eol ;
	} /* end if (tmtime) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
    	return rs ;
} /* end subroutine (libtmtime) */

local int libucftime() noex {
    	int		rs ;
	DEBUGPRINTF("ent\n") ;
	if (TIMEB tb ; (rs = uc_ftime(&tb)) >= 0) {
	    printf("libucftime	timezone	=%d\n",tb.timezone) ;
	    printf("libucftime	dstflag		=%d\n",tb.dstflag) ;
	} /* end if (uc_ftime) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (libucftime) */

local int libucgettime() noex {
    	int		rs ;
	TIMEZONE tz ;
	if (TIMEVAL tv ; (rs = uc_gettimeofday(&tv,&tz)) >= 0) {
	    printf("libucgettime tz_minuteswest =%d\n",tz.tz_minuteswest) ;
	    printf("libucgettime     tz_dsttime =%d\n",tz.tz_dsttime) ;
	} /* end if (uc_gettimeofday) */
	return rs ;
} /* end subroutine (libucgettime) */

local int libuftime() noex {	
    	int		rs ;
	if (TIMEB tb ; (rs = libu::uftime(&tb)) >= 0) {
	    printf("libuftime timezone=%d\n",tb.timezone) ;
	    printf("libuftime  dstflag=%d\n",tb.dstflag) ;
	} /* end if (u_timezone) */
	return rs ;
} /* end subroutine (libuftime) */

local int libtimezone() noex {	
    	int		rs = SR_OK ;
	if (TIMEZONE tz ; (rs = u_timezone(&tz)) >= 0) {
	    printf("libtimezone tz_minuteswest=%d\n",tz.tz_minuteswest) ;
	    printf("libtimezone tz_dsttime    =%d\n",tz.tz_dsttime) ;
	} /* end if (u_timezone) */
	return rs ;
} /* end subroutine (libtimezone) */

local int libtzname() noex {	
    	cnothrow	nt{} ;
    	cint		rlen = maxtzname ;
    	int		rs = SR_NOMEM ;
	DEBUGPRINTF("ent\n") ;
	if (char *rbuf = new(nt) char [rlen + 1] ; rbuf) {
	    DEBUGPRINTF("rlen=%d -> u_tzname\n",rlen) ;
	    if ((rs = u_tzname(rbuf,rlen)) >= 0) {
	        printf("tzname=%s\n",rbuf) ;
	    } /* end if (u_tzname) */
	    delete [] rbuf ;
	} /* end if (m-a-f) */
	DEBUGPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (libtimezone) */

#ifdef	COMMENT
		    const std::type_info& tid = typeid(roff) ;
		    cout << "same-long=" ;
		    cout << bool(is_same_v<typeof(roff),long>) << eol ;
		    cout << "same-long_long=" ;
		    cout << bool(is_same_v<typeof(roff),long long>) << eol ;
		    cout << "same-int64_t=" ;
		    cout << bool(is_same_v<typeof(roff),int64_t>) << eol ;
		    cout << "type-name=" << tid.name() << eol ;
		    cout << "type-size=" << szof(roff) << eol ;
#endif /* COMMENT */


