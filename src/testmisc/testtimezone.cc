/* testtimezone SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* the getitng the time-zone */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1992 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>
#include	<cstdlib>
#include	<chrono>
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

using std::cout ;

int main(int,con mainv,con mainv) {
    try {
	cauto tz = std::chrono::current_zone() ; // may throw
        cauto now = std::chrono::system_clock::now() ;
        const std::chrono::zoned_time cur_time(tz,now) ;
        std::cout << cur_time << '\n';
    } catch(const std::runtime_error& ex) {
        std::cerr << ex.what() << '\n';
    }
} /* end subrutine (main) */


