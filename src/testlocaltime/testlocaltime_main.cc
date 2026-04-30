/* testlocaltime_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |localtime_r(3c)| subroutine */
/* version %I% last-modified %G% */

#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


/* local defines */


/* exported variables */


/* external subroutines */

int main(int,con mainv,con mainv) {
	time_t		dt = time(nullptr) ;
	int		rs = SR_OK ;
	int		ex = EXIT_SUCCESS ;
	TM		ts ;
	localtime_r(&dt,&ts) ;
	printf("isdst=%d\n",ts.tm_isdst) ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


