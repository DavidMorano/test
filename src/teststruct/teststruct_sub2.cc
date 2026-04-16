/* teststruct_sub2 SUPPORT */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

#include	"teststruct_sub.hh"

constexpr substruct	s2 ;

void sub2() noex {
    printf("sub2 s2.a=%d\n",s2.a) ;
}


