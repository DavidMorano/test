/* mod_hello0 MODULE */

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


