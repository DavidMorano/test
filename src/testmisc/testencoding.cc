/* testencoding SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	main

	Description:
	I test something to do with text encodings.

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

extern cchar	gßstr[] ;

const cchar	gßstr[] = "g-str" ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
    	cout << "Hello world! - Jâck Smîth" << eol ;
	{
	    cchar	*ßthere = "xx-there" ;
	    cout << ßthere << eol ;
	}
	{
	    cout << gßstr << eol ;
	}
	encoding() ;
}
/* end subroutine (main) */


/* local subroutines */

void encoding() {
    // literal encoding is known at compile-time
    constexpr std::text_encoding literal_encoding = 
		std::text_encoding::literal();
 
    // check for literal encoding
    static_assert(literal_encoding.mib() != std::text_encoding::other &&
                  literal_encoding.mib() != std::text_encoding::unknown);
 
    // environment encoding is only known at runtime
    std::text_encoding env_encoding = std::text_encoding::environment();
 
    // associated encoding of the default locale
    std::text_encoding locale_encoding = std::locale("").encoding();
 
    std::println("The literal encoding is {}", literal_encoding.name());
    std::println("The aliases of literal encoding:");
    for (const char* alias_name : literal_encoding.aliases())
        std::println(" -> {}", alias_name);
 
    if (env_encoding == locale_encoding)
        std::println("Both environment and locale encodings are the same");
 
    std::println("The environment encoding is {}", env_encoding.name());
    std::println("The aliases of environment encoding:");
    for (const char* alias_name : env_encoding.aliases())
        std::println(" -> {}", alias_name);
} /* end subroutine (encoding) */


