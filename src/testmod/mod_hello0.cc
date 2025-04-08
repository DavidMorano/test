/* mod_hello0 MODULE */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* test modules */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/*******************************************************************************

  	Name:
	mod_main

*******************************************************************************/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

module ;

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<iostream>
#include	<iomanip>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>

void header(cchar *s) noex {
    std::cout << "header" << " - " << s << eol ;
}

export module hello ;

using std::cout ;

export extern void hello_there(cchar *) noex ;

void jackbean(cchar *sp) noex {
    cout << "hello - " << sp << eol ;
}

struct hidden {
    	int	v ;
} ;

void hello_hidden() noex {
    	cout << "hello-hidden" << eol ;
}


