/* testlibtime SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test time time function */
/* version %I% last-modified %G% */

#define	CF_TZSET	0		/* call 'tzset(3)' */
#define	CF_LOCALTIME	0
#define	CF_MKTIME	1

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */

#undef	LOCAL_DARWIN
#define	LOCAL_DARWIN	\
	(defined(OSNAME_Darwin) && (OSNAME_Darwin > 0))

#undef	LOCAL_SUNOS
#define	LOCAL_SUNOS	\
	(defined(OSNAME_SunOS) && (OSNAME_SunOS > 0))



/* local structures */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	TM	tms, *tmp = nullptr ;
	time_t	daytime = time(nullptr) ;
	time_t	t ;
	int	rs ;

#if	CF_TZSET
	tzset() ;
#endif

/* localtime_r(3c) test */

#if	CF_LOCALTIME

	fprintf(stdout,"test: localtime\n") ;

	memset(&tms,0,sizeof(TM)) ;

	tmp = localtime_r(&daytime,&tms) ;

	if (tmp != nullptr) {

		fprintf(stdout,"sec=   %u\n",tmp->tm_sec) ;
		fprintf(stdout,"min=   %u\n",tmp->tm_min) ;
		fprintf(stdout,"hour=  %u\n",tmp->tm_hour) ;
		fprintf(stdout,"mday=  %u\n",tmp->tm_mday) ;
		fprintf(stdout,"mon=   %u\n",tmp->tm_mon) ;
		fprintf(stdout,"year=  %u\n",tmp->tm_year) ;
		fprintf(stdout,"wday=  %u\n",tmp->tm_wday) ;
		fprintf(stdout,"isdst= %d\n",tmp->tm_isdst) ;
		fprintf(stdout,"zone=  %s\n",tmp->tm_zone) ;
		fprintf(stdout,"gmtoff=%d\n",tmp->tm_gmtoff) ;
	} else {
		fprintf(stdout,"failed\n") ;
	}

#endif /* CF_LOCALTIME */

/* mktime(3) test */

#if	CF_MKTIME

	fprintf(stdout,"test: mktime\n") ;

	if (tmp == nullptr) {
		tmp = &tms ;
		memset(&tms,0,sizeof(TM)) ;
		tms.tm_year = 107 ;
		tms.tm_mon = 7 ;
		tms.tm_mday = 28 ;
		tms.tm_hour = 9 ;
		tms.tm_min = 0 ;
		tms.tm_sec = 0 ;
		tms.tm_isdst = -1 ;
	}
	t = mktime(tmp) ;
	fprintf(stdout,"time=%lX\n",t) ;
		fprintf(stdout,"zone=  %s\n",tmp->tm_zone) ;
		fprintf(stdout,"gmtoff=%d\n",tmp->tm_gmtoff) ;

#endif /* CF_MKTIME */

/* done */
	return 0 ;
}
/* end subroutine (main) */


