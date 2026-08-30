/* testtimestr_main SUPPORT (testdate) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the TIMESTR famility */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<csignal>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD |tzset(3c)| */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<baops.h>		/* LIBU */
#include	<field.h>		/* LIBUC */
#include	<logfile.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |TIMEBUFLEN| */
#include	<bfile.h>		/* LIBB */


/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* external subroutines */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    	custime		dt = time(nullptr) ;
	char		timebuf[TIMEBUFLEN + 1] ;
	printf("tzname 1 » %s %s «\n",tzname[0],tzname[1]) ;
	printf("edate » %s «\n",timestr_edate(dt,timebuf)) ;
	printf("tzname 2 » %s %s «\n",tzname[0],tzname[1]) ;
	tzset() ;
	printf("tzname 3 » %s %s «\n",tzname[0],tzname[1]) ;
	printf("edate » %s «\n",timestr_edate(dt,timebuf)) ;
} /* end subroutine (main) */


