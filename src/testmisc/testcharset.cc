/* testcharset SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test how the (given) compiler treats non-ASCII characters */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A�D� Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright � 2013 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	main

	Description:
	I test something to do with a character set.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cinttypes>
#include	<cstring>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<string>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<locale>
#include	<print>
#include	<text_encoding>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures (and methods) */


/* forward references */

static void encoding() ;


/* local variables */

const cchar	g�str[] = "g-str" ;
const cchar	�g�str[] = "l-str" ;
const cchar	�g�str[] = "str2" ;
const cchar	�g�str[] = "str3" ;
const cchar	�g�str[] = "str4" ;
const cchar	�g�str�[] = "str�" ;
const cchar	�g�str�[] = "str�" ;
const cchar	�g�str�[] = "str�" ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cout << "Hello world! - J�ck Sm�th" << eol ;
	{
	    int	�ch = '�' ;
	    cout << "ch=" << �ch << eol ;
	}
	{
	    cchar	*�there = "xx-there" ;
	    cout << �there << eol ;
	}
	{
	    cout << g�str << eol ;
	    cout << �g�str << eol ;
	    cout << �g�str << eol ;
	    cout << �g�str << eol ;
	    cout << �g�str << eol ;
	    cout << �g�str� << eol ;
	    cout << �g�str� << eol ;
	    cout << �g�str� << eol ;
	}
	encoding() ;
}
/* end subroutine (main) */


/* local subroutines */

void encoding() {
    cout << "encoding" << eol ;
} /* end subroutine (encoding) */


