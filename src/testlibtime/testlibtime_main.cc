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
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
	TM	tms{} ;
	TM	*tmp = nullptr ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	(void) argc ;
	(void) argv ;
	(void) envv ;

#if	CF_TZSET
	tzset() ;
#endif

/* localtime_r(3c) test */

#if	CF_LOCALTIME
	{
	time_t		dt = time(nullptr) ;
	fprintf(stdout,"test: localtime\n") ;

	tmp = localtime_r(&dt,&tms) ;

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

	} /* end block */
#endif /* CF_LOCALTIME */

/* mktime(3) test */

#if	CF_MKTIME
	{
	time_t		t ;
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
		fprintf(stdout,"gmtoff=%ld\n",tmp->tm_gmtoff) ;

	} /* end block */
#endif /* CF_MKTIME */

	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


