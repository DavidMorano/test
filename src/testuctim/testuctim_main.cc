/* testuctim_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |uctim(3uc)| subroutines */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>
#include	<libdebug.h>		/* LIBDEBUG */

#include	"hasprint.h"


/* local defines */


/* imported namespaces */


/* local typedefs */

extern "C" {
    typedef bool (*hasprintx_f)(cchar *,int) noex ;
}


/* local structures */

enum result : bool {
    	resfail,
    	respass
} ;

struct testent {
    	cchar	*addr ;
	bool	fr ;
} ;


/* forward references */

local void testsuite(cc *,hasprintx_f,const testent *) noex ;


/* local variables */

constexpr testent	testbads[] = {
    	{ "127", 		resfail },
    	{ "\001:127", 		respass	},
    	{ "129.0.00.216", 	resfail	},
    	{ "0.0.00.216", 	resfail	},
    	{ ".0.00.216", 		resfail	},
    	{ "0.00.216", 		resfail	},
    	{ "0.0w.00.216", 	resfail	},
    	{ "0.0.00.", 		resfail	},
    	{ nullptr,		resfail	}
} ; /* end array (testbads) */

constexpr testent	testcmds[] = {
    	{ "127", 		resfail },
    	{ "\033[C:127",		respass	},
    	{ "bad-to-regular",	resfail	},
    	{ nullptr,		resfail	}
} ; /* end array (testcmds) */

constexpr cpcchar	res[] = {
    	"fail",
	"pass",
	nullptr
} ; /* end array (res) */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	testsuite("bad",hasprintbad,testbads) ;
    	testsuite("cmd",hasprintcmd,testcmds) ;
}
/* end subroutine (main) */


/* local subroutines */

local void testsuite(cc *af,hasprintx_f hasx,const testent *suite) noex {
    	cchar		*fmt = "%s %s %c %s\n" ;
	bool		fpass{} ;
	for (const testent *ep = suite ; ep->addr ; ep += 1) {
	    cbool f = hasx(ep->addr,-1) ;
	    fpass = (f == ep->fr) ;
	    printf(fmt,res[fpass],af,((f) ? 't' : 'f'),ep->addr) ;
	} /* end for */
} /* end subroutine (testsuite) */


