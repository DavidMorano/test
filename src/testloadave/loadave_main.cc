/* loadave_main SUPPORT (testloadave) */
/* charset=ISO8859-1 */
/* version %I% last-modified %G% */

/* test the LIBUC |loadave(3uc)| object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1988-01-10, David A­D­ Morano
	This subroutine was written (originally) as a test of
	the LIBUC |loadave(3uc)| object.

*/

/* Copyright © 1988 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:
	Test the LOADAVE object.

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ucmem.h>		/* LIBU */
#include	<ucsysmisc.h>		/* LIBU */
#include	<ucnprocs.h>		/* LIBU */
#include	<loadave.h>		/* LIBUC */
#include	<timestr.h>		/* LIBUC */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */


/* local defines */

#define	TO		11

#define	LOOPS		10

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif

#define	LA		loadave
#define	LA_MID		loadave_mid
#define	LA_VAL		loadave_val


/* external subroutines */


/* external variables */


/* forward references */

local int	printla(uint v,cchar *s) noex ;


/* local variables */

cbool		f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int		rs ;
	int		rs1 ;
	int		ex = EXIT_SUCCESS ;
	if (loadave la ; (rs = loadave_start(&la)) >= 0) {
	    loadave_mid	mid ;
	    if ((rs = loadave_readmid(&la,&mid)) >= 0) {
		char timebuf[TIMEBUFLEN + 1] ;
	        timestr_log(mid.tim_read,timebuf) ;
	        printf("mid_time> %s\n",timebuf) ;
	        printf("provider> %s\n",mid.provider) ;
	        printf("serial>   %s\n",mid.serial) ;
		loadave_val lav ;
	        if ((rs = loadave_readval(&la,&lav)) >= 0) {
	    	    for (int i = 0 ; (rs >= 0) && (i < LOOPS) ; i += 1) {
	                if (i > 0) {
	                    sleep(1) ;
	                    rs = loadave_readval(&la,&lav) ;
	                } /* end if */
	                DEBUGPRINTF("loadave_read() rs=%d\n",rs) ;
	                if (rs >= 0) {
	                    timestr_log(lav.tim_la,timebuf) ;
	                    printf("la_time> %s\n",timebuf) ;
	                    printf("nproc=%d\n",lav.nprocs) ;
	                    printf("ncpu=%d\n",lav.ncpu) ;
	                    printla(lav.la1min,"la1min") ;
	                    printla(lav.la5min,"la5min") ;
	                    printla(lav.la15min,"la15min") ;
	                } /* end if (ok) */
	            } /* end for */
	        } /* end if (loadave_readval) */
	    } /* end if (loadave_readmid) */
	    rs1 = loadave_finish(&la) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (loadave) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int printla(uint v,cchar *s) noex {
	uint	la_i = (v >> FSHIFT) ;
	uint	la_f = +((v % FSCALE) * 1000) / FSCALE ;
	int	rs = SR_OK ;
	printf("%-14s",s) ;
	printf(" l=%u",v) ;
	printf(" la=%u.%04u\n",la_i,la_f) ;
	return rs ;
} /* end subroutine (printla) */


