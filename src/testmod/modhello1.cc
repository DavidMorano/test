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
	modhello1

*******************************************************************************/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

module ;

#include	<envstandards.h>	/* ordered first to configure */
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>

extern void header(cchar *) noex ;

module modhello ;

using std::string ;
using std::cout ;
using std::hex ;

extern "C++" void subfrank(cchar *sp) noex ;

void access() noex {
    	hidden	a{} ;
	cout << "v=" << a.v << eol ;
}

void hello_there (cchar *sp)  noex {
    	string	s = "jack-in-the-box" ;
	cout << "Hello there! - " << sp << " - " << eol ;
	jackbean("there-jackbean") ;
	subfrank("there-frank") ;
	header("there") ;
	hello_hidden() ;
	access() ;
	cout << "one=" << hello_one << " two=" << hello_two << eol ;
	cout << hex << s << eol ;
}

