/* hello MODULE */

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

export module hello ;

using std::cout ;			/* variable */

export extern void hello_there() noex ;

export void hello_there ()  noex {
	cout << "Hello there!" << eol ;
}

