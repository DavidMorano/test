/* testtimestr_main SUPPORT (testdate) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the TIMESTR famility */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

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
#include	<cstdio>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<bfile.h>
#include	<field.h>
#include	<logfile.h>
#include	<baops.h>
#include	<timestr.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| */


/* local defines */

#ifndef	LINELEN
#define	LINELEN		100
#endif


/* external subroutines */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {)
	char	linebuf[LINELEN + 1] ;
	char	timebuf[TIMEBUFLEN + 1] ;
	print("main: entered\n\n") ;
	printf("tzname 1 %s %s\n",tzname[0],tzname[1]) ;
	tzset() ;

	printf("tzname 2 %s %s\n",tzname[0],tzname[1]) ;
	printf("edate\n%s\n",timestr_edate(daytime,timebuf)) ;
	printf("tzname 3 %s %s\n",tzname[0],tzname[1]) ;
	printf("tzset edate\n%s\n",timestr_edate(daytime,timebuf)) ;
} /* end subroutine (main) */


