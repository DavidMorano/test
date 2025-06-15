/* testlambda SUPPORT */
/* charset=ISO8859-1 */
/* C++20 */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* |sleep(3c)| */
#include	<iostream>
#include	<localmisc.h>


/* local defines */

#ifndef	SR_OK
#define	SR_OK		0
#endif

#ifndef	SR_LOCKLOST
#define	SR_LOCKLOST	-20
#endif

#ifndef	SR_TIMEDOUT
#define	SR_TIMEDOUT	-21
#endif


/* external subroutines */

extern "C" {
	static int	xsleep(int) noex ;
}


/* external variables */

volatile sig_atomic_t	f_init = true ;
volatile sig_atomic_t	f_initdone = 0 ;


using namespace	std ;

int callout(auto lamb) noex {
    return lamb() ;
}

class timewatch {
	int	to ;
public:
	timewatch(int a) : to(a) { } ;
	template<typename L>
	int operator () (L lamb) {
	    int		rs = SR_OK ;
	    for (int i = 0 ; (rs == 0) && (i < to) ; i += 1) {
		if ((rs = xsleep(1)) >= 0) {
		    rs = callout(lamb) ;
		}
	    } /* end for */
	    return rs ;
	} ;
} ; /* end class (timewatch) */


/* exported subroutines */

int main(int,const char **,const char **) {
	int	rs = SR_OK ;
	cout << "Hello world!" << '\n' ;
	{
	    timewatch	tw(5) ;
	    int		c = 0 ;
	    auto lamb = [&c,cn = int(0)] () mutable -> int {
	        int		rs = SR_OK ;
		cout << "c=" << c++ << '\n' ;
		cout << "cn=" << cn++ << '\n' ;
	        if (!f_init) {
		    rs = SR_LOCKLOST ;
	        } else if (f_initdone) {
		    rs = 1 ;
	        }
	        return rs ;
	    } ;
	    cint	rv = lamb() ;
	    cout << "rv=" << rv << '\n' ;
	    rs = tw(lamb) ;
	    cout << "final c=" << c << '\n' ;
	} /* end block */
	cout << "exiting rs=" << rs << '\n' ;
	return (rs >= 0) ? 1 : rs ;
}
/* end subroutine (main) */


/* local subroutines */

int init() {
	return 0 ;
}
/* end subroutine (init) */

static int xsleep(int to) noex {
    	sleep(to) ;
	return 0 ;
}


