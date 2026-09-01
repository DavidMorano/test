/* testchrono_main SUPPORT (testchrono) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test |sntmtime(3uc)| */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debugging */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<chrono>		/* CSTD */
#include	<iostream>		/* CSTD */
#include	<iomanip>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<tmtime.hh>		/* LIBUC */
#include	<sntmtime.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/cmdutils.ccm"

import libutil ;			/* |lenstr(3u)| */
import cmdutils ;			/* |optval(3uc)| */

/* local defines */

#define	VARDEBUGFNAME	"TESTCHRONO_DEBUGFILE"

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* compile-time debugging */
#endif


/* imported namespaces */

using std::cout ;			/* variable */


/* local typedefs */

using sub_f	= int (*)(time_t) noex ;


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int procargs	(int,con mainv) noex ;
local int procvals	(time_t) noex ;
local int procdefzone	(time_t) noex ;
local int proceval	(time_t) noex ;
local int proclocaltime	(time_t) noex ;
local int procmktime	(time_t) noex ;
local int procmktimer	(time_t) noex ;


/* local variables */

constexpr sub_f		subs[] = {
	&procvals,
	&procdefzone,
	&proceval,
	&proclocaltime,
	&procmktime,
	&procmktimer
} ; /* end array */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) noex {
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	if (cchar *cp = getourenv(envv,VARDEBUGFNAME) ; cp) {
	    debugopen(cp) ;
	    DEBUGPRINTF("starting dfn=%s\n",cp) ;
	} /* end if (debugopen) */
	if ((rs >= 0) && (argc > 1)) {
	    rs = procargs(argc,argv) ;
	} /* end if (ok) */
	if (rs >= 0) {
	    custime dt = getustime ;
	    for (cauto &fun : subs) {
		rs = fun(dt) ;
		if (rs < 0) break ;
	    } /* end for */
	} /* end if (ok) */
	DEBUGPRINTF("ret rs=%d ex=%d\n",rs,ex) ;
	debugclose() ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (exit-return) */
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int procargs(int argc,con mainv argv) noex {
	custime		dt = getustime ;
	int		rs ;
	if (tmtime tmt ; (rs = tmt.timelocal(dt)) >= 0) {
	    cint	tlen = TIMEBUFLEN ;
	    char	tbuf[TIMEBUFLEN+1] ;
	    cchar	*fmt ;
	    for (int ai = 1 ; ai < argc ; ai += 1) {
                fmt = argv[ai] ;
                rs = sntmtime(tbuf,tlen,&tmt,fmt) ;
                if (rs >= 0) {
                    printf("%s\n",tbuf) ;
                }
                if (rs < 0) break ;
            } /* end for */
	} /* end if (tmtime_timelocal) */
	return rs ;
} /* end subroutine (procargs) */

local int procvals(time_t dt) noex {
	cint		tlen = TIMEBUFLEN ;
    	int		rs = SR_OK ;
	char		tbuf[TIMEBUFLEN + 1] ;
	printf(" dt=%ld\n",dt) ;
	printf("time-loc » %s «\n",timestr_edate(dt,tbuf)) ;
	if (tmtime tmd ; (rs = tmd.timelocal(dt)) >= 0) {
	    printf("loc-off           isdst=%d\n",tmd.isdst) ;
	    printf("loc-off (secs west GMT)=%d\n",tmd.gmtoff) ;
	    cchar *fmt = "%y:%m:%d %H%M:%S $Z %O %z" ;
	    if ((rs = sntmtime(tbuf,tlen,&tmd,fmt)) >= 0) {
	        if (time_t ntv ; (rs = tmd.mktime(&ntv)) >= 0) {
		    printf("ntv=%ld\n",ntv) ;
	            printf("time-loc » %s «\n",timestr_edate(ntv,tbuf)) ;
		    ntv += (3600) ;
	            printf("time-rem » %s «\n",timestr_edate(ntv,tbuf)) ;
		    {
			tmd.gmtoff += (1 * 3600) ;
	        	if (time_t rtv ; (rs = tmd.mktime(&rtv)) >= 0) {
	            	    printf("time-rem » %s «\n",
				   timestr_edate(rtv,tbuf)) ;
			} /* end if (tmtime_mktime) */
		    } /* end block */
	        } /* end if (tmtime_mktime) */
	    } /* end if (sntmtime) */
	} /* end if (tmtime) */
    	return rs ;
} /* end subroutine (procvals) */

constexpr cpcchar	znames[] = {
        "US/Eastern",
        "US/Central",
       	"US/Mountain",
        "US/Pacific"
} ; /* end array (znames) */

local int procdefzone(time_t) noex {
    using namespace	std::chrono ;
    int		rs = SR_OK ;
    // 1. Alias the standard traits specialization for convenience
    using tz_traits = std::chrono::zoned_traits<const time_zone *> ;
    // 2. Fetch the default time zone pointer (returns UTC time zone pointer)
    const time_zone *def_zone = tz_traits::default_zone() ;
    // 3. Output the name of the retrieved time zone
    if (def_zone) {
        cout << "defzone="<< def_zone->name() << eol ;
    }
    return rs ;
} /* end subroutine (procdefzone) */

local int proceval(time_t) noex {
    	using namespace std::chrono ;
	using		std::setw ;
    	int		rs = SR_OK ;
        try {
            for (cauto &zn : znames) {
	        con time_zone *tzp = locate_zone(zn) ;
                cout << setw(20) << zn << " " << tzp->name() << eol ;
	    } /* end for */
        } catch (const std::runtime_error& ex) {
            cout << ex.what() << '\n';
        } catch (...) {
	    cout << "exception" << eol ;
        } /* end try */
    	return rs ;
} /* end subroutine (procvals) */

local int proclocaltime(time_t) noex {
    using namespace std::chrono ;
    con time_point	now = system_clock::now() ;
    con time_zone	*tzp = current_zone() ;
    int			rs = SR_OK ;
    // 1. Get the current time in the local time zone
    zoned_time local_time{ tzp , now } ;
    // 2. Extract the local time point (analogous overall local timestamp)
    auto local_tp = local_time.get_local_time();
    // 3. Separate into Date components (Year, Month, Day)
    local_days local_date = floor<std::chrono::days>(local_tp);
    year_month_day ymd{local_date};
    // 4. Separate into Time components (Hours, Minutes, Seconds, Subseconds)
    hh_mm_ss hms{local_tp - local_date};
    // 5. Access individual fields directly
    int 	tm_year		= static_cast<int>(ymd.year());
    unsigned 	tm_month	= static_cast<unsigned>(ymd.month());
    unsigned 	tm_day		= static_cast<unsigned>(ymd.day());
    (void) tm_year ;
    (void) tm_month ;
    (void) tm_day ;
    long tm_hours   = hms.hours().count();
    long tm_minutes = hms.minutes().count();
    long tm_seconds = hms.seconds().count();
    (void) tm_hours ;
    (void) tm_minutes ;
    (void) tm_seconds ;
    cout << "Local Date: " << ymd << eol ;
    cout << "Local Time: " << hms << eol ;
	return rs ;
} /* end subroutine (proclocaltime) */

local int procmktime(time_t dt) noex {
        using namespace std::chrono ;
        con time_point	now = system_clock::now() ;
        con time_zone	*tzp = current_zone() ;
    	int		rs = SR_OK ;
	{
    	    zoned_time lt{ tzp , now } ;
	    {
	        cauto st = lt.get_sys_time() ;
	        {
	            con time_t zt = system_clock::to_time_t(st) ;
	            cout << "mktime  zt=" << zt << eol ;
	            cout << "mktime  dt=" << dt << eol ;
	        }
	    }
	} /* end block */
	return rs ;
} /* end subroutine (procmktime) */

local time_t mktimer(cauto &zt) noex {
        using namespace std::chrono ;
	cauto st = zt.get_sys_time() ;
	time_t t{} ;
	{
	    t = system_clock::to_time_t(st) ;
	}
	return t ;
} /* end subroutine (mktimer) */

local int procmktimer(time_t dt) noex {
        using namespace std::chrono ;
        con time_zone	*tzp = current_zone() ;
    	int		rs = SR_OK ;
	{
    // 2. Define individual integer components
	    TM	*tmp = localtime(&dt) ;
    // 3. Construct the Date component
    year_month_day ymd{
        year{tmp->tm_year + TMTIME_YEARBASE},
        month{uint(tmp->tm_mon + 1)},
        day{uint(tmp->tm_mday)}
    } ;
    // 4. Construct the Time component (as a duration)
    auto time_duration = hours{tmp->tm_hour}
                       + minutes{tmp->tm_min}
                       + seconds{tmp->tm_sec} ;
    // 5. Combine into a type-safe local time point
    // local_days converts date to a days-resolution time point
    local_time<seconds> local_tp{ local_days{ymd} + time_duration } ;
    // 6. Construct the final zoned_time
    zoned_time zt{ tzp, local_tp, choose::earliest } ;
    cout << "zoned_time=" << zt << eol ;
    // Output validation
    {
	custime tt = mktimer(zt) ;
    cout << "mktimer zt=" << tt << eol ;
    cout << "mktimer dt=" << dt << eol ;
    }
	} /* end block */
	return rs ;
} /* end subroutine (procmktimer) */

#ifdef	COMMENT
// Choose the EARLIER system time if the local time is ambiguous
std::chrono::zoned_time zt_earlier{tz, local_tp, std::chrono::choose::earlier};
// Choose the LATER system time if the local time is ambiguous
std::chrono::zoned_time zt_later{tz, local_tp, std::chrono::choose::later};
#endif /* COMMENT */


