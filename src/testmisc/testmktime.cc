/* testmktime SUPPORT (C89) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test TM |mktime(3c)| */
/* version %I% last-modified %G% */

#define	CF_UCMKTIME	1		/* use 'uc_mktime(3uc)' */

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
#include	<cstring>		/* CSTD |memset(3c)| */
#include	<cstdio>		/* CSTD */
#include	<tzfile.h>		/* |TM_YEAR_BASE| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


int main(int,con mainv,con mainv) {
	TM tmval{} ;
	time_t		t = 0 ;
	cint	year = 2014 ;
	cint	m = 2 ; /* March */
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;

	tmval.tm_isdst = -1 ;
	tmval.tm_year = (year - TM_YEAR_BASE) ;
	tmval.tm_mon = m ;
	tmval.tm_sec = 0 ;
	tmval.tm_mday = 1 ;

#if	CF_UCMKTIME
	rs = uc_mktime(&tms,&t) ; /* always in current time zone! */
#else
	t = mktime(&tms) ;
#endif

	printf("main: uc_mktime() rs=%d\n",rs) ;
	printf("main: tmval.wday=%u\n",tmval.tm_wday) ;
	printf("main: tmval.isdst=%u\n",tmval.tm_isdst) ;

	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
/* end subroutine (main) */

