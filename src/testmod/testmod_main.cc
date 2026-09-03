/* testmod_main SUPPORT (Test-Modules) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test modules */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	testmod_main

	Description:
	Test how C++ modules work.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<new>			/* C++STD */
#include	<initializer_list>	/* C++STD */
#include	<utility>		/* C++STD */
#include	<functional>		/* C++STD */
#include	<algorithm>		/* C++STD */
#include	<vector>		/* C++STD */
#include	<string>		/* C++STD */
#include	<fstream>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<iomanip>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"testmod_sub.hh"

#pragma		GCC dependency		"mod/modhello.ccm"

import modhello ;


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */
using std::cerr ;			/* variable */


/* external subroutines */

extern void	sub(cchar *) noex ;


/* external variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	hello_there("main-there") ;
	sub("main-sub") ;
} /* end subroutine (main) */


/* local subroutines */


