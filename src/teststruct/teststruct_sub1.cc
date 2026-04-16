/* teststruct_sub1 SUPPORT */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>

#include	"teststruct_sub.hh"

constexpr substruct	s1 ;

void sub1() noex {
    printf("sub1 s1.a=%d\n",s1.a) ;
}


