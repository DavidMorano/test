/* mod_hello1 MODULE */

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

module hello ;

using std::cout ;			/* variable */

extern "C++" void subfrank(cchar *sp) noex ;

void hello_there (cchar *sp)  noex {
	cout << "Hello there! - " << sp << " - " << eol ;
	jackbean("there-jackbean") ;
	subfrank("there-frank") ;
	header("there") ;
}

