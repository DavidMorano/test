/* testcharset SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test how the (given) compiler treats non-ASCII characters */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A≠D≠ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A≠D≠ Morano.  All rights reserved. */

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
#include	<usysbase.h>
#include	<localmisc.h>		/* |eol| */


/* local defines */


/* name-spaces */

using std::cout ;			/* variable */


/* external subroutines */


/* external variables */


/* local structures (and methods) */


/* forward references */

static void encoding() ;


/* local variables */

const cchar	gﬂstr[] = "g-str" ;
const cchar	µgﬂstr[] = "l-str" ;
const cchar	™gﬂstr[] = "str2" ;
const cchar	∫gﬂstr[] = "str3" ;
const cchar	ﬂgﬂstr[] = "str4" ;
const cchar	ﬂgﬂstrπ[] = "strπ" ;
const cchar	ﬂgﬂstr≤[] = "str≤" ;
const cchar	ﬂgﬂstr≥[] = "str≥" ;
const cchar	ﬂg$str[] = "str$" ;
const cchar	ﬂg™str[] = "str™" ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    	cout << "Hello world! - J‚ck SmÓth" << eol ;
	{
	    int	∫ch = '‡' ;
	    cout << "ch=" << ∫ch << eol ;
	}
	{
	    cchar	*ﬂthere = "xx-there" ;
	    cout << ﬂthere << eol ;
	}
	{
	    cout << gﬂstr << eol ;
	    cout << µgﬂstr << eol ;
	    cout << ™gﬂstr << eol ;
	    cout << ∫gﬂstr << eol ;
	    cout << ﬂgﬂstr << eol ;
	    cout << ﬂgﬂstrπ << eol ;
	    cout << ﬂgﬂstr≤ << eol ;
	    cout << ﬂgﬂstr≥ << eol ;
	    cout << ﬂg$str << eol ;
	}
	encoding() ;
}
/* end subroutine (main) */


/* local subroutines */

void encoding() {
    cout << "encoding" << eol ;
} /* end subroutine (encoding) */


