/* testtime_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test time */
/* version %I% last-modified %G% */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/timeb.h>
#include	<ctime>
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<timestr.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| */

extern "C" {
    extern int uc_ftime(TIMEB *) noex ;
}

int main(int,con mainv,con mainv) {
	time_t	daytime = time(nullptr) ;
	int	rs = SR_OK ;
	char	timebuf[TIMEBUFLEN + 1] ;
	if (rs >= 0) {
	    time_t	a[6] = {} ;
	    a[0] = daytime ;
	    a[1] = INT_MAX ;
	    for (int i = 0 ; (rs >= 0) && (i < 2) ; i += 1) {
	        printf("time=\\x%08lx (%s)\n",
		    a[i],timestr_log(a[i],timebuf)) ;
	    } /* end for */
	} /* end if (ok) */
	/* |gettimeofday(3c)| */
	for (int i = 0 ; (rs >= 0) && (i < 5) ; i += 1) {
	    TIMEVAL tv ;
	    gettimeofday(&tv,nullptr) ;
	    printf("time=\\x%08lx (%s)\n",
		tv.tv_sec,timestr_log(tv.tv_sec,timebuf)) ;
	    printf("usec=%d\n",
		tv.tv_usec) ;
	} /* end for */
	/* try |ftime(3c)| */
	if (rs >= 0) {
	    if (TIMEB b ; (rs = uc_ftime(&b)) >= 0) {
	        printf("time=\\x%08lx (%s)\n",
		    b.time,timestr_log(b.time,timebuf)) ;
	        printf("milli=\\x%08x (%d)\n",
		    b.millitm,b.millitm) ;
	        printf("timezone=%d\n",
		    b.timezone) ;
	        printf("dstflag=%d\n",
		    b.dstflag) ;
	    } /* end if */
	} /* end if (ok) */
	if (rs < 0) printf("failure\n") ;
} /* end subroutine (main) */


