/* testhasinet_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |hasinet(3uc)| subroutine */
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

#include	"hasinet.h"


/* local defines */


/* imported namespaces */


/* local typedefs */

extern "C" {
    typedef bool (*hasinetx_f)(cchar *,int) noex ;
}


/* local structures */

enum result : bool {
    	resbad,
    	resgood
} ;

struct inetent {
    	cchar	*addr ;
	bool	fr ;
} ;


/* forward references */

local void testsuite(cc *,hasinetx_f,const inetent *) noex ;


/* local variables */

constexpr inetent	inet4s[] = {
    	{ "127", 		resgood	},
    	{ ":127", 		resbad	},
    	{ "129.0.00.216", 	resgood },
    	{ "0.0.00.216", 	resgood },
    	{ ".0.00.216", 		resbad	},
    	{ "0.00.216", 		resgood },
    	{ "0.0w.00.216", 	resbad	},
    	{ "0.0.00.", 		resbad	},
    	{ nullptr,		resbad	}
} ; /* end array (inet4s) */

constexpr inetent	inet6s[] = {
    	{ "0:1:a:b:c:d:e:f",	resgood },
    	{ "1:a::b:c::d:f",	resbad	},
    	{ "1:a::b:c:d:f:7",	resbad	},
    	{ ":1:a:b:c:d:e:f",	resbad	},
    	{ "1:a:b:c:d:e:f:",	resbad	},
    	{ "1:a:b:c",		resbad	},
    	{ "1:a:b:c:",		resbad	},
    	{ ":1:a:b:c",		resbad	},
    	{ ":1:a:b:c:",		resbad	},
    	{ "1:a:b::c:d:e:f",	resbad	},
    	{ "a:b::c:d:e:f",	resgood	},
    	{ "::1",		resgood },
    	{ "1::",		resgood },
    	{ "0::1",		resgood },
    	{ ":",			resbad },
    	{ "::",			resgood },
    	{ "::128:127",		resgood },
    	{ "0:1::",		resgood },
    	{ "127", 		resbad },
    	{ ":127", 		resbad },
#ifdef	COMMENT
    	{ "129.0.00.216", 	resbad },
    	{ "0.0.00.216", 	resbad },
    	{ ".0.00.216", 		resbad },
    	{ "0.00.216", 		resbad },
    	{ "0.0w.00.216", 	resbad },
#endif /* COMMENT */
    	{ nullptr,		resbad }
} ; /* end array (inet6s) */

constexpr cpcchar	res[] = {
    	"fail",
	"pass",
	nullptr
} ; /* end array (res) */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	testsuite("v4",hasinet4addrstr,inet4s) ;
    	testsuite("v6",hasinet6addrstr,inet6s) ;
}
/* end subroutine (main) */


/* local subroutines */

local void testsuite(cc *af,hasinetx_f hasx,const inetent *suite) noex {
    	cchar		*fmt = "%s %s %c %s\n" ;
	bool		fpass{} ;
	for (const inetent *ep = suite ; ep->addr ; ep += 1) {
	    cbool f = hasx(ep->addr,-1) ;
	    fpass = (f == ep->fr) ;
	    printf(fmt,res[fpass],af,((f) ? 't' : 'f'),ep->addr) ;
	} /* end for */
} /* end subroutine (testsuite) */


