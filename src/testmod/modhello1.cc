/* modhello1 MODULE */
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

extern void header(cchar *) noex ;

module modhello ;

using std::cout ;

extern "C++" void subfrank(cchar *sp) noex ;

void access() noex {
    	hidden	a{} ;
	cout << "v=" << a.v << eol ;
}

void hello_there (cchar *sp)  noex {
	cout << "Hello there! - " << sp << " - " << eol ;
	jackbean("there-jackbean") ;
	subfrank("there-frank") ;
	header("there") ;
	hello_hidden() ;
	access() ;
	cout << "one=" << hello_one << " two=" << hello_two << eol ;
}

