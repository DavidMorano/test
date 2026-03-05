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


/* local structures */

struct inetent {
    	cchar	*addr ;
	bool	fr ;
} ;


/* forward references */

local void testsuite(const inetent *) noex ;


/* local variables */

constexpr inetent	inet4s[] = {
    	{ "127", 		true },
    	{ "129.0.00.216", 	true },
    	{ "0.0.00.216", 	true },
    	{ ".0.00.216", 		false },
    	{ "0.00.216", 		true },
    	{ "0.0w.00.216", 	false },
    	{ "0.0.00.", 		false },
    	{ nullptr,		false }
} ; /* end array (inet4s) */

constexpr inetent	inet6s[] = {
    	{ "129.0.00.216", 	true },
    	{ "0.0.00.216", 	true },
    	{ ".0.00.216", 		false },
    	{ "0.00.216", 		true },
    	{ "0.0w.00.216", 	false },
    	{ nullptr,		false }
} ; /* end array (inet6s) */

constexpr cpcchar	res[] = {
    	"fail",
	"pass",
	nullptr
} ; /* end array (res) */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	testsuite(inet4s) ;
    	testsuite(inet6s) ;
}
/* end subroutine (main) */


/* local subroutines */

local void testsuite(const inetent *suite) noex {
	bool		fpass{} ;
	for (const inetent *ep = suite ; ep->addr ; ep += 1) {
	    cbool f = hasinet4addrstr(ep->addr,-1) ;
	    fpass = (f == ep->fr) ;
	    printf("%s %c %s\n",res[fpass],((f) ? 't' : 'f'),ep->addr) ;
	} /* end for */
} /* end subroutine (testsuite) */


